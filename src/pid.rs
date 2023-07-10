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
pub struct PID {
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
        ctx: *mut PID,
        num: uint,
        out: *mut float,
        fdb: *mut float,
        tmp: *mut float,
        err: *mut float,
    ) -> *mut PID;
    fn a_pid_kpid(ctx: *mut PID, kp: float, ki: float, kd: float) -> *mut PID;
    fn a_pid_outf(ctx: *mut PID, set: float, fdb: float) -> float;
    fn a_pid_outp(ctx: *mut PID, set: *const float, fdb: *const float) -> *const float;
    fn a_pid_zero(ctx: *mut PID) -> *mut PID;
}

impl PID {
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
    pub fn outp(&mut self, set: &[float], fdb: &[float]) -> &[float] {
        unsafe {
            std::slice::from_raw_parts(
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
    {
        let mut a = crate::PID::new(-10.0, 10.0, 10.0);
        println!("{}", a.kpid(10.0, 0.1, 1.0).outf(1.0, 0.0));
        assert!(a.mode == crate::pid::POS);
    }
    {
        let mut a = crate::PID::new(-10.0, 10.0, 0.0);
        println!("{}", a.kpid(10.0, 0.1, 1.0).outf(1.0, 0.0));
        assert!(a.mode == crate::pid::INC);
    }
    let mut a = crate::PID::new(-10.0, 10.0, 0.0);
    a.kpid(10.0, 0.1, 1.0).outf(1.0, 0.0);
    a.zero();
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
