//! fuzzy proportional integral derivative controller

use crate::pid::PID;
use crate::Real;
use crate::Uint;

/// fuzzy proportional integral derivative controller
#[repr(C)]
pub struct FPID {
    /// proportional integral derivative controller
    pub pid: PID,
    mmp: *const Real,
    mkp: *const Real,
    mki: *const Real,
    mkd: *const Real,
    idx: *mut Uint,
    mms: *mut Real,
    mat: *mut Real,
    /// fuzzy relational operator
    op: Option<extern "C" fn(Real, Real) -> Real>,
    sigma: Real,
    alpha: Real,
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
    fn a_fpid_ilim(ctx: *mut FPID, min: Real, max: Real) -> *mut FPID;
    fn a_fpid_olim(ctx: *mut FPID, min: Real, max: Real) -> *mut FPID;
    fn a_fpid_kpid(ctx: *mut FPID, kp: Real, ki: Real, kd: Real) -> *mut FPID;
    fn a_fpid_buff(ctx: *mut FPID, idx: *mut Uint, mms: *mut Real, mat: *mut Real) -> *mut FPID;
    fn a_fpid_base(
        ctx: *mut FPID,
        num: Uint,
        mmp: *const Real,
        mkp: *const Real,
        mki: *const Real,
        mkd: *const Real,
    ) -> *mut FPID;
    fn a_fpid_init(
        ctx: *mut FPID,
        dt: Real,
        num: Uint,
        mmp: *const Real,
        mkp: *const Real,
        mki: *const Real,
        mkd: *const Real,
        imin: Real,
        imax: Real,
        omin: Real,
        omax: Real,
    ) -> *mut FPID;
    fn a_fpid_outv(ctx: *mut FPID, set: Real, fdb: Real) -> Real;
    fn a_fpid_zero(ctx: *mut FPID) -> *mut FPID;
}

impl FPID {
    /// initialize function for fuzzy PID controller, default is turn off
    pub fn new(
        dt: Real,
        num: usize,
        mmp: &[Real],
        mkp: &[Real],
        mki: &[Real],
        mkd: &[Real],
        imin: Real,
        imax: Real,
        omin: Real,
        omax: Real,
    ) -> Self {
        let mut ctx: Self = Self {
            pid: PID::new(dt, omin, omax),
            mkp: std::ptr::null(),
            mki: std::ptr::null(),
            mkd: std::ptr::null(),
            mmp: std::ptr::null(),
            sigma: 0.0,
            alpha: 0.0,
            idx: std::ptr::null_mut(),
            mms: std::ptr::null_mut(),
            mat: std::ptr::null_mut(),
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            op: None,
        };
        unsafe {
            a_fpid_init(
                &mut ctx,
                dt,
                num as Uint,
                mmp.as_ptr(),
                mkp.as_ptr(),
                mki.as_ptr(),
                mkd.as_ptr(),
                imin,
                imax,
                omin,
                omax,
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

    /// set input extreme value for fuzzy PID controller
    pub fn ilim(&mut self, min: Real, max: Real) -> &mut Self {
        unsafe { a_fpid_ilim(self, min, max).as_mut().unwrap_unchecked() }
    }

    /// set output extreme value for fuzzy PID controller
    pub fn olim(&mut self, min: Real, max: Real) -> &mut Self {
        unsafe { a_fpid_olim(self, min, max).as_mut().unwrap_unchecked() }
    }

    /// set proportional integral derivative constant for fuzzy PID controller
    pub fn kpid(&mut self, kp: Real, ki: Real, kd: Real) -> &mut Self {
        unsafe { a_fpid_kpid(self, kp, ki, kd).as_mut().unwrap_unchecked() }
    }

    /// set buffer for fuzzy PID controller
    pub fn buff(&mut self, idx: &mut [u32], mms: &mut [Real], mat: &mut [Real]) -> &mut Self {
        unsafe {
            a_fpid_buff(self, idx.as_mut_ptr(), mms.as_mut_ptr(), mat.as_mut_ptr())
                .as_mut()
                .unwrap_unchecked()
        }
    }

    /// set rule base for fuzzy PID controller
    pub fn base(
        &mut self,
        num: usize,
        mmp: &[Real],
        mkp: &[Real],
        mki: &[Real],
        mkd: &[Real],
    ) -> &mut Self {
        unsafe {
            a_fpid_base(
                self,
                num as Uint,
                mmp.as_ptr(),
                mkp.as_ptr(),
                mki.as_ptr(),
                mkd.as_ptr(),
            )
            .as_mut()
            .unwrap_unchecked()
        }
    }

    /// process function for fuzzy PID controller
    pub fn proc(&mut self, set: Real, fdb: Real) -> Real {
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
fn fpid() {
    const NB: Real = -3.0;
    const NM: Real = -2.0;
    const NS: Real = -1.0;
    const ZO: Real = 0.0;
    const PS: Real = 1.0;
    const PM: Real = 2.0;
    const PB: Real = 3.0;
    let mmp = [
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
    let mkp = [
        [NB, NB, NM, NM, NS, ZO, ZO],
        [NB, NB, NM, NS, NS, ZO, PS],
        [NM, NM, NM, NS, ZO, PS, PS],
        [NM, NM, NS, ZO, PS, PM, PM],
        [NS, NS, ZO, PS, PS, PM, PM],
        [NS, ZO, PS, PM, PM, PM, PB],
        [ZO, ZO, PM, PM, PM, PB, PB],
    ];
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
        &mmp,
        &mkp.concat(),
        &mki.concat(),
        &mkd.concat(),
        -10.0,
        10.0,
        -10.0,
        10.0,
    );
    a.base(mkp.len(), &mmp, &mkp.concat(), &mki.concat(), &mkd.concat());
    a.kpid(10.0, 0.1, 1.0);
    let mut idx = [0u32; 4];
    let mut mms = [0.0; 4];
    let mut mat = [0.0; 4];
    a.buff(&mut idx, &mut mms, &mut mat);
    a.pos(10.0).off().inc().set_dt(0.1);
    assert!(a.mode() == crate::pid::INC);
    println!("{}", a.proc(1.0, 0.0));
    a.zero();
}
