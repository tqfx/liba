//! trapezoidal velocity profile trajectory

use crate::float;

/// trapezoidal velocity profile trajectory
#[repr(C)]
pub struct traptraj {
    /// acceleration before constant velocity
    pub ac: float,
    /// acceleration after constant velocity
    pub de: float,
    /// time period of increased velocity
    pub ta: float,
    /// displacement as velocity increases
    pub qa: float,
    /// time period of constant velocity
    pub tc: float,
    /// displacement at constant velocity
    pub qc: float,
    /// time period of decreased velocity
    pub td: float,
    /// displacement as velocity decreases
    pub qd: float,
    /// initial velocity
    pub vs: float,
    /// constant velocity
    pub vc: float,
    /// final velocity
    pub ve: float,
}

extern "C" {
    fn a_traptraj_gen(
        ctx: *mut traptraj,
        qm: float,
        vm: float,
        ac: float,
        de: float,
        vs: float,
        ve: float,
    ) -> float;
    fn a_traptraj_pos(ctx: *const traptraj, dt: float) -> float;
    fn a_traptraj_vel(ctx: *const traptraj, dt: float) -> float;
    fn a_traptraj_acc(ctx: *const traptraj, dt: float) -> float;
}

impl traptraj {
    /// initialize for trapezoidal velocity profile trajectory
    #[inline(always)]
    pub fn new(qm: float, vm: float, ac: float, de: float, vs: float, ve: float) -> Self {
        let mut ctx: Self = Self {
            ac: 0.0,
            de: 0.0,
            ta: 0.0,
            qa: 0.0,
            tc: 0.0,
            qc: 0.0,
            td: 0.0,
            qd: 0.0,
            vs: 0.0,
            vc: 0.0,
            ve: 0.0,
        };
        unsafe { a_traptraj_gen(&mut ctx, qm, vm, ac, de, vs, ve) };
        ctx
    }

    /// generate for trapezoidal velocity profile trajectory
    #[inline(always)]
    pub fn gen(
        &mut self,
        qm: float,
        vm: float,
        ac: float,
        de: float,
        vs: float,
        ve: float,
    ) -> float {
        unsafe { a_traptraj_gen(self, qm, vm, ac, de, vs, ve) }
    }

    /// calculate for trapezoidal velocity profile trajectory position
    #[inline(always)]
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_traptraj_pos(self, dt) }
    }

    /// calculate for trapezoidal velocity profile trajectory velocity
    #[inline(always)]
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_traptraj_vel(self, dt) }
    }

    /// calculate for trapezoidal velocity profile trajectory acceleration
    #[inline(always)]
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_traptraj_acc(self, dt) }
    }
}

#[test]
fn traptraj() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a = crate::traptraj::traptraj::new(10.0, 2.0, 2.0, -2.0, 0.0, 0.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        std::println!("[{}, {}, {}]", pos, vel, acc);
    }
}
