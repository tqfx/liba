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
    AND = 0b00010000,
    /// l*r
    AND_ALGEBRA = 0b00010100,
    /// max(l,r)
    AND_BOUNDED = 0b00011000,
    /// max(l,r)
    OR = 0b00100000,
    /// l+r-l*r
    OR_ALGEBRA = 0b00100100,
    /// min(l,r)
    OR_BOUNDED = 0b00101000,
}

/// fuzzy proportional integral derivative controller
#[repr(C)]
pub struct PID_fuzzy {
    /// proportional integral derivative controller
    pub pid: PID,
    me: *const float,
    mec: *const float,
    mkp: *const float,
    mki: *const float,
    mkd: *const float,
    idx: *mut uint,
    val: *mut float,
    /// fuzzy relational operator
    op: Option<extern "C" fn(float, float) -> float>,
    /// base proportional constant
    pub kp: float,
    /// base integral constant
    pub ki: float,
    /// base derivative constant
    pub kd: float,
}

extern "C" {
    fn a_pid_fuzzy_off(ctx: *mut PID_fuzzy) -> *mut PID_fuzzy;
    fn a_pid_fuzzy_inc(ctx: *mut PID_fuzzy) -> *mut PID_fuzzy;
    fn a_pid_fuzzy_pos(ctx: *mut PID_fuzzy, max: float) -> *mut PID_fuzzy;
    fn a_pid_fuzzy_kpid(ctx: *mut PID_fuzzy, kp: float, ki: float, kd: float) -> *mut PID_fuzzy;
    fn a_pid_fuzzy_buff(ctx: *mut PID_fuzzy, idx: *mut uint, val: *mut float) -> *mut PID_fuzzy;
    fn a_pid_fuzzy_chan(
        ctx: *mut PID_fuzzy,
        num: uint,
        out: *mut float,
        fdb: *mut float,
        tmp: *mut float,
        err: *mut float,
    ) -> *mut PID_fuzzy;
    fn a_pid_fuzzy_base(
        ctx: *mut PID_fuzzy,
        num: uint,
        me: *const float,
        mec: *const float,
        mkp: *const float,
        mki: *const float,
        mkd: *const float,
    ) -> *mut PID_fuzzy;
    fn a_pid_fuzzy_init(
        ctx: *mut PID_fuzzy,
        dt: float,
        col: uint,
        me: *const float,
        mec: *const float,
        mkp: *const float,
        mki: *const float,
        mkd: *const float,
        min: float,
        max: float,
    ) -> *mut PID_fuzzy;
    fn a_pid_fuzzy_outf(ctx: *mut PID_fuzzy, set: float, fdb: float) -> float;
    fn a_pid_fuzzy_outp(ctx: *mut PID_fuzzy, set: *const float, fdb: *const float) -> *const float;
    fn a_pid_fuzzy_zero(ctx: *mut PID_fuzzy) -> *mut PID_fuzzy;
    fn a_pid_fuzzy_set_op(ctx: *mut PID_fuzzy, op: uint);
    fn a_pid_num(ctx: *const PID) -> uint;
}

impl PID_fuzzy {
    /// initialize function for fuzzy PID controller, default is turn off
    #[allow(clippy::too_many_arguments)]
    pub fn new(
        dt: float,
        col: usize,
        me: &[float],
        mec: &[float],
        mkp: &[float],
        mki: &[float],
        mkd: &[float],
        min: float,
        max: float,
    ) -> Self {
        let mut ctx: Self = Self {
            pid: PID::new(dt, min, max),
            me: std::ptr::null(),
            mec: std::ptr::null(),
            mkp: std::ptr::null(),
            mki: std::ptr::null(),
            mkd: std::ptr::null(),
            idx: std::ptr::null_mut(),
            val: std::ptr::null_mut(),
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            op: None,
        };
        unsafe {
            a_pid_fuzzy_init(
                &mut ctx,
                dt,
                col as uint,
                me.as_ptr(),
                mec.as_ptr(),
                mkp.as_ptr(),
                mki.as_ptr(),
                mkd.as_ptr(),
                min,
                max,
            );
        };
        ctx
    }

    /// turn off fuzzy PID controller
    pub fn off(&mut self) -> &mut Self {
        unsafe { a_pid_fuzzy_off(self).as_mut().unwrap_unchecked() }
    }

    /// incremental fuzzy PID controller
    pub fn inc(&mut self) -> &mut Self {
        unsafe { a_pid_fuzzy_inc(self).as_mut().unwrap_unchecked() }
    }

    /// positional fuzzy PID controller
    pub fn pos(&mut self, max: float) -> &mut Self {
        unsafe { a_pid_fuzzy_pos(self, max).as_mut().unwrap_unchecked() }
    }

    /// set proportional integral derivative constant for fuzzy PID controller
    pub fn kpid(&mut self, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe {
            a_pid_fuzzy_kpid(self, kp, ki, kd)
                .as_mut()
                .unwrap_unchecked()
        }
    }

    /// set buffer for fuzzy PID controller
    pub fn buff(&mut self, idx: &mut [u32], val: &mut [float]) -> &mut Self {
        unsafe {
            a_pid_fuzzy_buff(self, idx.as_mut_ptr(), val.as_mut_ptr())
                .as_mut()
                .unwrap_unchecked()
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
            .as_mut()
            .unwrap_unchecked()
        }
    }

    /// set rule base for fuzzy PID controller
    pub fn base(
        &mut self,
        col: usize,
        me: &[float],
        mec: &[float],
        mkp: &[float],
        mki: &[float],
        mkd: &[float],
    ) -> &mut Self {
        unsafe {
            a_pid_fuzzy_base(
                self,
                col as uint,
                me.as_ptr(),
                mec.as_ptr(),
                mkp.as_ptr(),
                mki.as_ptr(),
                mkd.as_ptr(),
            )
            .as_mut()
            .unwrap_unchecked()
        }
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
                a_pid_num(&self.pid) as usize,
            )
        }
    }

    /// zero clear function for fuzzy PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_fuzzy_zero(self).as_mut().unwrap_unchecked() }
    }

    /// set fuzzy relational operator for fuzzy PID controller
    pub fn set_op(&mut self, op: op) -> &mut Self {
        unsafe { a_pid_fuzzy_set_op(self, op as uint) };
        self
    }

    /// get sampling time unit(s) for fuzzy PID controller
    pub fn dt(&self) -> uint {
        self.pid.mode()
    }
    /// set sampling time unit(s) for fuzzy PID controller
    pub fn set_dt(&mut self, dt: float) -> &mut Self {
        self.pid.set_dt(dt);
        self
    }

    /// get mode for fuzzy PID controller
    pub fn mode(&self) -> uint {
        self.pid.mode()
    }
    /// set mode for PID controller
    pub fn set_mode(&mut self, mode: uint) -> &mut Self {
        self.pid.set_mode(mode);
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
    let mut a = crate::PID_fuzzy::new(
        1.0,
        me.len(),
        &me.concat(),
        &mec.concat(),
        &mkp.concat(),
        &mki.concat(),
        &mkd.concat(),
        -10.0,
        10.0,
    );
    a.base(
        me.len(),
        &me.concat(),
        &mec.concat(),
        &mkp.concat(),
        &mki.concat(),
        &mkd.concat(),
    );
    a.kpid(10.0, 0.1, 1.0);
    let mut idx = [0u32; 4];
    let mut val = [0.0; 8];
    a.buff(&mut idx, &mut val);
    a.pos(10.0).off().inc().set_dt(0.1);
    assert!(a.mode() == crate::pid::INC);
    println!("{}", a.outf(1.0, 0.0));
    a.set_op(op::AND_ALGEBRA).zero();
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
