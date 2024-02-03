//! polynomial trajectory

use crate::float;

/// cubic polynomial trajectory
#[repr(C)]
pub struct polytraj3 {
    /// coefficients of position
    pub q: [float; 4],
    /// coefficients of velocity
    pub v: [float; 3],
    /// coefficients of acceleration
    pub a: [float; 2],
}

extern "C" {
    fn a_polytraj3_gen(ctx: *mut polytraj3, ts: float, q0: float, q1: float, v0: float, v1: float);
    fn a_polytraj3_pos(ctx: *const polytraj3, dt: float) -> float;
    fn a_polytraj3_vel(ctx: *const polytraj3, dt: float) -> float;
    fn a_polytraj3_acc(ctx: *const polytraj3, dt: float) -> float;
}

impl polytraj3 {
    /// initialize for cubic polynomial trajectory
    #[inline(always)]
    pub fn new(ts: float, q0: float, q1: float, v0: float, v1: float) -> Self {
        let mut ctx: Self = Self {
            q: [0.0; 4],
            v: [0.0; 3],
            a: [0.0; 2],
        };
        unsafe { a_polytraj3_gen(&mut ctx, ts, q0, q1, v0, v1) };
        ctx
    }

    /// generate for cubic polynomial trajectory
    #[inline(always)]
    pub fn gen(&mut self, ts: float, q0: float, q1: float, v0: float, v1: float) -> &mut Self {
        unsafe { a_polytraj3_gen(self, ts, q0, q1, v0, v1) };
        self
    }

    /// calculate for cubic polynomial trajectory position
    #[inline(always)]
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_polytraj3_pos(self, dt) }
    }

    /// calculate for cubic polynomial trajectory velocity
    #[inline(always)]
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_polytraj3_vel(self, dt) }
    }

    /// calculate for cubic polynomial trajectory acceleration
    #[inline(always)]
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_polytraj3_acc(self, dt) }
    }
}

#[test]
fn polytraj3() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a = crate::polytraj::polytraj3::new(1.0, 0.0, 1.0, 0.0, 1.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        std::println!("[{}, {}, {}]", pos, vel, acc);
    }
}

/// quintic polynomial trajectory
#[repr(C)]
pub struct polytraj5 {
    /// coefficients of position
    pub q: [float; 6],
    /// coefficients of velocity
    pub v: [float; 5],
    /// coefficients of acceleration
    pub a: [float; 4],
}

extern "C" {
    fn a_polytraj5_gen(
        ctx: *mut polytraj5,
        ts: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
    );
    fn a_polytraj5_pos(ctx: *const polytraj5, dt: float) -> float;
    fn a_polytraj5_vel(ctx: *const polytraj5, dt: float) -> float;
    fn a_polytraj5_acc(ctx: *const polytraj5, dt: float) -> float;
}

impl polytraj5 {
    /// initialize for quintic polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn new(
        ts: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
    ) -> Self {
        let mut ctx: Self = Self {
            q: [0.0; 6],
            v: [0.0; 5],
            a: [0.0; 4],
        };
        unsafe { a_polytraj5_gen(&mut ctx, ts, q0, q1, v0, v1, a0, a1) };
        ctx
    }

    /// generate for quintic polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn gen(
        &mut self,
        ts: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
    ) -> &mut Self {
        unsafe { a_polytraj5_gen(self, ts, q0, q1, v0, v1, a0, a1) };
        self
    }

    /// calculate for quintic polynomial trajectory position
    #[inline(always)]
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_polytraj5_pos(self, dt) }
    }

    /// calculate for quintic polynomial trajectory velocity
    #[inline(always)]
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_polytraj5_vel(self, dt) }
    }

    /// calculate for quintic polynomial trajectory acceleration
    #[inline(always)]
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_polytraj5_acc(self, dt) }
    }
}

#[test]
fn polytraj5() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a = crate::polytraj::polytraj5::new(1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        std::println!("[{}, {}, {}]", pos, vel, acc);
    }
}

/// hepta polynomial trajectory
#[repr(C)]
pub struct polytraj7 {
    /// coefficients of position
    pub q: [float; 8],
    /// coefficients of velocity
    pub v: [float; 7],
    /// coefficients of acceleration
    pub a: [float; 6],
    /// coefficients of jerk
    pub j: [float; 5],
}

extern "C" {
    fn a_polytraj7_gen(
        ctx: *mut polytraj7,
        ts: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
        j0: float,
        j1: float,
    );
    fn a_polytraj7_pos(ctx: *const polytraj7, dt: float) -> float;
    fn a_polytraj7_vel(ctx: *const polytraj7, dt: float) -> float;
    fn a_polytraj7_acc(ctx: *const polytraj7, dt: float) -> float;
    fn a_polytraj7_jer(ctx: *const polytraj7, dt: float) -> float;
}

impl polytraj7 {
    /// initialize for hepta polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn new(
        ts: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
        j0: float,
        j1: float,
    ) -> Self {
        let mut ctx: Self = Self {
            q: [0.0; 8],
            v: [0.0; 7],
            a: [0.0; 6],
            j: [0.0; 5],
        };
        unsafe { a_polytraj7_gen(&mut ctx, ts, q0, q1, v0, v1, a0, a1, j0, j1) };
        ctx
    }

    /// generate for hepta polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn gen(
        &mut self,
        ts: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
        a0: float,
        a1: float,
        j0: float,
        j1: float,
    ) -> &mut Self {
        unsafe { a_polytraj7_gen(self, ts, q0, q1, v0, v1, a0, a1, j0, j1) };
        self
    }

    /// calculate for hepta polynomial trajectory position
    #[inline(always)]
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_polytraj7_pos(self, dt) }
    }

    /// calculate for hepta polynomial trajectory velocity
    #[inline(always)]
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_polytraj7_vel(self, dt) }
    }

    /// calculate for hepta polynomial trajectory acceleration
    #[inline(always)]
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_polytraj7_acc(self, dt) }
    }

    /// calculate for hepta polynomial trajectory jerk
    #[inline(always)]
    pub fn jer(&mut self, dt: float) -> float {
        unsafe { a_polytraj7_jer(self, dt) }
    }
}

#[test]
fn polytraj7() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a = crate::polytraj::polytraj7::new(1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        let jer = a.jer(dt);
        std::println!("[{}, {}, {}, {}]", pos, vel, acc, jer);
    }
}
