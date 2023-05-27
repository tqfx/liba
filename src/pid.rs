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
    /// sampling time unit(s)
    dt: float,
    /// proportional constant
    kp: float,
    /// integral constant
    ki: float,
    /// derivative constant
    kd: float,
    /// controller output
    pub out: Float,
    /// (integral) output item sum
    pub sum: Float,
    /// cache feedback
    pub fdb: Float,
    /// error change
    pub ec: Float,
    /// error input
    pub e: Float,
    /// minimum output
    pub outmin: float,
    /// maximum output
    pub outmax: float,
    /// maximum integral output
    pub summax: float,
    num: uint,
    reg: uint,
}

extern "C" {
    fn a_pid_off(ctx: *mut PID) -> *mut PID;
    fn a_pid_inc(ctx: *mut PID) -> *mut PID;
    fn a_pid_pos(ctx: *mut PID, max: float) -> *mut PID;
    fn a_pid_kpid(ctx: *mut PID, kp: float, ki: float, kd: float) -> *mut PID;
    fn a_pid_chan(
        ctx: *mut PID,
        num: uint,
        out: *mut float,
        fdb: *mut float,
        sum: *mut float,
        ec: *mut float,
        e: *mut float,
    ) -> *mut PID;
    fn a_pid_outf(ctx: *mut PID, set: float, fdb: float) -> float;
    fn a_pid_outp(ctx: *mut PID, set: *const float, fdb: *const float) -> *const float;
    fn a_pid_zero(ctx: *mut PID) -> *mut PID;
    fn a_pid_num(ctx: *const PID) -> uint;
    fn a_pid_dt(ctx: *const PID) -> float;
    fn a_pid_set_dt(ctx: *mut PID, dt: float);
    fn a_pid_kp(ctx: *const PID) -> float;
    fn a_pid_set_kp(ctx: *mut PID, kp: float);
    fn a_pid_ki(ctx: *const PID) -> float;
    fn a_pid_set_ki(ctx: *mut PID, ki: float);
    fn a_pid_kd(ctx: *const PID) -> float;
    fn a_pid_set_kd(ctx: *mut PID, kd: float);
    fn a_pid_mode(ctx: *const PID) -> uint;
    fn a_pid_set_mode(ctx: *mut PID, mode: uint);
}

impl PID {
    /// initialize function for PID controller, default is turn off
    pub fn new(dt: float, outmin: float, outmax: float) -> Self {
        Self {
            dt,
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            out: Float { f: 0.0 },
            sum: Float { f: 0.0 },
            fdb: Float { f: 0.0 },
            ec: Float { f: 0.0 },
            e: Float { f: 0.0 },
            outmin,
            outmax,
            summax: 0.0,
            reg: OFF,
            num: 0,
        }
    }

    /// initialize function for positional PID controller
    pub fn new_pos(
        dt: float,
        kp: float,
        ki: float,
        kd: float,
        outmin: float,
        outmax: float,
        summax: float,
    ) -> Self {
        Self {
            dt,
            kp,
            ki: ki * dt,
            kd: kd / dt,
            out: Float { f: 0.0 },
            sum: Float { f: 0.0 },
            fdb: Float { f: 0.0 },
            ec: Float { f: 0.0 },
            e: Float { f: 0.0 },
            outmin,
            outmax,
            summax,
            reg: POS,
            num: 0,
        }
    }

    /// initialize function for incremental PID controller
    pub fn new_inc(
        dt: float,
        kp: float,
        ki: float,
        kd: float,
        outmin: float,
        outmax: float,
    ) -> Self {
        Self {
            dt,
            kp,
            ki: ki * dt,
            kd: kd / dt,
            out: Float { f: 0.0 },
            sum: Float { f: 0.0 },
            fdb: Float { f: 0.0 },
            ec: Float { f: 0.0 },
            e: Float { f: 0.0 },
            outmin,
            outmax,
            summax: 0.0,
            reg: INC,
            num: 0,
        }
    }

    /// turn off PID controller
    pub fn off(&mut self) -> &mut Self {
        unsafe { a_pid_off(self).as_mut().unwrap_unchecked() }
    }

    /// incremental PID controller
    pub fn inc(&mut self) -> &mut Self {
        unsafe { a_pid_inc(self).as_mut().unwrap_unchecked() }
    }

    /// positional PID controller
    pub fn pos(&mut self, max: float) -> &mut Self {
        unsafe { a_pid_pos(self, max).as_mut().unwrap_unchecked() }
    }

    /// set proportional integral derivative constant for PID controller
    pub fn kpid(&mut self, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_kpid(self, kp, ki, kd).as_mut().unwrap_unchecked() }
    }

    /// set buffer for multichannel PID controller
    pub fn chan(
        &mut self,
        out: &mut [float],
        fdb: &mut [float],
        sum: &mut [float],
        ec: &mut [float],
        e: &mut [float],
    ) -> &mut Self {
        unsafe {
            a_pid_chan(
                self,
                out.len() as uint,
                out.as_mut_ptr(),
                fdb.as_mut_ptr(),
                sum.as_mut_ptr(),
                ec.as_mut_ptr(),
                e.as_mut_ptr(),
            )
            .as_mut()
            .unwrap_unchecked()
        }
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
                a_pid_num(self) as usize,
            )
        }
    }

    /// zero function for PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_zero(self).as_mut().unwrap_unchecked() }
    }

    /// get sampling time unit(s) for PID controller
    pub fn dt(&self) -> float {
        unsafe { a_pid_dt(self) }
    }
    /// set sampling time unit(s) for PID controller
    pub fn set_dt(&mut self, dt: float) -> &mut Self {
        unsafe { a_pid_set_dt(self, dt) };
        self
    }

    /// get proportional constant for PID controller
    pub fn kp(&self) -> float {
        unsafe { a_pid_kp(self) }
    }
    /// set proportional constant for PID controller
    pub fn set_kp(&mut self, kp: float) -> &mut Self {
        unsafe { a_pid_set_kp(self, kp) };
        self
    }

    /// get integral constant for PID controller
    pub fn ki(&self) -> float {
        unsafe { a_pid_ki(self) }
    }
    /// set integral constant for PID controller
    pub fn set_ki(&mut self, ki: float) -> &mut Self {
        unsafe { a_pid_set_ki(self, ki) };
        self
    }

    /// get derivative constant for PID controller
    pub fn kd(&self) -> float {
        unsafe { a_pid_kd(self) }
    }
    /// set derivative constant for PID controller
    pub fn set_kd(&mut self, kd: float) -> &mut Self {
        unsafe { a_pid_set_kd(self, kd) };
        self
    }

    /// get mode for PID controller
    pub fn mode(&self) -> uint {
        unsafe { a_pid_mode(self) }
    }
    /// set mode for PID controller
    pub fn set_mode(&mut self, mode: uint) -> &mut Self {
        unsafe { a_pid_set_mode(self, mode) };
        self
    }
}

#[test]
fn pid() {
    {
        let mut a = crate::PID::new_pos(0.1, 10.0, 0.1, 1.0, -10.0, 10.0, 10.0);
        println!("{}", a.outf(1.0, 0.0));
    }
    {
        let mut a = crate::PID::new_inc(0.1, 10.0, 0.1, 1.0, -10.0, 10.0);
        println!("{}", a.outf(1.0, 0.0));
    }
    let mut a = crate::PID::new(1.0, -10.0, 10.0);
    a.kpid(10.0, 0.1, 1.0).pos(10.0).off().inc().set_dt(0.1);
    assert!(a.mode() == crate::pid::INC);
    println!("{}", a.outf(1.0, 0.0));
    a.zero();
    {
        let mut out: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut fdb: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut sum: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut ec: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut e: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        a.chan(&mut out, &mut fdb, &mut sum, &mut ec, &mut e);
        a.outp(&[0.1, 0.2, 0.3, 0.4], &[0.0, 0.0, 0.0, 0.0]);
        println!("{:?}", out);
    }
}
