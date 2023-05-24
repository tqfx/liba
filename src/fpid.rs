//! fuzzy proportional integral derivative controller

use crate::pid::PID;
use crate::float;
use crate::uint;

/// enumeration for fuzzy PID controller operator
#[repr(C)]
pub enum op {
    /// sqrt(l,r)*sqrt(1-(1-r)*(1-r))
    EQU,
    /// min(l,r)
    AND = 0b00010000,
    /// l*r
    AND_ALGEBRA = 0b00010100,
    /// max(l,r)
    AND_BOUNDED = 0b00011000,
    /// max(l,r)
    OR = 0b00100000,
    /// l+r-l*r
    OR_ALGEBRA = 0b00100100,
    /// min(l,r)
    OR_BOUNDED = 0b00101000,
}

/// fuzzy proportional integral derivative controller
#[repr(C)]
pub struct FPID {
    /// proportional integral derivative controller
    pub pid: PID,
    me: *const float,
    mec: *const float,
    mkp: *const float,
    mki: *const float,
    mkd: *const float,
    idx: *mut uint,
    val: *mut float,
    /// fuzzy relational operator
    op: Option<extern "C" fn(float, float) -> float>,
    /// base proportional constant
    pub kp: float,
    /// base integral constant
    pub ki: float,
    /// base derivative constant
    pub kd: float,
}

extern "C" {
    fn a_fpid_off(ctx: *mut FPID) -> *mut FPID;
    fn a_fpid_inc(ctx: *mut FPID) -> *mut FPID;
    fn a_fpid_pos(ctx: *mut FPID, max: float) -> *mut FPID;
    fn a_fpid_kpid(ctx: *mut FPID, kp: float, ki: float, kd: float) -> *mut FPID;
    fn a_fpid_buff(ctx: *mut FPID, idx: *mut uint, val: *mut float) -> *mut FPID;
    fn a_fpid_chan(
        ctx: *mut FPID,
        num: uint,
        out: *mut float,
        fdb: *mut float,
        sum: *mut float,
        ec: *mut float,
        e: *mut float,
    ) -> *mut FPID;
    fn a_fpid_base(
        ctx: *mut FPID,
        num: uint,
        me: *const float,
        mec: *const float,
        mkp: *const float,
        mki: *const float,
        mkd: *const float,
    ) -> *mut FPID;
    fn a_fpid_init(
        ctx: *mut FPID,
        dt: float,
        col: uint,
        me: *const float,
        mec: *const float,
        mkp: *const float,
        mki: *const float,
        mkd: *const float,
        min: float,
        max: float,
    ) -> *mut FPID;
    fn a_fpid_outf(ctx: *mut FPID, set: float, fdb: float) -> float;
    fn a_fpid_outp(ctx: *mut FPID, set: *const float, fdb: *const float) -> *const float;
    fn a_fpid_zero(ctx: *mut FPID) -> *mut FPID;
    fn a_fpid_set_op(ctx: *mut FPID, op: uint);
    fn a_pid_num(ctx: *const PID) -> uint;
}

impl FPID {
    /// initialize function for fuzzy PID controller, default is turn off
    pub fn new(
        dt: float,
        col: usize,
        me: &[float],
        mec: &[float],
        mkp: &[float],
        mki: &[float],
        mkd: &[float],
        min: float,
        max: float,
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
                col as uint,
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
    pub fn pos(&mut self, max: float) -> &mut Self {
        unsafe { a_fpid_pos(self, max).as_mut().unwrap_unchecked() }
    }

    /// set proportional integral derivative constant for fuzzy PID controller
    pub fn kpid(&mut self, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_fpid_kpid(self, kp, ki, kd).as_mut().unwrap_unchecked() }
    }

    /// set buffer for fuzzy PID controller
    pub fn buff(&mut self, idx: &mut [u32], val: &mut [float]) -> &mut Self {
        unsafe {
            a_fpid_buff(self, idx.as_mut_ptr(), val.as_mut_ptr())
                .as_mut()
                .unwrap_unchecked()
        }
    }

    /// set buffer for multichannel fuzzy PID controller
    pub fn chan(
        &mut self,
        out: &mut [float],
        fdb: &mut [float],
        sum: &mut [float],
        ec: &mut [float],
        e: &mut [float],
    ) -> &mut Self {
        unsafe {
            a_fpid_chan(
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

    /// set rule base for fuzzy PID controller
    pub fn base(
        &mut self,
        col: usize,
        me: &[float],
        mec: &[float],
        mkp: &[float],
        mki: &[float],
        mkd: &[float],
    ) -> &mut Self {
        unsafe {
            a_fpid_base(
                self,
                col as uint,
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
    pub fn outf(&mut self, set: float, fdb: float) -> float {
        unsafe { a_fpid_outf(self, set, fdb) }
    }
    /// calculate function for multichannel fuzzy PID controller
    pub fn outp(&mut self, set: &[float], fdb: &[float]) -> &[float] {
        unsafe {
            std::slice::from_raw_parts(
                a_fpid_outp(self, set.as_ptr(), fdb.as_ptr()),
                a_pid_num(&self.pid) as usize,
            )
        }
    }

    /// zero function for fuzzy PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_fpid_zero(self).as_mut().unwrap_unchecked() }
    }

    /// set fuzzy relational operator for fuzzy PID controller
    pub fn set_op(&mut self, op: op) -> &mut Self {
        unsafe { a_fpid_set_op(self, op as uint) };
        self
    }

    /// get sampling time unit(s) for fuzzy PID controller
    pub fn dt(&self) -> uint {
        self.pid.mode()
    }
    /// set sampling time unit(s) for fuzzy PID controller
    pub fn set_dt(&mut self, dt: float) -> &mut Self {
        self.pid.set_dt(dt);
        self
    }

    /// get mode for fuzzy PID controller
    pub fn mode(&self) -> uint {
        self.pid.mode()
    }
    /// set mode for PID controller
    pub fn set_mode(&mut self, mode: uint) -> &mut Self {
        self.pid.set_mode(mode);
        self
    }
}

#[test]
#[allow(non_snake_case)]
fn fpid() {
    let NB: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PB: float = 3.0;
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
    let NB: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PB: float = 3.0;
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
    let NB: float = -15.0;
    let NM: float = -10.0;
    let NS: float = -5.0;
    let ZO: float = 0.0;
    let PS: float = 5.0;
    let PM: float = 10.0;
    let PB: float = 15.0;
    let mkp = [
        [NB, NB, NM, NM, NS, ZO, ZO],
        [NB, NB, NM, NS, NS, ZO, PS],
        [NM, NM, NM, NS, ZO, PS, PS],
        [NM, NM, NS, ZO, PS, PM, PM],
        [NS, NS, ZO, PS, PS, PM, PM],
        [NS, ZO, PS, PM, PM, PM, PB],
        [ZO, ZO, PM, PM, PM, PB, PB],
    ];
    let NB: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PB: float = 3.0;
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
    println!("{}", a.outf(1.0, 0.0));
    a.set_op(op::AND_ALGEBRA).zero();
    {
        let mut out: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut fdb: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut sum: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut ec: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut e: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        a.chan(&mut out, &mut fdb, &mut sum, &mut ec, &mut e);
        a.outp(&[0.1, 0.2, 0.3, 0.4], &[0.0, 0.0, 0.0, 0.0]);
        println!("{:?}", out);
    }
}
