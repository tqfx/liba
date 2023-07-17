//! polynomial trajectory

use crate::float;

/// cubic polynomial trajectory
#[repr(C)]
pub struct polytrack3 {
    /// quantity
    k: [float; 4],
}

extern "C" {
    fn a_polytrack3_gen(
        ctx: *mut polytrack3,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
    );
    fn a_polytrack3_pos(ctx: *const polytrack3, dt: float) -> float;
    fn a_polytrack3_vel(ctx: *const polytrack3, dt: float) -> float;
    fn a_polytrack3_acc(ctx: *const polytrack3, dt: float) -> float;
    fn a_polytrack3_out(ctx: *const polytrack3, dt: float, out: *mut [float; 3]);
}

impl polytrack3 {
    /// initialize function for cubic polynomial trajectory
    pub fn new(t0: float, t1: float, q0: float, q1: float, v0: float, v1: float) -> Self {
        let mut ctx: Self = Self { k: [0.0; 4] };
        unsafe { a_polytrack3_gen(&mut ctx, t0, t1, q0, q1, v0, v1) };
        ctx
    }

    /// generation function for cubic polynomial trajectory
    pub fn gen(
        &mut self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
    ) -> &mut Self {
        unsafe { a_polytrack3_gen(self, t0, t1, q0, q1, v0, v1) };
        self
    }

    /// calculate function for cubic polynomial trajectory
    pub fn out(&mut self, dt: float) -> [float; 3] {
        let mut out: [float; 3] = [0.0; 3];
        unsafe { a_polytrack3_out(self, dt, &mut out) };
        out
    }

    /// calculate function for cubic polynomial trajectory position
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_polytrack3_pos(self, dt) }
    }

    /// calculate function for cubic polynomial trajectory velocity
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_polytrack3_vel(self, dt) }
    }

    /// calculate function for cubic polynomial trajectory acceleration
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_polytrack3_acc(self, dt) }
    }
}

#[test]
fn polytrack3() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a = crate::polytrack::polytrack3::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        let out = a.out(dt);
        std::println!("[{}, {}, {}]", pos, vel, acc);
        std::println!("{:?}", out);
    }
}

/// quintic polynomial trajectory
#[repr(C)]
pub struct polytrack5 {
    /// quantity
    k: [float; 6],
}

extern "C" {
    fn a_polytrack5_gen(
        ctx: *mut polytrack5,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
    );
    fn a_polytrack5_pos(ctx: *const polytrack5, dt: float) -> float;
    fn a_polytrack5_vel(ctx: *const polytrack5, dt: float) -> float;
    fn a_polytrack5_acc(ctx: *const polytrack5, dt: float) -> float;
    fn a_polytrack5_out(ctx: *const polytrack5, dt: float, out: *mut [float; 3]);
}

impl polytrack5 {
    /// initialize function for quintic polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    pub fn new(
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
    ) -> Self {
        let mut ctx: Self = Self { k: [0.0; 6] };
        unsafe { a_polytrack5_gen(&mut ctx, t0, t1, q0, q1, v0, v1, a0, a1) };
        ctx
    }

    /// generation function for quintic polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    pub fn gen(
        &mut self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
    ) -> &mut Self {
        unsafe { a_polytrack5_gen(self, t0, t1, q0, q1, v0, v1, a0, a1) };
        self
    }

    /// calculate function for quintic polynomial trajectory
    pub fn out(&mut self, dt: float) -> [float; 3] {
        let mut out: [float; 3] = [0.0; 3];
        unsafe { a_polytrack5_out(self, dt, &mut out) };
        out
    }

    /// calculate function for quintic polynomial trajectory position
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_polytrack5_pos(self, dt) }
    }

    /// calculate function for quintic polynomial trajectory velocity
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_polytrack5_vel(self, dt) }
    }

    /// calculate function for quintic polynomial trajectory acceleration
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_polytrack5_acc(self, dt) }
    }
}

#[test]
fn polytrack5() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a = crate::polytrack::polytrack5::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        let out = a.out(dt);
        std::println!("[{}, {}, {}]", pos, vel, acc);
        std::println!("{:?}", out);
    }
}

/// hepta polynomial trajectory
#[repr(C)]
pub struct polytrack7 {
    /// quantity
    k: [float; 8],
}

extern "C" {
    fn a_polytrack7_gen(
        ctx: *mut polytrack7,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
        j0: float,
        j1: float,
    );
    fn a_polytrack7_pos(ctx: *const polytrack7, dt: float) -> float;
    fn a_polytrack7_vel(ctx: *const polytrack7, dt: float) -> float;
    fn a_polytrack7_acc(ctx: *const polytrack7, dt: float) -> float;
    fn a_polytrack7_jer(ctx: *const polytrack7, dt: float) -> float;
    fn a_polytrack7_out(ctx: *const polytrack7, dt: float, out: *mut [float; 4]);
}

impl polytrack7 {
    /// initialize function for hepta polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    pub fn new(
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
        j0: float,
        j1: float,
    ) -> Self {
        let mut ctx: Self = Self { k: [0.0; 8] };
        unsafe { a_polytrack7_gen(&mut ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) };
        ctx
    }

    /// generation function for hepta polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    pub fn gen(
        &mut self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
        j0: float,
        j1: float,
    ) -> &mut Self {
        unsafe { a_polytrack7_gen(self, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) };
        self
    }

    /// calculate function for hepta polynomial trajectory
    pub fn out(&mut self, dt: float) -> [float; 4] {
        let mut out: [float; 4] = [0.0; 4];
        unsafe { a_polytrack7_out(self, dt, &mut out) };
        out
    }

    /// calculate function for hepta polynomial trajectory position
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_polytrack7_pos(self, dt) }
    }

    /// calculate function for hepta polynomial trajectory velocity
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_polytrack7_vel(self, dt) }
    }

    /// calculate function for hepta polynomial trajectory acceleration
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_polytrack7_acc(self, dt) }
    }

    /// calculate function for hepta polynomial trajectory jerk
    pub fn jer(&mut self, dt: float) -> float {
        unsafe { a_polytrack7_jer(self, dt) }
    }
}

#[test]
fn polytrack7() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a =
            crate::polytrack::polytrack7::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        let jer = a.jer(dt);
        let out = a.out(dt);
        std::println!("[{}, {}, {}, {}]", pos, vel, acc, jer);
        std::println!("{:?}", out);
    }
}
