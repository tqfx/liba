//! fuzzy proportional integral derivative controller

use crate::float;
use crate::uint;
use crate::PID;

/// enumeration for fuzzy PID controller operator
#[repr(C)]
pub enum op {
    /// sqrt(l,r)*sqrt(1-(1-r)*(1-r))
    EQU,
    /// min(l,r)
    AND,
    /// l*r
    AND_ALGEBRA,
    /// max(l,r)
    AND_BOUNDED,
    /// max(l,r)
    OR,
    /// l+r-l*r
    OR_ALGEBRA,
    /// min(l,r)
    OR_BOUNDED,
}

/// fuzzy proportional integral derivative controller
#[repr(C)]
pub struct PID_fuzzy {
    /// proportional integral derivative controller
    pub pid: PID,
    pub(crate) me: *const float,
    pub(crate) mec: *const float,
    pub(crate) mkp: *const float,
    pub(crate) mki: *const float,
    pub(crate) mkd: *const float,
    pub(crate) idx: *mut uint,
    pub(crate) val: *mut float,
    /// fuzzy relational operator
    pub(crate) op: extern "C" fn(float, float) -> float,
    /// base proportional constant
    pub kp: float,
    /// base integral constant
    pub ki: float,
    /// base derivative constant
    pub kd: float,
    /// number of columns in the rule base
    pub(crate) col: uint,
    /// maximum number triggered by the rule
    pub(crate) buf: uint,
}

extern "C" {
    fn a_pid_fuzzy_op(op: uint) -> extern "C" fn(float, float) -> float;
    fn a_pid_fuzzy_set_op(ctx: *mut PID_fuzzy, op: uint);
    fn a_pid_fuzzy_chan(
        ctx: *mut PID_fuzzy,
        num: uint,
        out: *mut float,
        fdb: *mut float,
        tmp: *mut float,
        err: *mut float,
    );
    fn a_pid_fuzzy_rule(
        ctx: *mut PID_fuzzy,
        num: uint,
        me: *const float,
        mec: *const float,
        mkp: *const float,
        mki: *const float,
        mkd: *const float,
    );
    fn a_pid_fuzzy_kpid(ctx: *mut PID_fuzzy, kp: float, ki: float, kd: float);
    fn a_pid_fuzzy_buff(ctx: *mut PID_fuzzy, idx: *mut uint, val: *mut float);
    fn a_pid_fuzzy_outf(ctx: *mut PID_fuzzy, set: float, fdb: float) -> float;
    fn a_pid_fuzzy_outp(ctx: *mut PID_fuzzy, set: *const float, fdb: *const float) -> *const float;
    fn a_pid_fuzzy_zero(ctx: *mut PID_fuzzy);
}

impl PID_fuzzy {
    /// initialize function for fuzzy PID controller
    pub fn new(min: float, max: float, sum: float) -> Self {
        PID_fuzzy {
            pid: PID::new(min, max, sum),
            me: std::ptr::null(),
            mec: std::ptr::null(),
            mkp: std::ptr::null(),
            mki: std::ptr::null(),
            mkd: std::ptr::null(),
            idx: std::ptr::null_mut(),
            val: std::ptr::null_mut(),
            op: unsafe { a_pid_fuzzy_op(op::EQU as uint) },
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            col: 0,
            buf: 0,
        }
    }

    /// set buffer for multichannel fuzzy PID controller
    pub fn chan(
        &mut self,
        out: &mut [float],
        fdb: &mut [float],
        tmp: &mut [float],
        err: &mut [float],
    ) -> &mut Self {
        unsafe {
            a_pid_fuzzy_chan(
                self,
                out.len() as uint,
                out.as_mut_ptr(),
                fdb.as_mut_ptr(),
                tmp.as_mut_ptr(),
                err.as_mut_ptr(),
            )
        };
        self
    }

    /// set rule base for fuzzy PID controller
    pub fn rule(
        &mut self,
        col: usize,
        me: &[float],
        mec: &[float],
        mkp: &[float],
        mki: &[float],
        mkd: &[float],
    ) -> &mut Self {
        unsafe {
            a_pid_fuzzy_rule(
                self,
                col as uint,
                me.as_ptr(),
                mec.as_ptr(),
                mkp.as_ptr(),
                mki.as_ptr(),
                mkd.as_ptr(),
            )
        };
        self
    }

    /// set proportional integral derivative constant for fuzzy PID controller
    pub fn kpid(&mut self, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_fuzzy_kpid(self, kp, ki, kd) };
        self
    }

    /// set buffer for fuzzy PID controller
    pub fn buff(&mut self, idx: &mut [u32], val: &mut [float]) -> &mut Self {
        unsafe { a_pid_fuzzy_buff(self, idx.as_mut_ptr(), val.as_mut_ptr()) };
        self
    }

    /// set fuzzy relational operator for fuzzy PID controller
    pub fn op(&mut self, op: op) -> &mut Self {
        unsafe { a_pid_fuzzy_set_op(self, op as uint) };
        self
    }

    /// calculate function for fuzzy PID controller
    pub fn outf(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_fuzzy_outf(self, set, fdb) }
    }
    /// calculate function for multichannel fuzzy PID controller
    pub fn outp(&mut self, set: &[float], fdb: &[float]) -> &[float] {
        unsafe {
            std::slice::from_raw_parts(
                a_pid_fuzzy_outp(self, set.as_ptr(), fdb.as_ptr()),
                self.pid.chan as usize,
            )
        }
    }

    /// zero clear function for fuzzy PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_fuzzy_zero(self) };
        self
    }
}

#[test]
#[allow(non_snake_case)]
fn pid_fuzzy() {
    let NL: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PL: float = 3.0;
    let me = [
        [crate::mf::TRI, NL, NL, NM],
        [crate::mf::TRI, NL, NM, NS],
        [crate::mf::TRI, NM, NS, ZO],
        [crate::mf::TRI, NS, ZO, PS],
        [crate::mf::TRI, ZO, PS, PM],
        [crate::mf::TRI, PS, PM, PL],
        [crate::mf::TRI, PM, PL, PL],
    ];
    let NL: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PL: float = 3.0;
    let mec = [
        [crate::mf::TRI, NL, NL, NM],
        [crate::mf::TRI, NL, NM, NS],
        [crate::mf::TRI, NM, NS, ZO],
        [crate::mf::TRI, NS, ZO, PS],
        [crate::mf::TRI, ZO, PS, PM],
        [crate::mf::TRI, PS, PM, PL],
        [crate::mf::TRI, PM, PL, PL],
    ];
    let NL: float = -15.0;
    let NM: float = -10.0;
    let NS: float = -5.0;
    let ZO: float = 0.0;
    let PS: float = 5.0;
    let PM: float = 10.0;
    let PL: float = 15.0;
    let mkp = [
        [NL, NL, NM, NM, NS, ZO, ZO],
        [NL, NL, NM, NS, NS, ZO, PS],
        [NM, NM, NM, NS, ZO, PS, PS],
        [NM, NM, NS, ZO, PS, PM, PM],
        [NS, NS, ZO, PS, PS, PM, PM],
        [NS, ZO, PS, PM, PM, PM, PL],
        [ZO, ZO, PM, PM, PM, PL, PL],
    ];
    let NL: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PL: float = 3.0;
    let mki = [
        [PL, PL, PM, PM, PS, ZO, ZO],
        [PL, PL, PM, PS, PS, ZO, ZO],
        [PL, PM, PS, PS, ZO, NS, NS],
        [PM, PM, PS, ZO, NS, NM, NM],
        [PM, PS, ZO, NS, NS, NM, NL],
        [ZO, ZO, NS, NS, NM, NL, NL],
        [ZO, ZO, NS, NM, NM, NL, NL],
    ];
    let mkd = [
        [NS, PS, PL, PL, PL, PM, NS],
        [NS, PS, PL, PM, PM, PS, ZO],
        [ZO, PS, PM, PM, PS, PS, ZO],
        [ZO, PS, PS, PS, PS, PS, ZO],
        [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
        [NL, NS, NS, NS, NS, NS, NL],
        [NL, NM, NM, NM, NS, NS, NL],
    ];
    let mut a = PID_fuzzy::new(-10.0, 10.0, 0.0);
    assert!(a.pid.mode == crate::pid::INC);
    let mut idx = [0u32; 4];
    let mut val = [0.0; 8];
    a.rule(
        me.len(),
        &me.concat(),
        &mec.concat(),
        &mkp.concat(),
        &mki.concat(),
        &mkd.concat(),
    )
    .buff(&mut idx, &mut val)
    .kpid(10.0, 0.1, 1.0);
    println!("{}", a.outf(1.0, 0.0));
    a.op(op::AND_ALGEBRA).zero();
    {
        let mut out: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut fdb: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut tmp: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut err: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        a.chan(&mut out, &mut fdb, &mut tmp, &mut err);
        a.outp(&[0.1, 0.2, 0.3, 0.4], &[0.0, 0.0, 0.0, 0.0]);
        println!("{:?}", out);
    }
}
