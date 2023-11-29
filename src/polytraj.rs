//! polynomial trajectory

use crate::float;

/// cubic polynomial trajectory
#[repr(C)]
pub struct polytraj3 {
    /// coefficients, q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3
    k: [float; 4],
}

extern "C" {
    fn a_polytraj3_gen(
        ctx: *mut polytraj3,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
    );
    fn a_polytraj3_pos(ctx: *const polytraj3, dt: float) -> float;
    fn a_polytraj3_vel(ctx: *const polytraj3, dt: float) -> float;
    fn a_polytraj3_acc(ctx: *const polytraj3, dt: float) -> float;
    fn a_polytraj3_out(ctx: *const polytraj3, dt: float, out: *mut [float; 3]);
}

impl polytraj3 {
    /// initialize for cubic polynomial trajectory
    pub fn new(t0: float, t1: float, q0: float, q1: float, v0: float, v1: float) -> Self {
        let mut ctx: Self = Self { k: [0.0; 4] };
        unsafe { a_polytraj3_gen(&mut ctx, t0, t1, q0, q1, v0, v1) };
        ctx
    }

    /// generate for cubic polynomial trajectory
    pub fn gen(
        &mut self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float,
        v1: float,
    ) -> &mut Self {
        unsafe { a_polytraj3_gen(self, t0, t1, q0, q1, v0, v1) };
        self
    }

    /// calculate for cubic polynomial trajectory
    pub fn out(&mut self, dt: float) -> [float; 3] {
        let mut out: [float; 3] = [0.0; 3];
        unsafe { a_polytraj3_out(self, dt, &mut out) };
        out
    }

    /// calculate for cubic polynomial trajectory position
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_polytraj3_pos(self, dt) }
    }

    /// calculate for cubic polynomial trajectory velocity
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_polytraj3_vel(self, dt) }
    }

    /// calculate for cubic polynomial trajectory acceleration
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_polytraj3_acc(self, dt) }
    }
}

#[test]
fn polytraj3() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a = crate::polytraj::polytraj3::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
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
pub struct polytraj5 {
    /// coefficients, q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3+k_4(t-t_0)^4+k_5(t-t_0)^5
    k: [float; 6],
}

extern "C" {
    fn a_polytraj5_gen(
        ctx: *mut polytraj5,
        t0: float,
        t1: float,
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
    fn a_polytraj5_out(ctx: *const polytraj5, dt: float, out: *mut [float; 3]);
}

impl polytraj5 {
    /// initialize for quintic polynomial trajectory
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
        unsafe { a_polytraj5_gen(&mut ctx, t0, t1, q0, q1, v0, v1, a0, a1) };
        ctx
    }

    /// generate for quintic polynomial trajectory
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
        unsafe { a_polytraj5_gen(self, t0, t1, q0, q1, v0, v1, a0, a1) };
        self
    }

    /// calculate for quintic polynomial trajectory
    pub fn out(&mut self, dt: float) -> [float; 3] {
        let mut out: [float; 3] = [0.0; 3];
        unsafe { a_polytraj5_out(self, dt, &mut out) };
        out
    }

    /// calculate for quintic polynomial trajectory position
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_polytraj5_pos(self, dt) }
    }

    /// calculate for quintic polynomial trajectory velocity
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_polytraj5_vel(self, dt) }
    }

    /// calculate for quintic polynomial trajectory acceleration
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_polytraj5_acc(self, dt) }
    }
}

#[test]
fn polytraj5() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a = crate::polytraj::polytraj5::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
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
pub struct polytraj7 {
    /// coefficients, q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3+k_4(t-t_0)^4+k_5(t-t_0)^5+k_6(t-t_0)^6+k_7(t-t_0)^7
    k: [float; 8],
}

extern "C" {
    fn a_polytraj7_gen(
        ctx: *mut polytraj7,
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
    fn a_polytraj7_pos(ctx: *const polytraj7, dt: float) -> float;
    fn a_polytraj7_vel(ctx: *const polytraj7, dt: float) -> float;
    fn a_polytraj7_acc(ctx: *const polytraj7, dt: float) -> float;
    fn a_polytraj7_jer(ctx: *const polytraj7, dt: float) -> float;
    fn a_polytraj7_out(ctx: *const polytraj7, dt: float, out: *mut [float; 4]);
}

impl polytraj7 {
    /// initialize for hepta polynomial trajectory
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
        unsafe { a_polytraj7_gen(&mut ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) };
        ctx
    }

    /// generate for hepta polynomial trajectory
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
        unsafe { a_polytraj7_gen(self, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) };
        self
    }

    /// calculate for hepta polynomial trajectory
    pub fn out(&mut self, dt: float) -> [float; 4] {
        let mut out: [float; 4] = [0.0; 4];
        unsafe { a_polytraj7_out(self, dt, &mut out) };
        out
    }

    /// calculate for hepta polynomial trajectory position
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_polytraj7_pos(self, dt) }
    }

    /// calculate for hepta polynomial trajectory velocity
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_polytraj7_vel(self, dt) }
    }

    /// calculate for hepta polynomial trajectory acceleration
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_polytraj7_acc(self, dt) }
    }

    /// calculate for hepta polynomial trajectory jerk
    pub fn jer(&mut self, dt: float) -> float {
        unsafe { a_polytraj7_jer(self, dt) }
    }
}

#[test]
fn polytraj7() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a =
            crate::polytraj::polytraj7::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        let jer = a.jer(dt);
        let out = a.out(dt);
        std::println!("[{}, {}, {}, {}]", pos, vel, acc, jer);
        std::println!("{:?}", out);
    }
}
