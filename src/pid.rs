//! proportional integral derivative controller

use crate::real;
use crate::uint;
use crate::Real;

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
    dt: real,
    /// proportional constant
    kp: real,
    /// integral constant
    ki: real,
    /// derivative constant
    kd: real,
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
    pub outmin: real,
    /// maximum output
    pub outmax: real,
    /// maximum integral output
    pub summax: real,
    num: uint,
    reg: uint,
}

extern "C" {
    fn a_pid_off(ctx: *mut PID) -> *mut PID;
    fn a_pid_inc(ctx: *mut PID) -> *mut PID;
    fn a_pid_pos(ctx: *mut PID, max: real) -> *mut PID;
    fn a_pid_kpid(ctx: *mut PID, kp: real, ki: real, kd: real) -> *mut PID;
    fn a_pid_chan(
        ctx: *mut PID,
        num: uint,
        out: *mut real,
        fdb: *mut real,
        sum: *mut real,
        ec: *mut real,
        e: *mut real,
    ) -> *mut PID;
    fn a_pid_outf(ctx: *mut PID, set: real, fdb: real) -> real;
    fn a_pid_outp(ctx: *mut PID, set: *const real, fdb: *const real) -> *const real;
    fn a_pid_zero(ctx: *mut PID) -> *mut PID;
    fn a_pid_num(ctx: *const PID) -> uint;
    fn a_pid_dt(ctx: *const PID) -> real;
    fn a_pid_set_dt(ctx: *mut PID, dt: real);
    fn a_pid_kp(ctx: *const PID) -> real;
    fn a_pid_set_kp(ctx: *mut PID, kp: real);
    fn a_pid_ki(ctx: *const PID) -> real;
    fn a_pid_set_ki(ctx: *mut PID, ki: real);
    fn a_pid_kd(ctx: *const PID) -> real;
    fn a_pid_set_kd(ctx: *mut PID, kd: real);
    fn a_pid_mode(ctx: *const PID) -> uint;
    fn a_pid_set_mode(ctx: *mut PID, mode: uint);
}

impl PID {
    /// initialize function for PID controller, default is turn off
    pub fn new(dt: real, outmin: real, outmax: real) -> Self {
        Self {
            dt,
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            out: Real { f: 0.0 },
            sum: Real { f: 0.0 },
            fdb: Real { f: 0.0 },
            ec: Real { f: 0.0 },
            e: Real { f: 0.0 },
            outmin,
            outmax,
            summax: 0.0,
            reg: OFF,
            num: 0,
        }
    }

    /// initialize function for positional PID controller
    pub fn new_pos(
        dt: real,
        kp: real,
        ki: real,
        kd: real,
        outmin: real,
        outmax: real,
        summax: real,
    ) -> Self {
        Self {
            dt,
            kp,
            ki: ki * dt,
            kd: kd / dt,
            out: Real { f: 0.0 },
            sum: Real { f: 0.0 },
            fdb: Real { f: 0.0 },
            ec: Real { f: 0.0 },
            e: Real { f: 0.0 },
            outmin,
            outmax,
            summax,
            reg: POS,
            num: 0,
        }
    }

    /// initialize function for incremental PID controller
    pub fn new_inc(dt: real, kp: real, ki: real, kd: real, outmin: real, outmax: real) -> Self {
        Self {
            dt,
            kp,
            ki: ki * dt,
            kd: kd / dt,
            out: Real { f: 0.0 },
            sum: Real { f: 0.0 },
            fdb: Real { f: 0.0 },
            ec: Real { f: 0.0 },
            e: Real { f: 0.0 },
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
    pub fn pos(&mut self, max: real) -> &mut Self {
        unsafe { a_pid_pos(self, max).as_mut().unwrap_unchecked() }
    }

    /// set proportional integral derivative constant for PID controller
    pub fn kpid(&mut self, kp: real, ki: real, kd: real) -> &mut Self {
        unsafe { a_pid_kpid(self, kp, ki, kd).as_mut().unwrap_unchecked() }
    }

    /// set buffer for multichannel PID controller
    pub fn chan(
        &mut self,
        out: &mut [real],
        fdb: &mut [real],
        sum: &mut [real],
        ec: &mut [real],
        e: &mut [real],
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
    pub fn outf(&mut self, set: real, fdb: real) -> real {
        unsafe { a_pid_outf(self, set, fdb) }
    }
    /// calculate function for multichannel PID controller
    pub fn outp(&mut self, set: &[real], fdb: &[real]) -> &[real] {
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
    pub fn dt(&self) -> real {
        unsafe { a_pid_dt(self) }
    }
    /// set sampling time unit(s) for PID controller
    pub fn set_dt(&mut self, dt: real) -> &mut Self {
        unsafe { a_pid_set_dt(self, dt) };
        self
    }

    /// get proportional constant for PID controller
    pub fn kp(&self) -> real {
        unsafe { a_pid_kp(self) }
    }
    /// set proportional constant for PID controller
    pub fn set_kp(&mut self, kp: real) -> &mut Self {
        unsafe { a_pid_set_kp(self, kp) };
        self
    }

    /// get integral constant for PID controller
    pub fn ki(&self) -> real {
        unsafe { a_pid_ki(self) }
    }
    /// set integral constant for PID controller
    pub fn set_ki(&mut self, ki: real) -> &mut Self {
        unsafe { a_pid_set_ki(self, ki) };
        self
    }

    /// get derivative constant for PID controller
    pub fn kd(&self) -> real {
        unsafe { a_pid_kd(self) }
    }
    /// set derivative constant for PID controller
    pub fn set_kd(&mut self, kd: real) -> &mut Self {
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
        let mut out: [real; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut fdb: [real; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut sum: [real; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut ec: [real; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut e: [real; 4] = [0.0, 0.0, 0.0, 0.0];
        a.chan(&mut out, &mut fdb, &mut sum, &mut ec, &mut e);
        a.outp(&[0.1, 0.2, 0.3, 0.4], &[0.0, 0.0, 0.0, 0.0]);
        println!("{:?}", out);
    }
}
