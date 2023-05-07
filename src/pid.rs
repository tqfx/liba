//! proportional integral derivative controller

use crate::Real;
use crate::Uint;

/// turn off PID controller
pub const OFF: Uint = 0;
/// positional PID controller
pub const POS: Uint = 1;
/// incremental PID controller
pub const INC: Uint = 2;

/// proportional integral derivative controller
#[repr(C)]
pub struct PID {
    /// sampling time unit(s)
    dt: Real,
    /// proportional constant
    kp: Real,
    /// integral constant
    ki: Real,
    /// derivative constant
    kd: Real,
    /// controller output
    pub out: Real,
    /// (integral) output item sum
    pub sum: Real,
    /// cache feedback
    pub fdb: Real,
    /// error change
    pub ec: Real,
    /// error input
    pub e: Real,
    /// minimum output
    pub outmin: Real,
    /// maximum output
    pub outmax: Real,
    /// maximum integral output
    pub summax: Real,
    num: Uint,
    reg: Uint,
}

extern "C" {
    fn a_pid_off(ctx: *mut PID) -> *mut PID;
    fn a_pid_inc(ctx: *mut PID) -> *mut PID;
    fn a_pid_pos(ctx: *mut PID, max: Real) -> *mut PID;
    fn a_pid_kpid(ctx: *mut PID, kp: Real, ki: Real, kd: Real) -> *mut PID;
    fn a_pid_outv(ctx: *mut PID, set: Real, fdb: Real) -> Real;
    fn a_pid_zero(ctx: *mut PID) -> *mut PID;
    fn a_pid_set_dt(ctx: *mut PID, dt: Real);
    fn a_pid_dt(ctx: *const PID) -> Real;
    fn a_pid_set_kp(ctx: *mut PID, kp: Real);
    fn a_pid_kp(ctx: *const PID) -> Real;
    fn a_pid_set_ki(ctx: *mut PID, ki: Real);
    fn a_pid_ki(ctx: *const PID) -> Real;
    fn a_pid_set_kd(ctx: *mut PID, kd: Real);
    fn a_pid_kd(ctx: *const PID) -> Real;
    fn a_pid_set_mode(ctx: *mut PID, mode: Uint);
    fn a_pid_mode(ctx: *const PID) -> Uint;
}

impl PID {
    /// initialize function for PID controller, default is turn off
    pub fn new(dt: Real, outmin: Real, outmax: Real) -> Self {
        Self {
            dt,
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            out: 0.0,
            outmin,
            outmax,
            sum: 0.0,
            summax: 0.0,
            e: 0.0,
            ec: 0.0,
            fdb: 0.0,
            reg: OFF,
            num: 0,
        }
    }

    /// initialize function for positional PID controller
    pub fn new_pos(
        dt: Real,
        kp: Real,
        ki: Real,
        kd: Real,
        outmin: Real,
        outmax: Real,
        summax: Real,
    ) -> Self {
        Self {
            dt,
            kp,
            ki,
            kd,
            out: 0.0,
            outmin,
            outmax,
            sum: 0.0,
            summax,
            e: 0.0,
            ec: 0.0,
            fdb: 0.0,
            reg: POS,
            num: 0,
        }
    }

    /// initialize function for incremental PID controller
    pub fn new_inc(dt: Real, kp: Real, ki: Real, kd: Real, outmin: Real, outmax: Real) -> Self {
        Self {
            dt,
            kp,
            ki,
            kd,
            out: 0.0,
            outmin,
            outmax,
            sum: 0.0,
            summax: 0.0,
            e: 0.0,
            ec: 0.0,
            fdb: 0.0,
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
    pub fn pos(&mut self, max: Real) -> &mut Self {
        unsafe { a_pid_pos(self, max).as_mut().unwrap_unchecked() }
    }

    /// set proportional integral derivative constant for PID controller
    pub fn kpid(&mut self, kp: Real, ki: Real, kd: Real) -> &mut Self {
        unsafe { a_pid_kpid(self, kp, ki, kd).as_mut().unwrap_unchecked() }
    }

    /// calculate function for PID controller
    pub fn iter(&mut self, set: Real, fdb: Real) -> Real {
        unsafe { a_pid_outv(self, set, fdb) }
    }

    /// zero function for PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_zero(self).as_mut().unwrap_unchecked() }
    }

    /// get sampling time unit(s) for PID controller
    pub fn dt(&self) -> Real {
        unsafe { a_pid_dt(self) }
    }
    /// set sampling time unit(s) for PID controller
    pub fn set_dt(&mut self, dt: Real) -> &mut Self {
        unsafe { a_pid_set_dt(self, dt) };
        self
    }

    /// get proportional constant for PID controller
    pub fn kp(&self) -> Real {
        unsafe { a_pid_kp(self) }
    }
    /// set proportional constant for PID controller
    pub fn set_kp(&mut self, kp: Real) -> &mut Self {
        unsafe { a_pid_set_kp(self, kp) };
        self
    }

    /// get integral constant for PID controller
    pub fn ki(&self) -> Real {
        unsafe { a_pid_ki(self) }
    }
    /// set integral constant for PID controller
    pub fn set_ki(&mut self, ki: Real) -> &mut Self {
        unsafe { a_pid_set_ki(self, ki) };
        self
    }

    /// get derivative constant for PID controller
    pub fn kd(&self) -> Real {
        unsafe { a_pid_kd(self) }
    }
    /// set derivative constant for PID controller
    pub fn set_kd(&mut self, kd: Real) -> &mut Self {
        unsafe { a_pid_set_kd(self, kd) };
        self
    }

    /// get mode for PID controller
    pub fn mode(&self) -> Uint {
        unsafe { a_pid_mode(self) }
    }
    /// set mode for PID controller
    pub fn set_mode(&mut self, mode: Uint) -> &mut Self {
        unsafe { a_pid_set_mode(self, mode) };
        self
    }
}

#[test]
fn pid() {
    {
        let mut a = crate::PID::new_pos(0.1, 10.0, 0.1, 1.0, -10.0, 10.0, 10.0);
        println!("{}", a.iter(1.0, 0.0));
    }
    {
        let mut a = crate::PID::new_inc(0.1, 10.0, 0.1, 1.0, -10.0, 10.0);
        println!("{}", a.iter(1.0, 0.0));
    }
    let mut a = crate::PID::new(1.0, -10.0, 10.0);
    a.kpid(10.0, 0.1, 1.0);
    a.pos(10.0).off().inc().set_dt(0.1);
    assert!(a.mode() == crate::pid::INC);
    println!("{}", a.iter(1.0, 0.0));
    a.zero();
}
