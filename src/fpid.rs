//! fuzzy proportional integral derivative controller

use crate::pid::PID;
use crate::Real;
use crate::Uint;

/// fuzzy proportional integral derivative controller
#[repr(C)]
pub struct FPID {
    /// proportional integral derivative controller
    pub pid: PID,
    me: *const Real,
    mec: *const Real,
    mkp: *const Real,
    mki: *const Real,
    mkd: *const Real,
    idx: *mut Uint,
    val: *mut Real,
    /// fuzzy relational operator
    op: Option<extern "C" fn(Real, Real) -> Real>,
    /// base proportional constant
    pub kp: Real,
    /// base integral constant
    pub ki: Real,
    /// base derivative constant
    pub kd: Real,
}

extern "C" {
    fn a_fpid_off(ctx: *mut FPID) -> *mut FPID;
    fn a_fpid_inc(ctx: *mut FPID) -> *mut FPID;
    fn a_fpid_pos(ctx: *mut FPID, max: Real) -> *mut FPID;
    fn a_fpid_kpid(ctx: *mut FPID, kp: Real, ki: Real, kd: Real) -> *mut FPID;
    fn a_fpid_buff(ctx: *mut FPID, idx: *mut Uint, val: *mut Real) -> *mut FPID;
    fn a_fpid_base(
        ctx: *mut FPID,
        num: Uint,
        me: *const Real,
        mec: *const Real,
        mkp: *const Real,
        mki: *const Real,
        mkd: *const Real,
    ) -> *mut FPID;
    fn a_fpid_init(
        ctx: *mut FPID,
        dt: Real,
        col: Uint,
        me: *const Real,
        mec: *const Real,
        mkp: *const Real,
        mki: *const Real,
        mkd: *const Real,
        min: Real,
        max: Real,
    ) -> *mut FPID;
    fn a_fpid_outv(ctx: *mut FPID, set: Real, fdb: Real) -> Real;
    fn a_fpid_zero(ctx: *mut FPID) -> *mut FPID;
}

impl FPID {
    /// initialize function for fuzzy PID controller, default is turn off
    pub fn new(
        dt: Real,
        col: usize,
        me: &[Real],
        mec: &[Real],
        mkp: &[Real],
        mki: &[Real],
        mkd: &[Real],
        min: Real,
        max: Real,
    ) -> Self {
        let mut ctx: Self = Self {
            pid: PID::new(dt, min, max),
            me: std::ptr::null(),
            mec: std::ptr::null(),
            mkp: std::ptr::null(),
            mki: std::ptr::null(),
            mkd: std::ptr::null(),
            idx: std::ptr::null_mut(),
            val: std::ptr::null_mut(),
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            op: None,
        };
        unsafe {
            a_fpid_init(
                &mut ctx,
                dt,
                col as Uint,
                me.as_ptr(),
                mec.as_ptr(),
                mkp.as_ptr(),
                mki.as_ptr(),
                mkd.as_ptr(),
                min,
                max,
            );
        };
        ctx
    }

    /// turn off fuzzy PID controller
    pub fn off(&mut self) -> &mut Self {
        unsafe { a_fpid_off(self).as_mut().unwrap_unchecked() }
    }

    /// incremental fuzzy PID controller
    pub fn inc(&mut self) -> &mut Self {
        unsafe { a_fpid_inc(self).as_mut().unwrap_unchecked() }
    }

    /// positional fuzzy PID controller
    pub fn pos(&mut self, max: Real) -> &mut Self {
        unsafe { a_fpid_pos(self, max).as_mut().unwrap_unchecked() }
    }

    /// set proportional integral derivative constant for fuzzy PID controller
    pub fn kpid(&mut self, kp: Real, ki: Real, kd: Real) -> &mut Self {
        unsafe { a_fpid_kpid(self, kp, ki, kd).as_mut().unwrap_unchecked() }
    }

    /// set buffer for fuzzy PID controller
    pub fn buff(&mut self, idx: &mut [u32], val: &mut [Real]) -> &mut Self {
        unsafe {
            a_fpid_buff(self, idx.as_mut_ptr(), val.as_mut_ptr())
                .as_mut()
                .unwrap_unchecked()
        }
    }

    /// set rule base for fuzzy PID controller
    pub fn base(
        &mut self,
        col: usize,
        me: &[Real],
        mec: &[Real],
        mkp: &[Real],
        mki: &[Real],
        mkd: &[Real],
    ) -> &mut Self {
        unsafe {
            a_fpid_base(
                self,
                col as Uint,
                me.as_ptr(),
                mec.as_ptr(),
                mkp.as_ptr(),
                mki.as_ptr(),
                mkd.as_ptr(),
            )
            .as_mut()
            .unwrap_unchecked()
        }
    }

    /// calculate function for fuzzy PID controller
    pub fn iter(&mut self, set: Real, fdb: Real) -> Real {
        unsafe { a_fpid_outv(self, set, fdb) }
    }

    /// zero function for fuzzy PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_fpid_zero(self).as_mut().unwrap_unchecked() }
    }

    /// get sampling time unit(s) for fuzzy PID controller
    pub fn dt(&self) -> Uint {
        self.pid.mode()
    }
    /// set sampling time unit(s) for fuzzy PID controller
    pub fn set_dt(&mut self, dt: Real) -> &mut Self {
        self.pid.set_dt(dt);
        self
    }

    /// get mode for fuzzy PID controller
    pub fn mode(&self) -> Uint {
        self.pid.mode()
    }
    /// set mode for PID controller
    pub fn set_mode(&mut self, reg: Uint) -> &mut Self {
        self.pid.set_mode(reg);
        self
    }
}

#[test]
#[allow(non_snake_case)]
fn fpid() {
    let NB: Real = -3.0;
    let NM: Real = -2.0;
    let NS: Real = -1.0;
    let ZO: Real = 0.0;
    let PS: Real = 1.0;
    let PM: Real = 2.0;
    let PB: Real = 3.0;
    let me = [
        crate::mf::TRI,
        NB,
        NB,
        NM,
        crate::mf::TRI,
        NB,
        NM,
        NS,
        crate::mf::TRI,
        NM,
        NS,
        ZO,
        crate::mf::TRI,
        NS,
        ZO,
        PS,
        crate::mf::TRI,
        ZO,
        PS,
        PM,
        crate::mf::TRI,
        PS,
        PM,
        PB,
        crate::mf::TRI,
        PM,
        PB,
        PB,
        crate::mf::NUL,
    ];
    let NB: Real = -3.0;
    let NM: Real = -2.0;
    let NS: Real = -1.0;
    let ZO: Real = 0.0;
    let PS: Real = 1.0;
    let PM: Real = 2.0;
    let PB: Real = 3.0;
    let mec = [
        crate::mf::TRI,
        NB,
        NB,
        NM,
        crate::mf::TRI,
        NB,
        NM,
        NS,
        crate::mf::TRI,
        NM,
        NS,
        ZO,
        crate::mf::TRI,
        NS,
        ZO,
        PS,
        crate::mf::TRI,
        ZO,
        PS,
        PM,
        crate::mf::TRI,
        PS,
        PM,
        PB,
        crate::mf::TRI,
        PM,
        PB,
        PB,
        crate::mf::NUL,
    ];
    let NB: Real = -15.0;
    let NM: Real = -10.0;
    let NS: Real = -5.0;
    let ZO: Real = 0.0;
    let PS: Real = 5.0;
    let PM: Real = 10.0;
    let PB: Real = 15.0;
    let mkp = [
        [NB, NB, NM, NM, NS, ZO, ZO],
        [NB, NB, NM, NS, NS, ZO, PS],
        [NM, NM, NM, NS, ZO, PS, PS],
        [NM, NM, NS, ZO, PS, PM, PM],
        [NS, NS, ZO, PS, PS, PM, PM],
        [NS, ZO, PS, PM, PM, PM, PB],
        [ZO, ZO, PM, PM, PM, PB, PB],
    ];
    let NB: Real = -3.0;
    let NM: Real = -2.0;
    let NS: Real = -1.0;
    let ZO: Real = 0.0;
    let PS: Real = 1.0;
    let PM: Real = 2.0;
    let PB: Real = 3.0;
    let mki = [
        [PB, PB, PM, PM, PS, ZO, ZO],
        [PB, PB, PM, PS, PS, ZO, ZO],
        [PB, PM, PS, PS, ZO, NS, NS],
        [PM, PM, PS, ZO, NS, NM, NM],
        [PM, PS, ZO, NS, NS, NM, NB],
        [ZO, ZO, NS, NS, NM, NB, NB],
        [ZO, ZO, NS, NM, NM, NB, NB],
    ];
    let mkd = [
        [NS, PS, PB, PB, PB, PM, NS],
        [NS, PS, PB, PM, PM, PS, ZO],
        [ZO, PS, PM, PM, PS, PS, ZO],
        [ZO, PS, PS, PS, PS, PS, ZO],
        [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
        [NB, NS, NS, NS, NS, NS, NB],
        [NB, NM, NM, NM, NS, NS, NB],
    ];
    let mut a = crate::FPID::new(
        1.0,
        mkp.len(),
        &me,
        &mec,
        &mkp.concat(),
        &mki.concat(),
        &mkd.concat(),
        -10.0,
        10.0,
    );
    a.base(
        mkp.len(),
        &me,
        &mec,
        &mkp.concat(),
        &mki.concat(),
        &mkd.concat(),
    );
    a.kpid(10.0, 0.1, 1.0);
    let mut idx = [0u32; 4];
    let mut val = [0.0; 8];
    a.buff(&mut idx, &mut val);
    a.pos(10.0).off().inc().set_dt(0.1);
    assert!(a.mode() == crate::pid::INC);
    println!("{}", a.iter(1.0, 0.0));
    a.zero();
}
