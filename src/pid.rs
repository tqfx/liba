//! proportional integral derivative controller

use crate::float;
use crate::uint;

/// turn off PID controller
pub const OFF: uint = 0;
/// positional PID controller
pub const POS: uint = 1;
/// incremental PID controller
pub const INC: uint = 2;

/// proportional integral derivative controller
#[repr(C)]
pub struct pid {
    /// proportional constant
    pub kp: float,
    /// integral constant
    pub ki: float,
    /// derivative constant
    pub kd: float,
    /// maximum integral output
    pub summax: float,
    /// minimum integral output
    pub summin: float,
    /// controller integral output
    pub sum: float,
    /// maximum output
    pub outmax: float,
    /// minimum output
    pub outmin: float,
    /// controller output
    pub out: float,
    /// cache feedback
    pub fdb: float,
    /// cache variable
    pub(crate) var: float,
    /// cache error
    pub err: float,
}

impl Default for pid {
    fn default() -> Self {
        Self {
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            summax: float::INFINITY,
            summin: -float::INFINITY,
            sum: 0.0,
            outmax: float::INFINITY,
            outmin: -float::INFINITY,
            out: 0.0,
            fdb: 0.0,
            var: 0.0,
            err: 0.0,
        }
    }
}

extern "C" {
    fn a_pid_kpid(ctx: *mut pid, kp: float, ki: float, kd: float);
    fn a_pid_off(ctx: *mut pid, set: float, fdb: float) -> float;
    fn a_pid_pos(ctx: *mut pid, set: float, fdb: float) -> float;
    fn a_pid_inc(ctx: *mut pid, set: float, fdb: float) -> float;
    fn a_pid_zero(ctx: *mut pid);
}

impl pid {
    /// initialize for PID controller
    pub fn new() -> Self {
        Self { ..Self::default() }
    }
    /// set proportional integral derivative constant for PID controller
    pub fn kpid(&mut self, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_kpid(self, kp, ki, kd) };
        self
    }
    /// calculate for PID controller
    pub fn off(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_off(self, set, fdb) }
    }
    /// calculate for positional PID controller
    pub fn pos(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_pos(self, set, fdb) }
    }
    /// calculate for incremental PID controller
    pub fn inc(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_inc(self, set, fdb) }
    }
    /// zeroing for PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_zero(self) };
        self
    }
}

#[test]
fn pid() {
    extern crate std;
    let mut a = crate::pid::pid::new();
    a.kpid(10.0, 0.1, 1.0);
    std::println!("{}", a.zero().pos(1.0, 0.0));
    std::println!("{}", a.zero().inc(1.0, 0.0));
}

/// fuzzy PID controller operator
pub mod fuzzy {
    use crate::uint;
    /// min(a,b)
    pub const CAP: uint = 1;
    /// a*b
    pub const CAP_ALGEBRA: uint = 2;
    /// max(a+b-1,0)
    pub const CAP_BOUNDED: uint = 3;
    /// max(a,b)
    pub const CUP: uint = 4;
    /// a+b-a*b
    pub const CUP_ALGEBRA: uint = 5;
    /// min(a+b,1)
    pub const CUP_BOUNDED: uint = 6;
    /// sqrt(a,b)*sqrt(1-(1-a)*(1-b))
    pub const EQU: uint = 0;
}

#[macro_export]
/// compute size of joint buffer for fuzzy PID controller
macro_rules! PID_FUZZY_JOINT {
    ($n:expr) => {{
        core::mem::size_of::<uint>() * $n * 2 + core::mem::size_of::<float>() * $n * (2 + $n)
    }};
}

/// fuzzy proportional integral derivative controller
#[repr(C)]
pub struct pid_fuzzy {
    /// proportional integral derivative controller
    pub pid: crate::pid::pid,
    pub(crate) me: *const float,
    pub(crate) mec: *const float,
    pub(crate) mkp: *const float,
    pub(crate) mki: *const float,
    pub(crate) mkd: *const float,
    pub(crate) idx: *mut uint,
    pub(crate) val: *mut float,
    /// fuzzy relational operator
    pub(crate) op: extern "C" fn(float, float) -> float,
    /// base proportional constant
    pub kp: float,
    /// base integral constant
    pub ki: float,
    /// base derivative constant
    pub kd: float,
    /// number of order in the square matrix
    pub(crate) order: uint,
    /// maximum number triggered by the rule
    pub(crate) joint: uint,
}

impl Default for pid_fuzzy {
    fn default() -> Self {
        Self {
            pid: pid::default(),
            me: core::ptr::null(),
            mec: core::ptr::null(),
            mkp: core::ptr::null(),
            mki: core::ptr::null(),
            mkd: core::ptr::null(),
            idx: core::ptr::null_mut(),
            val: core::ptr::null_mut(),
            op: unsafe { a_pid_fuzzy_op(fuzzy::EQU) },
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            order: 0,
            joint: 0,
        }
    }
}

extern "C" {
    fn a_pid_fuzzy_op(op: uint) -> extern "C" fn(float, float) -> float;
    fn a_pid_fuzzy_set_op(ctx: *mut pid_fuzzy, op: uint);
    fn a_pid_fuzzy_rule(
        ctx: *mut pid_fuzzy,
        num: uint,
        me: *const float,
        mec: *const float,
        mkp: *const float,
        mki: *const float,
        mkd: *const float,
    );
    fn a_pid_fuzzy_joint(ctx: *mut pid_fuzzy) -> *mut u8;
    fn a_pid_fuzzy_set_joint(ctx: *mut pid_fuzzy, ptr: *mut u8, num: usize);
    fn a_pid_fuzzy_kpid(ctx: *mut pid_fuzzy, kp: float, ki: float, kd: float);
    fn a_pid_fuzzy_off(ctx: *mut pid_fuzzy, set: float, fdb: float) -> float;
    fn a_pid_fuzzy_pos(ctx: *mut pid_fuzzy, set: float, fdb: float) -> float;
    fn a_pid_fuzzy_inc(ctx: *mut pid_fuzzy, set: float, fdb: float) -> float;
    fn a_pid_fuzzy_zero(ctx: *mut pid_fuzzy);
}

impl pid_fuzzy {
    /// initialize for fuzzy PID controller
    pub fn new() -> Self {
        Self { ..Self::default() }
    }
    /// set rule base for fuzzy PID controller
    pub fn rule(
        &mut self,
        col: usize,
        me: &[float],
        mec: &[float],
        mkp: &[float],
        mki: &[float],
        mkd: &[float],
    ) -> &mut Self {
        unsafe {
            a_pid_fuzzy_rule(
                self,
                col as uint,
                me.as_ptr(),
                mec.as_ptr(),
                mkp.as_ptr(),
                mki.as_ptr(),
                mkd.as_ptr(),
            )
        };
        self
    }
    /// set proportional integral derivative constant for fuzzy PID controller
    pub fn kpid(&mut self, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_fuzzy_kpid(self, kp, ki, kd) };
        self
    }
    /// set joint buffer for fuzzy PID controller
    pub fn set_joint(&mut self, ptr: &mut [u8], num: usize) -> &mut Self {
        unsafe { a_pid_fuzzy_set_joint(self, ptr.as_mut_ptr(), num) };
        self
    }
    /// get joint buffer for fuzzy PID controller
    pub fn joint(&mut self) -> &mut [u8] {
        unsafe {
            core::slice::from_raw_parts_mut(
                a_pid_fuzzy_joint(self),
                PID_FUZZY_JOINT!(self.joint as usize),
            )
        }
    }
    /// set fuzzy relational operator for fuzzy PID controller
    pub fn op(&mut self, op: uint) -> &mut Self {
        unsafe { a_pid_fuzzy_set_op(self, op) };
        self
    }
    /// calculate for fuzzy PID controller
    pub fn off(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_fuzzy_off(self, set, fdb) }
    }
    /// calculate for positional fuzzy PID controller
    pub fn pos(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_fuzzy_pos(self, set, fdb) }
    }
    /// calculate for incremental fuzzy PID controller
    pub fn inc(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_fuzzy_inc(self, set, fdb) }
    }
    /// zeroing for fuzzy PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_fuzzy_zero(self) };
        self
    }
}

#[test]
#[allow(non_snake_case)]
fn pid_fuzzy() {
    extern crate std;
    let NL: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PL: float = 3.0;
    let me = [
        [crate::mf::TRI as float, NL, NL, NM],
        [crate::mf::TRI as float, NL, NM, NS],
        [crate::mf::TRI as float, NM, NS, ZO],
        [crate::mf::TRI as float, NS, ZO, PS],
        [crate::mf::TRI as float, ZO, PS, PM],
        [crate::mf::TRI as float, PS, PM, PL],
        [crate::mf::TRI as float, PM, PL, PL],
    ];
    let NL: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PL: float = 3.0;
    let mec = [
        [crate::mf::TRI as float, NL, NL, NM],
        [crate::mf::TRI as float, NL, NM, NS],
        [crate::mf::TRI as float, NM, NS, ZO],
        [crate::mf::TRI as float, NS, ZO, PS],
        [crate::mf::TRI as float, ZO, PS, PM],
        [crate::mf::TRI as float, PS, PM, PL],
        [crate::mf::TRI as float, PM, PL, PL],
    ];
    let NL: float = -15.0;
    let NM: float = -10.0;
    let NS: float = -5.0;
    let ZO: float = 0.0;
    let PS: float = 5.0;
    let PM: float = 10.0;
    let PL: float = 15.0;
    let mkp = [
        [NL, NL, NM, NM, NS, ZO, ZO],
        [NL, NL, NM, NS, NS, ZO, PS],
        [NM, NM, NM, NS, ZO, PS, PS],
        [NM, NM, NS, ZO, PS, PM, PM],
        [NS, NS, ZO, PS, PS, PM, PM],
        [NS, ZO, PS, PM, PM, PM, PL],
        [ZO, ZO, PM, PM, PM, PL, PL],
    ];
    let NL: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PL: float = 3.0;
    let mki = [
        [PL, PL, PM, PM, PS, ZO, ZO],
        [PL, PL, PM, PS, PS, ZO, ZO],
        [PL, PM, PS, PS, ZO, NS, NS],
        [PM, PM, PS, ZO, NS, NM, NM],
        [PM, PS, ZO, NS, NS, NM, NL],
        [ZO, ZO, NS, NS, NM, NL, NL],
        [ZO, ZO, NS, NM, NM, NL, NL],
    ];
    let mkd = [
        [NS, PS, PL, PL, PL, PM, NS],
        [NS, PS, PL, PM, PM, PS, ZO],
        [ZO, PS, PM, PM, PS, PS, ZO],
        [ZO, PS, PS, PS, PS, PS, ZO],
        [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
        [NL, NS, NS, NS, NS, NS, NL],
        [NL, NM, NM, NM, NS, NS, NL],
    ];
    let mut joint = [0u8; crate::PID_FUZZY_JOINT!(2)];
    let mut a = pid_fuzzy::new();
    a.rule(
        me.len(),
        &me.concat(),
        &mec.concat(),
        &mkp.concat(),
        &mki.concat(),
        &mkd.concat(),
    )
    .kpid(10.0, 0.1, 1.0)
    .set_joint(&mut joint, 2);
    a.op(crate::pid::fuzzy::EQU).zero();
    std::println!("{} {}", a.pos(1.0, 0.0), a.pos(1.0, 0.0));
    a.op(crate::pid::fuzzy::EQU).zero();
    std::println!("{} {}", a.inc(1.0, 0.0), a.inc(1.0, 0.0));
}

/// single neuron proportional integral derivative controller
#[repr(C)]
pub struct pid_neuron {
    /// proportional integral derivative controller
    pub pid: crate::pid::pid,
    /// proportional coefficient
    pub k: float,
    /// proportional weight
    pub wp: float,
    /// integral weight
    pub wi: float,
    /// derivative weight
    pub wd: float,
    /// error change
    pub ec: float,
}

impl Default for pid_neuron {
    fn default() -> Self {
        Self {
            pid: pid::default(),
            k: 0.0,
            wp: 0.0,
            wi: 0.0,
            wd: 0.0,
            ec: 0.0,
        }
    }
}

extern "C" {
    fn a_pid_neuron_kpid(ctx: *mut pid_neuron, k: float, kp: float, ki: float, kd: float);
    fn a_pid_neuron_wpid(ctx: *mut pid_neuron, wp: float, wi: float, wd: float);
    fn a_pid_neuron_off(ctx: *mut pid_neuron, set: float, fdb: float) -> float;
    fn a_pid_neuron_inc(ctx: *mut pid_neuron, set: float, fdb: float) -> float;
    fn a_pid_neuron_zero(ctx: *mut pid_neuron);
}

impl pid_neuron {
    /// initialize for single neuron PID controller
    pub fn new() -> Self {
        Self { ..Self::default() }
    }
    /// set proportional integral derivative constant for single neuron PID controller
    pub fn kpid(&mut self, k: float, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_neuron_kpid(self, k, kp, ki, kd) };
        self
    }
    /// set proportional integral derivative weight for single neuron PID controller
    pub fn wpid(&mut self, wp: float, wi: float, wd: float) -> &mut Self {
        unsafe { a_pid_neuron_wpid(self, wp, wi, wd) };
        self
    }
    /// calculate for single neuron PID controller
    pub fn off(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_neuron_off(self, set, fdb) }
    }
    /// calculate for incremental single neuron PID controller
    pub fn inc(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_neuron_inc(self, set, fdb) }
    }
    /// zeroing for single neuron PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_neuron_zero(self) };
        self
    }
}

#[test]
fn pid_neuron() {
    extern crate std;
    let mut a = crate::pid::pid_neuron::new();
    a.kpid(10.0, 1.0, 0.1, 1.0).wpid(1.0, 0.0, 0.0);
    std::println!("{}", a.inc(1.0, 0.0));
    a.zero();
}
