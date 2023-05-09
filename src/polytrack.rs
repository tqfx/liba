//! polynomial trajectory

use crate::real;

/// cubic polynomial trajectory
#[repr(C)]
pub struct PolyTrack3 {
    /// quantity
    k: [real; 4],
    /// time unit(s)
    pub t: [real; 2],
    /// position
    pub q: [real; 2],
    /// velocity
    pub v: [real; 2],
}

extern "C" {
    fn a_polytrack3_init(
        ctx: *mut PolyTrack3,
        t0: real,
        t1: real,
        q0: real,
        q1: real,
        v0: real,
        v1: real,
    );
    fn a_polytrack3_init1(
        ctx: *mut PolyTrack3,
        t: *const [real; 2],
        q: *const [real; 2],
        v: *const [real; 2],
    );
    fn a_polytrack3_init2(ctx: *mut PolyTrack3, source: *const [real; 3], target: *const [real; 3]);
    fn a_polytrack3_pos(ctx: *mut PolyTrack3, ts: real) -> real;
    fn a_polytrack3_vec(ctx: *mut PolyTrack3, ts: real) -> real;
    fn a_polytrack3_acc(ctx: *mut PolyTrack3, ts: real) -> real;
    fn a_polytrack3_out(ctx: *mut PolyTrack3, ts: real, out: *mut [real; 3]);
    fn a_polytrack3_gen(ctx: *mut PolyTrack3);
}

impl PolyTrack3 {
    /// initialize function for cubic polynomial trajectory
    pub fn new(t0: real, t1: real, q0: real, q1: real, v0: real, v1: real) -> Self {
        let mut ctx: Self = Self {
            k: [0.0; 4],
            t: [0.0; 2],
            q: [0.0; 2],
            v: [0.0; 2],
        };
        unsafe { a_polytrack3_init(&mut ctx, t0, t1, q0, q1, v0, v1) };
        ctx
    }

    /// initialize function for cubic polynomial trajectory
    pub fn new1(t: [real; 2], q: [real; 2], v: [real; 2]) -> Self {
        let mut ctx: Self = Self {
            k: [0.0; 4],
            t: [0.0; 2],
            q: [0.0; 2],
            v: [0.0; 2],
        };
        unsafe { a_polytrack3_init1(&mut ctx, &t, &q, &v) };
        ctx
    }

    /// initialize function for cubic polynomial trajectory
    pub fn new2(source: [real; 3], target: [real; 3]) -> Self {
        let mut ctx: Self = Self {
            k: [0.0; 4],
            t: [0.0; 2],
            q: [0.0; 2],
            v: [0.0; 2],
        };
        unsafe { a_polytrack3_init2(&mut ctx, &source, &target) };
        ctx
    }

    /// generation function for cubic polynomial trajectory
    pub fn gen(&mut self) -> &mut Self {
        unsafe { a_polytrack3_gen(self) };
        self
    }

    /// calculate function for cubic polynomial trajectory
    pub fn out(&mut self, ts: real) -> [real; 3] {
        let mut out: [real; 3] = [0.0; 3];
        unsafe { a_polytrack3_out(self, ts, &mut out) };
        out
    }

    /// calculate function for cubic polynomial trajectory position
    pub fn pos(&mut self, ts: real) -> real {
        unsafe { a_polytrack3_pos(self, ts) }
    }

    /// calculate function for cubic polynomial trajectory velocity
    pub fn vec(&mut self, ts: real) -> real {
        unsafe { a_polytrack3_vec(self, ts) }
    }

    /// calculate function for cubic polynomial trajectory acceleration
    pub fn acc(&mut self, ts: real) -> real {
        unsafe { a_polytrack3_acc(self, ts) }
    }
}

#[test]
fn polytrack3() {
    let ts = 0.3;
    {
        let mut a = crate::PolyTrack3::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        println!("[{}, {}, {}]", a.pos(ts), a.vec(ts), a.acc(ts));
        println!("{:?}", a.out(ts));
    }
    {
        let mut a = crate::PolyTrack3::new1([0.0, 1.0], [0.0, 1.0], [0.0, 1.0]);
        println!("[{}, {}, {}]", a.pos(ts), a.vec(ts), a.acc(ts));
        println!("{:?}", a.out(ts));
    }
    {
        let mut a = crate::PolyTrack3::new2([0.0, 0.0, 0.0], [1.0, 1.0, 1.0]);
        println!("[{}, {}, {}]", a.pos(ts), a.vec(ts), a.acc(ts));
        println!("{:?}", a.out(ts));
        a.v = [0.0, 0.0];
        println!("{:?}", a.k);
        a.gen();
        println!("{:?}", a.k);
    }
}

/// quintic polynomial trajectory
#[repr(C)]
pub struct PolyTrack5 {
    /// quantity
    k: [real; 6],
    /// time unit(s)
    pub t: [real; 2],
    /// position
    pub q: [real; 2],
    /// velocity
    pub v: [real; 2],
    /// acceleration
    pub a: [real; 2],
}

extern "C" {
    fn a_polytrack5_init(
        ctx: *mut PolyTrack5,
        t0: real,
        t1: real,
        q0: real,
        q1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
    );
    fn a_polytrack5_init1(
        ctx: *mut PolyTrack5,
        t: *const [real; 2],
        q: *const [real; 2],
        v: *const [real; 2],
        a: *const [real; 2],
    );
    fn a_polytrack5_init2(ctx: *mut PolyTrack5, source: *const [real; 4], target: *const [real; 4]);
    fn a_polytrack5_pos(ctx: *mut PolyTrack5, ts: real) -> real;
    fn a_polytrack5_vec(ctx: *mut PolyTrack5, ts: real) -> real;
    fn a_polytrack5_acc(ctx: *mut PolyTrack5, ts: real) -> real;
    fn a_polytrack5_out(ctx: *mut PolyTrack5, ts: real, out: *mut [real; 3]);
    fn a_polytrack5_gen(ctx: *mut PolyTrack5);
}

impl PolyTrack5 {
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
        let mut ctx: Self = Self {
            k: [0.0; 6],
            t: [0.0; 2],
            q: [0.0; 2],
            v: [0.0; 2],
            a: [0.0; 2],
        };
        unsafe { a_polytrack5_init(&mut ctx, t0, t1, q0, q1, v0, v1, a0, a1) };
        ctx
    }

    /// initialize function for quintic polynomial trajectory
    pub fn new1(t: [real; 2], q: [real; 2], v: [real; 2], a: [real; 2]) -> Self {
        let mut ctx: Self = Self {
            k: [0.0; 6],
            t: [0.0; 2],
            q: [0.0; 2],
            v: [0.0; 2],
            a: [0.0; 2],
        };
        unsafe { a_polytrack5_init1(&mut ctx, &t, &q, &v, &a) };
        ctx
    }

    /// initialize function for quintic polynomial trajectory
    pub fn new2(source: [real; 4], target: [real; 4]) -> Self {
        let mut ctx: Self = Self {
            k: [0.0; 6],
            t: [0.0; 2],
            q: [0.0; 2],
            v: [0.0; 2],
            a: [0.0; 2],
        };
        unsafe { a_polytrack5_init2(&mut ctx, &source, &target) };
        ctx
    }

    /// generation function for quintic polynomial trajectory
    pub fn gen(&mut self) -> &mut Self {
        unsafe { a_polytrack5_gen(self) };
        self
    }

    /// calculate function for quintic polynomial trajectory
    pub fn out(&mut self, ts: real) -> [real; 3] {
        let mut out: [real; 3] = [0.0; 3];
        unsafe { a_polytrack5_out(self, ts, &mut out) };
        out
    }

    /// calculate function for quintic polynomial trajectory position
    pub fn pos(&mut self, ts: real) -> real {
        unsafe { a_polytrack5_pos(self, ts) }
    }

    /// calculate function for quintic polynomial trajectory velocity
    pub fn vec(&mut self, ts: real) -> real {
        unsafe { a_polytrack5_vec(self, ts) }
    }

    /// calculate function for quintic polynomial trajectory acceleration
    pub fn acc(&mut self, ts: real) -> real {
        unsafe { a_polytrack5_acc(self, ts) }
    }
}

#[test]
fn polytrack5() {
    let ts = 0.5;
    {
        let mut a = crate::PolyTrack5::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        println!("[{}, {}, {}]", a.pos(ts), a.vec(ts), a.acc(ts));
        println!("{:?}", a.out(ts));
    }
    {
        let mut a = crate::PolyTrack5::new1([0.0, 1.0], [0.0, 1.0], [0.0, 1.0], [0.0, 1.0]);
        println!("[{}, {}, {}]", a.pos(ts), a.vec(ts), a.acc(ts));
        println!("{:?}", a.out(ts));
    }
    {
        let mut a = crate::PolyTrack5::new2([0.0, 0.0, 0.0, 0.0], [1.0, 1.0, 1.0, 1.0]);
        println!("[{}, {}, {}]", a.pos(ts), a.vec(ts), a.acc(ts));
        println!("{:?}", a.out(ts));
        a.v = [0.0, 0.0];
        a.a = [0.0, 0.0];
        println!("{:?}", a.k);
        a.gen();
        println!("{:?}", a.k);
    }
}

/// hepta polynomial trajectory
#[repr(C)]
pub struct PolyTrack7 {
    /// quantity
    k: [real; 8],
    /// time unit(s)
    pub t: [real; 2],
    /// position
    pub q: [real; 2],
    /// velocity
    pub v: [real; 2],
    /// acceleration
    pub a: [real; 2],
    /// jerk
    pub j: [real; 2],
}

extern "C" {
    fn a_polytrack7_init(
        ctx: *mut PolyTrack7,
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
    fn a_polytrack7_init1(
        ctx: *mut PolyTrack7,
        t: *const [real; 2],
        q: *const [real; 2],
        v: *const [real; 2],
        a: *const [real; 2],
        j: *const [real; 2],
    );
    fn a_polytrack7_init2(ctx: *mut PolyTrack7, source: *const [real; 5], target: *const [real; 5]);
    fn a_polytrack7_pos(ctx: *mut PolyTrack7, ts: real) -> real;
    fn a_polytrack7_vec(ctx: *mut PolyTrack7, ts: real) -> real;
    fn a_polytrack7_acc(ctx: *mut PolyTrack7, ts: real) -> real;
    fn a_polytrack7_jer(ctx: *mut PolyTrack7, ts: real) -> real;
    fn a_polytrack7_out(ctx: *mut PolyTrack7, ts: real, out: *mut [real; 4]);
    fn a_polytrack7_gen(ctx: *mut PolyTrack7);
}

impl PolyTrack7 {
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
        let mut ctx: Self = Self {
            k: [0.0; 8],
            t: [0.0; 2],
            q: [0.0; 2],
            v: [0.0; 2],
            a: [0.0; 2],
            j: [0.0; 2],
        };
        unsafe { a_polytrack7_init(&mut ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) };
        ctx
    }

    /// initialize function for hepta polynomial trajectory
    pub fn new1(t: [real; 2], q: [real; 2], v: [real; 2], a: [real; 2], j: [real; 2]) -> Self {
        let mut ctx: Self = Self {
            k: [0.0; 8],
            t: [0.0; 2],
            q: [0.0; 2],
            v: [0.0; 2],
            a: [0.0; 2],
            j: [0.0; 2],
        };
        unsafe { a_polytrack7_init1(&mut ctx, &t, &q, &v, &a, &j) };
        ctx
    }

    /// initialize function for hepta polynomial trajectory
    pub fn new2(source: [real; 5], target: [real; 5]) -> Self {
        let mut ctx: Self = Self {
            k: [0.0; 8],
            t: [0.0; 2],
            q: [0.0; 2],
            v: [0.0; 2],
            a: [0.0; 2],
            j: [0.0; 2],
        };
        unsafe { a_polytrack7_init2(&mut ctx, &source, &target) };
        ctx
    }

    /// generation function for hepta polynomial trajectory
    pub fn gen(&mut self) -> &mut Self {
        unsafe { a_polytrack7_gen(self) };
        self
    }

    /// calculate function for hepta polynomial trajectory
    pub fn out(&mut self, ts: real) -> [real; 4] {
        let mut out: [real; 4] = [0.0; 4];
        unsafe { a_polytrack7_out(self, ts, &mut out) };
        out
    }

    /// calculate function for hepta polynomial trajectory position
    pub fn pos(&mut self, ts: real) -> real {
        unsafe { a_polytrack7_pos(self, ts) }
    }

    /// calculate function for hepta polynomial trajectory velocity
    pub fn vec(&mut self, ts: real) -> real {
        unsafe { a_polytrack7_vec(self, ts) }
    }

    /// calculate function for hepta polynomial trajectory acceleration
    pub fn acc(&mut self, ts: real) -> real {
        unsafe { a_polytrack7_acc(self, ts) }
    }

    /// calculate function for hepta polynomial trajectory jerk
    pub fn jer(&mut self, ts: real) -> real {
        unsafe { a_polytrack7_jer(self, ts) }
    }
}

#[test]
fn polytrack7() {
    let ts = 0.5;
    {
        let mut a = crate::PolyTrack7::new(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        println!("{:?}", a.out(ts));
        println!(
            "[{}, {}, {}, {}]",
            a.pos(ts),
            a.vec(ts),
            a.acc(ts),
            a.jer(ts)
        );
    }
    {
        let mut a =
            crate::PolyTrack7::new1([0.0, 1.0], [0.0, 1.0], [0.0, 1.0], [0.0, 1.0], [0.0, 1.0]);
        println!("{:?}", a.out(ts));
        println!(
            "[{}, {}, {}, {}]",
            a.pos(ts),
            a.vec(ts),
            a.acc(ts),
            a.jer(ts)
        );
    }
    {
        let mut a = crate::PolyTrack7::new2([0.0, 0.0, 0.0, 0.0, 0.0], [1.0, 1.0, 1.0, 1.0, 1.0]);
        println!("{:?}", a.out(ts));
        println!(
            "[{}, {}, {}, {}]",
            a.pos(ts),
            a.vec(ts),
            a.acc(ts),
            a.jer(ts)
        );
        a.v = [0.0, 0.0];
        a.a = [0.0, 0.0];
        a.j = [0.0, 0.0];
        println!("{:?}", a.k);
        a.gen();
        println!("{:?}", a.k);
    }
}
