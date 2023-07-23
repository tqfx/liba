//! proportional integral derivative controller

use crate::float;
use crate::uint;
use crate::Float;

/// turn off PID controller
pub const OFF: uint = 0;
/// positional PID controller
pub const POS: uint = 1;
/// incremental PID controller
pub const INC: uint = 2;

/// proportional integral derivative controller
#[repr(C)]
pub struct pid {
    /// proportional constant
    pub kp: float,
    /// integral constant
    pub ki: float,
    /// derivative constant
    pub kd: float,
    /// maximum integral output
    pub summax: float,
    /// maximum output
    pub outmax: float,
    /// minimum output
    pub outmin: float,
    /// controller output
    pub out: Float,
    /// cache feedback
    pub fdb: Float,
    /// cache variable
    pub(crate) tmp: Float,
    /// cache error
    pub err: Float,
    /// channel
    pub chan: uint,
    /// mode
    pub mode: uint,
}

extern "C" {
    fn a_pid_chan(
        ctx: *mut pid,
        num: uint,
        out: *mut float,
        fdb: *mut float,
        tmp: *mut float,
        err: *mut float,
    );
    fn a_pid_kpid(ctx: *mut pid, kp: float, ki: float, kd: float);
    fn a_pid_outf(ctx: *mut pid, set: float, fdb: float) -> float;
    fn a_pid_outp(ctx: *const pid, set: *const float, fdb: *const float) -> *const float;
    fn a_pid_zero(ctx: *mut pid);
}

impl pid {
    /// initialize function for PID controller
    pub fn new(min: float, max: float, sum: float) -> Self {
        Self {
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            summax: sum,
            outmax: max,
            outmin: min,
            out: Float { f: 0.0 },
            fdb: Float { f: 0.0 },
            tmp: Float { f: 0.0 },
            err: Float { f: 0.0 },
            chan: 0,
            mode: if sum != 0.0 { POS } else { INC },
        }
    }

    /// set buffer for multichannel PID controller
    pub fn chan(
        &mut self,
        out: &mut [float],
        fdb: &mut [float],
        tmp: &mut [float],
        err: &mut [float],
    ) -> &mut Self {
        unsafe {
            a_pid_chan(
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

    /// set proportional integral derivative constant for PID controller
    pub fn kpid(&mut self, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_kpid(self, kp, ki, kd) };
        self
    }

    /// calculate function for PID controller
    pub fn outf(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_outf(self, set, fdb) }
    }
    /// calculate function for multichannel PID controller
    pub fn outp(&self, set: &[float], fdb: &[float]) -> &[float] {
        unsafe {
            core::slice::from_raw_parts(
                a_pid_outp(self, set.as_ptr(), fdb.as_ptr()),
                self.chan as usize,
            )
        }
    }

    /// zero clear function for PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_zero(self) };
        self
    }
}

#[test]
fn pid() {
    extern crate std;
    {
        let mut a = crate::pid::pid::new(-10.0, 10.0, 10.0);
        std::println!("{}", a.kpid(10.0, 0.1, 1.0).outf(1.0, 0.0));
        assert!(a.mode == crate::pid::POS);
    }
    {
        let mut a = crate::pid::pid::new(-10.0, 10.0, 0.0);
        std::println!("{}", a.kpid(10.0, 0.1, 1.0).outf(1.0, 0.0));
        assert!(a.mode == crate::pid::INC);
    }
    let mut a = crate::pid::pid::new(-10.0, 10.0, 0.0);
    a.kpid(10.0, 0.1, 1.0).outf(1.0, 0.0);
    a.zero();
    {
        let mut out: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut fdb: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut tmp: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut err: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        a.chan(&mut out, &mut fdb, &mut tmp, &mut err);
        std::println!("{:?}", a.outp(&[0.1, 0.2, 0.3, 0.4], &[0.0, 0.0, 0.0, 0.0]));
    }
}

/// fuzzy PID controller operator
pub mod fuzzy {
    use crate::uint;
    /// sqrt(a,b)*sqrt(1-(1-a)*(1-b))
    pub const EQU: uint = 0;
    /// min(a,b)
    pub const CAP: uint = 1;
    /// a*b
    pub const CAP_ALGEBRA: uint = 2;
    /// max(a+b-1,0)
    pub const CAP_BOUNDED: uint = 3;
    /// max(a,b)
    pub const CUP: uint = 4;
    /// a+b-a*b
    pub const CUP_ALGEBRA: uint = 5;
    /// min(a+b,1)
    pub const CUP_BOUNDED: uint = 6;
}

/// fuzzy proportional integral derivative controller
#[repr(C)]
pub struct pid_fuzzy {
    /// proportional integral derivative controller
    pub pid: crate::pid::pid,
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
    fn a_pid_fuzzy_set_op(ctx: *mut pid_fuzzy, op: uint);
    fn a_pid_fuzzy_chan(
        ctx: *mut pid_fuzzy,
        num: uint,
        out: *mut float,
        fdb: *mut float,
        tmp: *mut float,
        err: *mut float,
    );
    fn a_pid_fuzzy_rule(
        ctx: *mut pid_fuzzy,
        num: uint,
        me: *const float,
        mec: *const float,
        mkp: *const float,
        mki: *const float,
        mkd: *const float,
    );
    fn a_pid_fuzzy_kpid(ctx: *mut pid_fuzzy, kp: float, ki: float, kd: float);
    fn a_pid_fuzzy_buff(ctx: *mut pid_fuzzy, idx: *mut uint, val: *mut float);
    fn a_pid_fuzzy_outf(ctx: *mut pid_fuzzy, set: float, fdb: float) -> float;
    fn a_pid_fuzzy_outp(ctx: *mut pid_fuzzy, set: *const float, fdb: *const float) -> *const float;
    fn a_pid_fuzzy_zero(ctx: *mut pid_fuzzy);
}

impl pid_fuzzy {
    /// initialize function for fuzzy PID controller
    pub fn new(min: float, max: float, sum: float) -> Self {
        pid_fuzzy {
            pid: crate::pid::pid::new(min, max, sum),
            me: core::ptr::null(),
            mec: core::ptr::null(),
            mkp: core::ptr::null(),
            mki: core::ptr::null(),
            mkd: core::ptr::null(),
            idx: core::ptr::null_mut(),
            val: core::ptr::null_mut(),
            op: unsafe { a_pid_fuzzy_op(fuzzy::EQU as uint) },
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
    pub fn op(&mut self, op: uint) -> &mut Self {
        unsafe { a_pid_fuzzy_set_op(self, op) };
        self
    }

    /// calculate function for fuzzy PID controller
    pub fn outf(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_fuzzy_outf(self, set, fdb) }
    }
    /// calculate function for multichannel fuzzy PID controller
    pub fn outp(&mut self, set: &[float], fdb: &[float]) -> &[float] {
        unsafe {
            core::slice::from_raw_parts(
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
    extern crate std;
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
    let mut a = pid_fuzzy::new(-10.0, 10.0, 0.0);
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
    std::println!("{}", a.outf(1.0, 0.0));
    a.op(crate::pid::fuzzy::EQU).zero();
    {
        let mut out: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut fdb: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut tmp: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut err: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        a.chan(&mut out, &mut fdb, &mut tmp, &mut err);
        std::println!("{:?}", a.outp(&[0.1, 0.2, 0.3, 0.4], &[0.0, 0.0, 0.0, 0.0]));
    }
}

/// single neuron proportional integral derivative controller
#[repr(C)]
pub struct pid_neuron {
    /// proportional integral derivative controller
    pub pid: crate::pid::pid,
    /// error change
    pub ec: Float,
    /// proportional weight
    pub wp: Float,
    /// integral weight
    pub wi: Float,
    /// derivative weight
    pub wd: Float,
    /// proportional coefficient
    pub k: float,
}

extern "C" {
    fn a_pid_neuron_chan(
        ctx: *mut pid_neuron,
        num: uint,
        out: *mut float,
        fdb: *mut float,
        tmp: *mut float,
        err: *mut float,
        ec: *mut float,
        wp: *mut float,
        wi: *mut float,
        wd: *mut float,
    );
    fn a_pid_neuron_kpid(ctx: *mut pid_neuron, k: float, kp: float, ki: float, kd: float);
    fn a_pid_neuron_wpid(ctx: *mut pid_neuron, wp: float, wi: float, wd: float);
    fn a_pid_neuron_outf(ctx: *mut pid_neuron, set: float, fdb: float) -> float;
    fn a_pid_neuron_outp(
        ctx: *const pid_neuron,
        set: *const float,
        fdb: *const float,
    ) -> *const float;
    fn a_pid_neuron_zero(ctx: *mut pid_neuron);
}

impl pid_neuron {
    /// initialize function for single neuron PID controller
    pub fn new(min: float, max: float, sum: float) -> Self {
        pid_neuron {
            pid: crate::pid::pid::new(min, max, sum),
            ec: Float { f: 0.0 },
            wp: Float { f: 0.0 },
            wi: Float { f: 0.0 },
            wd: Float { f: 0.0 },
            k: 0.0,
        }
    }

    /// set buffer for multichannel single neuron PID controller
    #[allow(clippy::too_many_arguments)]
    pub fn chan(
        &mut self,
        out: &mut [float],
        fdb: &mut [float],
        tmp: &mut [float],
        err: &mut [float],
        ec: &mut [float],
        wp: &mut [float],
        wi: &mut [float],
        wd: &mut [float],
    ) -> &mut Self {
        unsafe {
            a_pid_neuron_chan(
                self,
                out.len() as uint,
                out.as_mut_ptr(),
                fdb.as_mut_ptr(),
                tmp.as_mut_ptr(),
                err.as_mut_ptr(),
                ec.as_mut_ptr(),
                wp.as_mut_ptr(),
                wi.as_mut_ptr(),
                wd.as_mut_ptr(),
            )
        };
        self
    }

    /// set proportional integral derivative constant for single neuron PID controller
    pub fn kpid(&mut self, k: float, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_neuron_kpid(self, k, kp, ki, kd) };
        self
    }

    /// set proportional integral derivative weight for single neuron PID controller
    pub fn wpid(&mut self, wp: float, wi: float, wd: float) -> &mut Self {
        unsafe { a_pid_neuron_wpid(self, wp, wi, wd) };
        self
    }

    /// calculate function for single neuron PID controller
    pub fn outf(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_neuron_outf(self, set, fdb) }
    }
    /// calculate function for multichannel single neuron PID controller
    pub fn outp(&self, set: &[float], fdb: &[float]) -> &[float] {
        unsafe {
            core::slice::from_raw_parts(
                a_pid_neuron_outp(self, set.as_ptr(), fdb.as_ptr()),
                self.pid.chan as usize,
            )
        }
    }

    /// zero clear function for single neuron PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_neuron_zero(self) };
        self
    }
}

#[test]
fn pid_neuron() {
    extern crate std;
    let mut a = crate::pid::pid_neuron::new(-10.0, 10.0, 0.0);
    a.kpid(10.0, 1.0, 0.1, 1.0).wpid(1.0, 0.0, 0.0);
    assert!(a.pid.mode == crate::pid::INC);
    std::println!("{}", a.outf(1.0, 0.0));
    a.zero();
    {
        let mut out: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut fdb: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut tmp: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut err: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut ec: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut wp: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut wi: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut wd: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        a.chan(
            &mut out, &mut fdb, &mut tmp, &mut err, &mut ec, &mut wp, &mut wi, &mut wd,
        )
        .wpid(1.0, 0.0, 0.0);
        std::println!("{:?}", a.outp(&[0.1, 0.2, 0.3, 0.4], &[0.0, 0.0, 0.0, 0.0]));
    }
}
