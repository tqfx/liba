//! polynomial trajectory

use crate::real;

/// cubic polynomial trajectory
#[repr(C)]
pub struct polytrack3 {
    /// quantity
    k: [real; 4],
}

extern "C" {
    fn a_polytrack3_gen(
        ctx: *mut polytrack3,
        t0: real,
        t1: real,
        q0: real,
        q1: real,
        v0: real,
        v1: real,
    );
    fn a_polytrack3_pos(ctx: *const polytrack3, dt: real) -> real;
    fn a_polytrack3_vec(ctx: *const polytrack3, dt: real) -> real;
    fn a_polytrack3_acc(ctx: *const polytrack3, dt: real) -> real;
    fn a_polytrack3_out(ctx: *const polytrack3, dt: real, out: *mut [real; 3]);
}

impl polytrack3 {
    /// initialize function for cubic polynomial trajectory
    pub fn new(t0: real, t1: real, q0: real, q1: real, v0: real, v1: real) -> Self {
        let mut ctx: Self = Self { k: [0.0; 4] };
        unsafe { a_polytrack3_gen(&mut ctx, t0, t1, q0, q1, v0, v1) };
        ctx
    }

    /// generation function for cubic polynomial trajectory
    pub fn gen(&mut self, t0: real, t1: real, q0: real, q1: real, v0: real, v1: real) -> &mut Self {
        unsafe { a_polytrack3_gen(self, t0, t1, q0, q1, v0, v1) };
        self
    }

    /// calculate function for cubic polynomial trajectory
    pub fn out(&mut self, dt: real) -> [real; 3] {
        let mut out: [real; 3] = [0.0; 3];
        unsafe { a_polytrack3_out(self, dt, &mut out) };
        out
    }

    /// calculate function for cubic polynomial trajectory position
    pub fn pos(&mut self, dt: real) -> real {
        unsafe { a_polytrack3_pos(self, dt) }
    }

    /// calculate function for cubic polynomial trajectory velocity
    pub fn vec(&mut self, dt: real) -> real {
        unsafe { a_polytrack3_vec(self, dt) }
    }

    /// calculate function for cubic polynomial trajectory acceleration
    pub fn acc(&mut self, dt: real) -> real {
        unsafe { a_polytrack3_acc(self, dt) }
    }
}

#[test]
fn polytrack3() {
    let dt = 0.5;
    {
        let mut a = crate::polytrack3::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        println!("[{}, {}, {}]", a.pos(dt), a.vec(dt), a.acc(dt));
        println!("{:?}", a.out(dt));
    }
}

/// quintic polynomial trajectory
#[repr(C)]
pub struct polytrack5 {
    /// quantity
    k: [real; 6],
}

extern "C" {
    fn a_polytrack5_gen(
        ctx: *mut polytrack5,
        t0: real,
        t1: real,
        q0: real,
        q1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
    );
    fn a_polytrack5_pos(ctx: *const polytrack5, dt: real) -> real;
    fn a_polytrack5_vec(ctx: *const polytrack5, dt: real) -> real;
    fn a_polytrack5_acc(ctx: *const polytrack5, dt: real) -> real;
    fn a_polytrack5_out(ctx: *const polytrack5, dt: real, out: *mut [real; 3]);
}

impl polytrack5 {
    /// initialize function for quintic polynomial trajectory
    pub fn new(
        t0: real,
        t1: real,
        q0: real,
        q1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
    ) -> Self {
        let mut ctx: Self = Self { k: [0.0; 6] };
        unsafe { a_polytrack5_gen(&mut ctx, t0, t1, q0, q1, v0, v1, a0, a1) };
        ctx
    }

    /// generation function for quintic polynomial trajectory
    pub fn gen(
        &mut self,
        t0: real,
        t1: real,
        q0: real,
        q1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
    ) -> &mut Self {
        unsafe { a_polytrack5_gen(self, t0, t1, q0, q1, v0, v1, a0, a1) };
        self
    }

    /// calculate function for quintic polynomial trajectory
    pub fn out(&mut self, dt: real) -> [real; 3] {
        let mut out: [real; 3] = [0.0; 3];
        unsafe { a_polytrack5_out(self, dt, &mut out) };
        out
    }

    /// calculate function for quintic polynomial trajectory position
    pub fn pos(&mut self, dt: real) -> real {
        unsafe { a_polytrack5_pos(self, dt) }
    }

    /// calculate function for quintic polynomial trajectory velocity
    pub fn vec(&mut self, dt: real) -> real {
        unsafe { a_polytrack5_vec(self, dt) }
    }

    /// calculate function for quintic polynomial trajectory acceleration
    pub fn acc(&mut self, dt: real) -> real {
        unsafe { a_polytrack5_acc(self, dt) }
    }
}

#[test]
fn polytrack5() {
    let dt = 0.5;
    {
        let mut a = crate::polytrack5::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        println!("[{}, {}, {}]", a.pos(dt), a.vec(dt), a.acc(dt));
        println!("{:?}", a.out(dt));
    }
}

/// hepta polynomial trajectory
#[repr(C)]
pub struct polytrack7 {
    /// quantity
    k: [real; 8],
}

extern "C" {
    fn a_polytrack7_gen(
        ctx: *mut polytrack7,
        t0: real,
        t1: real,
        q0: real,
        q1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
        j0: real,
        j1: real,
    );
    fn a_polytrack7_pos(ctx: *const polytrack7, dt: real) -> real;
    fn a_polytrack7_vec(ctx: *const polytrack7, dt: real) -> real;
    fn a_polytrack7_acc(ctx: *const polytrack7, dt: real) -> real;
    fn a_polytrack7_jer(ctx: *const polytrack7, dt: real) -> real;
    fn a_polytrack7_out(ctx: *const polytrack7, dt: real, out: *mut [real; 4]);
}

impl polytrack7 {
    /// initialize function for hepta polynomial trajectory
    pub fn new(
        t0: real,
        t1: real,
        q0: real,
        q1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
        j0: real,
        j1: real,
    ) -> Self {
        let mut ctx: Self = Self { k: [0.0; 8] };
        unsafe { a_polytrack7_gen(&mut ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) };
        ctx
    }

    /// generation function for hepta polynomial trajectory
    pub fn gen(
        &mut self,
        t0: real,
        t1: real,
        q0: real,
        q1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
        j0: real,
        j1: real,
    ) -> &mut Self {
        unsafe { a_polytrack7_gen(self, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) };
        self
    }

    /// calculate function for hepta polynomial trajectory
    pub fn out(&mut self, dt: real) -> [real; 4] {
        let mut out: [real; 4] = [0.0; 4];
        unsafe { a_polytrack7_out(self, dt, &mut out) };
        out
    }

    /// calculate function for hepta polynomial trajectory position
    pub fn pos(&mut self, dt: real) -> real {
        unsafe { a_polytrack7_pos(self, dt) }
    }

    /// calculate function for hepta polynomial trajectory velocity
    pub fn vec(&mut self, dt: real) -> real {
        unsafe { a_polytrack7_vec(self, dt) }
    }

    /// calculate function for hepta polynomial trajectory acceleration
    pub fn acc(&mut self, dt: real) -> real {
        unsafe { a_polytrack7_acc(self, dt) }
    }

    /// calculate function for hepta polynomial trajectory jerk
    pub fn jer(&mut self, dt: real) -> real {
        unsafe { a_polytrack7_jer(self, dt) }
    }
}

#[test]
fn polytrack7() {
    let dt = 0.5;
    {
        let mut a = crate::polytrack7::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        println!("{:?}", a.out(dt));
        println!(
            "[{}, {}, {}, {}]",
            a.pos(dt),
            a.vec(dt),
            a.acc(dt),
            a.jer(dt)
        );
    }
}
