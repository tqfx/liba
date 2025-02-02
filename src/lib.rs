/*!
An algorithm library based on C/C++

## Installation

Add this to your `Cargo.toml`:

```toml
[dependencies]
liba = "0.1"
```
*/

#![warn(missing_docs)]
#![allow(non_camel_case_types)]
#![cfg_attr(not(feature = "std"), no_std)]

/// floating-point number stored using `f64`
#[cfg(not(feature = "float"))]
pub type real = f64;
/// floating-point number stored using `f32`
#[cfg(feature = "float")]
pub type real = f32;

#[cfg(feature = "std")]
extern crate std;

#[cfg(not(feature = "std"))]
pub use core::ffi::c_int;
#[cfg(feature = "std")]
pub use std::os::raw::c_int;

#[cfg(not(feature = "std"))]
pub use core::ffi::c_uint;
#[cfg(feature = "std")]
pub use std::os::raw::c_uint;

#[cfg(not(feature = "std"))]
use core::mem::size_of;
#[cfg(feature = "std")]
use std::mem::size_of;

#[cfg(not(feature = "std"))]
use core::cmp::Ordering;
#[cfg(feature = "std")]
use std::cmp::Ordering;

#[cfg(not(feature = "std"))]
use core::ptr::{null, null_mut};
#[cfg(feature = "std")]
use std::ptr::{null, null_mut};

#[cfg(not(feature = "std"))]
use core::slice::{from_raw_parts, from_raw_parts_mut};
#[cfg(feature = "std")]
use std::slice::{from_raw_parts, from_raw_parts_mut};

extern "C" {
    fn a_u32_sqrt(x: u32) -> u16;
    fn a_u64_sqrt(x: u64) -> u32;
}

/// square root of an unsigned integer
#[inline(always)]
pub fn u32_sqrt(x: u32) -> u16 {
    unsafe { a_u32_sqrt(x) }
}
/// square root of an unsigned integer
#[inline(always)]
pub fn u64_sqrt(x: u64) -> u32 {
    unsafe { a_u64_sqrt(x) }
}

extern "C" {
    fn a_f32_rsqrt(x: f32) -> f32;
    fn a_f64_rsqrt(x: f64) -> f64;
}

/// reciprocal of square-root, `\frac{1}{\sqrt{x}}`
#[inline(always)]
pub fn f32_rsqrt(x: f32) -> f32 {
    unsafe { a_f32_rsqrt(x) }
}
/// reciprocal of square-root, `\frac{1}{\sqrt{x}}`
#[inline(always)]
pub fn f64_rsqrt(x: f64) -> f64 {
    unsafe { a_f64_rsqrt(x) }
}

extern "C" {
    fn a_real_sum(n: usize, p: *const real) -> real;
    fn a_real_sum1(n: usize, p: *const real) -> real;
    fn a_real_sum2(n: usize, p: *const real) -> real;
    fn a_real_mean(n: usize, p: *const real) -> real;
}

/// calculate the sum of a float array
#[inline(always)]
pub fn real_sum(x: &[real]) -> real {
    unsafe { a_real_sum(x.len(), x.as_ptr()) }
}
/// calculate the absolute sum of a float array
#[inline(always)]
pub fn real_sum1(x: &[real]) -> real {
    unsafe { a_real_sum1(x.len(), x.as_ptr()) }
}
/// calculate the sum of squares of a float array
#[inline(always)]
pub fn real_sum2(x: &[real]) -> real {
    unsafe { a_real_sum2(x.len(), x.as_ptr()) }
}
/// calculate the mean of a float array
#[inline(always)]
pub fn real_mean(x: &[real]) -> real {
    unsafe { a_real_mean(x.len(), x.as_ptr()) }
}

extern "C" {
    fn a_hash_bkdr_(pdata: *const u8, nbyte: usize, value: u32) -> u32;
    fn a_hash_sdbm_(pdata: *const u8, nbyte: usize, value: u32) -> u32;
}

/// a hash function whose prime number is 131
#[inline(always)]
pub fn hash_bkdr(block: &[u8], value: u32) -> u32 {
    unsafe { a_hash_bkdr_(block.as_ptr(), block.len(), value) }
}
/// a hash function whose prime number is 65599
#[inline(always)]
pub fn hash_sdbm(block: &[u8], value: u32) -> u32 {
    unsafe { a_hash_sdbm_(block.as_ptr(), block.len(), value) }
}

/// Cyclic Redundancy Check for 8 bits
#[repr(C)]
pub struct crc8 {
    /// Cyclic Redundancy Check comparison table
    pub table: [u8; 0x100],
}

extern "C" {
    fn a_crc8m_init(table: *mut u8, poly: u8);
    fn a_crc8l_init(table: *mut u8, poly: u8);
    fn a_crc8(table: *const u8, pdate: *const u8, nbyte: usize, value: u8) -> u8;
}

impl crc8 {
    /// initialize for MSB CRC-8
    #[inline(always)]
    pub fn new_msb(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-8
    #[inline(always)]
    pub fn new_lsb(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// generate for MSB CRC-8
    #[inline(always)]
    pub fn gen_msb(&mut self, poly: u8) -> &mut Self {
        unsafe { a_crc8m_init(self.table.as_mut_ptr(), poly) };
        self
    }
    /// generate for LSB CRC-8
    #[inline(always)]
    pub fn gen_lsb(&mut self, poly: u8) -> &mut Self {
        unsafe { a_crc8l_init(self.table.as_mut_ptr(), poly) };
        self
    }
    /// calculate for CRC-8
    #[inline(always)]
    pub fn eval(self, block: &[u8], value: u8) -> u8 {
        unsafe { a_crc8(self.table.as_ptr(), block.as_ptr(), block.len(), value) }
    }
}

/// Cyclic Redundancy Check for 16 bits
#[repr(C)]
pub struct crc16 {
    /// Cyclic Redundancy Check comparison table
    pub table: [u16; 0x100],
    eval: unsafe extern "C" fn(*const u16, *const u8, usize, u16) -> u16,
}

extern "C" {
    fn a_crc16m_init(table: *mut u16, poly: u16);
    fn a_crc16l_init(table: *mut u16, poly: u16);
    fn a_crc16m(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
    fn a_crc16l(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
}

impl crc16 {
    /// initialize for MSB CRC-16
    #[inline(always)]
    pub fn new_msb(poly: u16) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc16m,
        };
        unsafe { a_crc16m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-16
    #[inline(always)]
    pub fn new_lsb(poly: u16) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc16l,
        };
        unsafe { a_crc16l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// generate for MSB CRC-16
    #[inline(always)]
    pub fn gen_msb(&mut self, poly: u16) -> &mut Self {
        unsafe { a_crc16m_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc16m;
        self
    }
    /// generate for LSB CRC-16
    #[inline(always)]
    pub fn gen_lsb(&mut self, poly: u16) -> &mut Self {
        unsafe { a_crc16l_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc16l;
        self
    }
    /// calculate for CRC-16
    #[inline(always)]
    pub fn eval(self, block: &[u8], value: u16) -> u16 {
        unsafe { (self.eval)(self.table.as_ptr(), block.as_ptr(), block.len(), value) }
    }
}

/// Cyclic Redundancy Check for 32 bits
#[repr(C)]
pub struct crc32 {
    /// Cyclic Redundancy Check comparison table
    pub table: [u32; 0x100],
    eval: unsafe extern "C" fn(*const u32, *const u8, usize, u32) -> u32,
}

extern "C" {
    fn a_crc32m_init(table: *mut u32, poly: u32);
    fn a_crc32l_init(table: *mut u32, poly: u32);
    fn a_crc32m(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
    fn a_crc32l(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
}

impl crc32 {
    /// initialize for MSB CRC-32
    #[inline(always)]
    pub fn new_msb(poly: u32) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc32m,
        };
        unsafe { a_crc32m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-32
    #[inline(always)]
    pub fn new_lsb(poly: u32) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc32l,
        };
        unsafe { a_crc32l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// generate for MSB CRC-32
    #[inline(always)]
    pub fn gen_msb(&mut self, poly: u32) -> &mut Self {
        unsafe { a_crc32m_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc32m;
        self
    }
    /// generate for LSB CRC-32
    #[inline(always)]
    pub fn gen_lsb(&mut self, poly: u32) -> &mut Self {
        unsafe { a_crc32l_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc32l;
        self
    }
    /// calculate for CRC-32
    #[inline(always)]
    pub fn eval(self, block: &[u8], value: u32) -> u32 {
        unsafe { (self.eval)(self.table.as_ptr(), block.as_ptr(), block.len(), value) }
    }
}

/// Cyclic Redundancy Check for 64 bits
#[repr(C)]
pub struct crc64 {
    /// Cyclic Redundancy Check comparison table
    pub table: [u64; 0x100],
    eval: unsafe extern "C" fn(*const u64, *const u8, usize, u64) -> u64,
}

extern "C" {
    fn a_crc64m_init(table: *mut u64, poly: u64);
    fn a_crc64l_init(table: *mut u64, poly: u64);
    fn a_crc64m(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
    fn a_crc64l(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
}

impl crc64 {
    /// initialize for MSB CRC-64
    #[inline(always)]
    pub fn new_msb(poly: u64) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc64m,
        };
        unsafe { a_crc64m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-64
    #[inline(always)]
    pub fn new_lsb(poly: u64) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc64l,
        };
        unsafe { a_crc64l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// generate for MSB CRC-64
    #[inline(always)]
    pub fn gen_msb(&mut self, poly: u64) -> &mut Self {
        unsafe { a_crc64m_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc64m;
        self
    }
    /// generate for LSB CRC-64
    #[inline(always)]
    pub fn gen_lsb(&mut self, poly: u64) -> &mut Self {
        unsafe { a_crc64l_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc64l;
        self
    }
    /// calculate for CRC-64
    #[inline(always)]
    pub fn eval(self, block: &[u8], value: u64) -> u64 {
        unsafe { (self.eval)(self.table.as_ptr(), block.as_ptr(), block.len(), value) }
    }
}

#[allow(clippy::excessive_precision)]
const TAU: real = 6.28318530717958647692528676655900577;

/// High Pass Filter
#[repr(C)]
pub struct hpf {
    /// filter coefficient
    pub alpha: real,
    /// filter output
    pub output: real,
    /// filter input
    pub input: real,
}

impl hpf {
    /// initialize for High Pass Filter
    #[inline(always)]
    pub fn new(fc: real, ts: real) -> Self {
        Self {
            alpha: 1.0 / (TAU * fc * ts + 1.0),
            output: 0.0,
            input: 0.0,
        }
    }
    /// generate for High Pass Filter
    #[inline(always)]
    pub fn gen(&mut self, fc: real, ts: real) -> &mut Self {
        self.alpha = 1.0 / (TAU * fc * ts + 1.0);
        self
    }
    /// calculate for High Pass Filter
    #[inline(always)]
    pub fn iter(&mut self, x: real) -> real {
        self.output = self.alpha * (self.output + x - self.input);
        self.input = x;
        self.output
    }
    /// zeroing for High Pass Filter
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        self.output = 0.0;
        self.input = 0.0;
        self
    }
}

#[allow(clippy::excessive_precision)]
const _1_TAU: real = 0.159154943091895335768883763372514362;

/// Low Pass Filter
#[repr(C)]
pub struct lpf {
    /// filter coefficient
    pub alpha: real,
    /// filter output
    pub output: real,
}

impl lpf {
    /// initialize for Low Pass Filter
    #[inline(always)]
    pub fn new(fc: real, ts: real) -> Self {
        Self {
            alpha: ts / (_1_TAU / fc + ts),
            output: 0.0,
        }
    }
    /// generate for Low Pass Filter
    #[inline(always)]
    pub fn gen(&mut self, fc: real, ts: real) -> &mut Self {
        self.alpha = ts / (_1_TAU / fc + ts);
        self
    }
    /// calculate for Low Pass Filter
    #[inline(always)]
    pub fn iter(&mut self, x: real) -> real {
        self.output *= 1.0 - self.alpha;
        self.output += x * self.alpha;
        self.output
    }
    /// zeroing for Low Pass Filter
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        self.output = 0.0;
        self
    }
}

/// membership function
pub mod mf {
    use crate::c_int;
    /// none
    pub const NUL: c_int = 0;
    /// gaussian membership function
    pub const GAUSS: c_int = 1;
    /// gaussian combination membership function
    pub const GAUSS2: c_int = 2;
    /// generalized bell-shaped membership function
    pub const GBELL: c_int = 3;
    /// sigmoidal membership function
    pub const SIG: c_int = 4;
    /// difference between two sigmoidal membership functions
    pub const DSIG: c_int = 5;
    /// product of two sigmoidal membership functions
    pub const PSIG: c_int = 6;
    /// trapezoidal membership function
    pub const TRAP: c_int = 7;
    /// triangular membership function
    pub const TRI: c_int = 8;
    /// linear s-shaped saturation membership function
    pub const LINS: c_int = 9;
    /// linear z-shaped saturation membership function
    pub const LINZ: c_int = 10;
    /// s-shaped membership function
    pub const S: c_int = 11;
    /// z-shaped membership function
    pub const Z: c_int = 12;
    /// pi-shaped membership function
    pub const PI: c_int = 13;

    use crate::real;
    extern "C" {
        fn a_mf_gauss(x: real, sigma: real, c: real) -> real;
        fn a_mf_gauss2(x: real, sigma1: real, c1: real, sigma2: real, c2: real) -> real;
        fn a_mf_gbell(x: real, a: real, b: real, c: real) -> real;
        fn a_mf_sig(x: real, a: real, c: real) -> real;
        fn a_mf_dsig(x: real, a1: real, c1: real, a2: real, c2: real) -> real;
        fn a_mf_psig(x: real, a1: real, c1: real, a2: real, c2: real) -> real;
        fn a_mf_trap(x: real, a: real, b: real, c: real, d: real) -> real;
        fn a_mf_tri(x: real, a: real, b: real, c: real) -> real;
        fn a_mf_lins(x: real, a: real, b: real) -> real;
        fn a_mf_linz(x: real, a: real, b: real) -> real;
        fn a_mf_s(x: real, a: real, b: real) -> real;
        fn a_mf_z(x: real, a: real, b: real) -> real;
        fn a_mf_pi(x: real, a: real, b: real, c: real, d: real) -> real;
    }

    /// gaussian membership function
    #[inline(always)]
    pub fn gauss(x: real, sigma: real, c: real) -> real {
        unsafe { a_mf_gauss(x, sigma, c) }
    }
    /// gaussian combination membership function
    #[inline(always)]
    pub fn gauss2(x: real, sigma1: real, c1: real, sigma2: real, c2: real) -> real {
        unsafe { a_mf_gauss2(x, sigma1, c1, sigma2, c2) }
    }
    /// generalized bell-shaped membership function
    #[inline(always)]
    pub fn gbell(x: real, a: real, b: real, c: real) -> real {
        unsafe { a_mf_gbell(x, a, b, c) }
    }
    /// sigmoidal membership function
    #[inline(always)]
    pub fn sig(x: real, a: real, c: real) -> real {
        unsafe { a_mf_sig(x, a, c) }
    }
    /// difference between two sigmoidal membership functions
    #[inline(always)]
    pub fn dsig(x: real, a1: real, c1: real, a2: real, c2: real) -> real {
        unsafe { a_mf_dsig(x, a1, c1, a2, c2) }
    }
    /// product of two sigmoidal membership functions
    #[inline(always)]
    pub fn psig(x: real, a1: real, c1: real, a2: real, c2: real) -> real {
        unsafe { a_mf_psig(x, a1, c1, a2, c2) }
    }
    /// trapezoidal membership function
    #[inline(always)]
    pub fn trap(x: real, a: real, b: real, c: real, d: real) -> real {
        unsafe { a_mf_trap(x, a, b, c, d) }
    }
    /// triangular membership function
    #[inline(always)]
    pub fn tri(x: real, a: real, b: real, c: real) -> real {
        unsafe { a_mf_tri(x, a, b, c) }
    }
    /// linear s-shaped saturation membership function
    #[inline(always)]
    pub fn lins(x: real, a: real, b: real) -> real {
        unsafe { a_mf_lins(x, a, b) }
    }
    /// linear z-shaped saturation membership function
    #[inline(always)]
    pub fn linz(x: real, a: real, b: real) -> real {
        unsafe { a_mf_linz(x, a, b) }
    }
    /// s-shaped membership function
    #[inline(always)]
    pub fn s(x: real, a: real, b: real) -> real {
        unsafe { a_mf_s(x, a, b) }
    }
    /// z-shaped membership function
    #[inline(always)]
    pub fn z(x: real, a: real, b: real) -> real {
        unsafe { a_mf_z(x, a, b) }
    }
    /// pi-shaped membership function
    #[inline(always)]
    pub fn pi(x: real, a: real, b: real, c: real, d: real) -> real {
        unsafe { a_mf_pi(x, a, b, c, d) }
    }
}

/// proportional integral derivative controller
#[repr(C)]
pub struct pid {
    /// proportional constant
    pub kp: real,
    /// integral constant
    pub ki: real,
    /// derivative constant
    pub kd: real,
    /// maximum integral output
    pub summax: real,
    /// minimum integral output
    pub summin: real,
    /// controller integral output
    pub sum: real,
    /// maximum final output
    pub outmax: real,
    /// minimum final output
    pub outmin: real,
    /// controller final output
    pub out: real,
    /// cache variable
    var: real,
    /// cache feedback
    pub fdb: real,
    /// cache error
    pub err: real,
}

impl Default for pid {
    #[inline(always)]
    fn default() -> Self {
        Self {
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            summax: real::INFINITY,
            summin: -real::INFINITY,
            sum: 0.0,
            outmax: real::INFINITY,
            outmin: -real::INFINITY,
            out: 0.0,
            var: 0.0,
            fdb: 0.0,
            err: 0.0,
        }
    }
}

extern "C" {
    fn a_pid_set_kpid(ctx: *mut pid, kp: real, ki: real, kd: real);
    fn a_pid_run(ctx: *mut pid, set: real, fdb: real) -> real;
    fn a_pid_pos(ctx: *mut pid, set: real, fdb: real) -> real;
    fn a_pid_inc(ctx: *mut pid, set: real, fdb: real) -> real;
    fn a_pid_zero(ctx: *mut pid);
}

impl pid {
    /// initialize for PID controller
    #[inline(always)]
    pub fn new() -> Self {
        Self::default()
    }
    /// set proportional integral derivative constant for PID controller
    #[inline(always)]
    pub fn set_kpid(&mut self, kp: real, ki: real, kd: real) -> &mut Self {
        unsafe { a_pid_set_kpid(self, kp, ki, kd) };
        self
    }
    /// calculate for PID controller
    #[inline(always)]
    pub fn run(&mut self, set: real, fdb: real) -> real {
        unsafe { a_pid_run(self, set, fdb) }
    }
    /// calculate for positional PID controller
    #[inline(always)]
    pub fn pos(&mut self, set: real, fdb: real) -> real {
        unsafe { a_pid_pos(self, set, fdb) }
    }
    /// calculate for incremental PID controller
    #[inline(always)]
    pub fn inc(&mut self, set: real, fdb: real) -> real {
        unsafe { a_pid_inc(self, set, fdb) }
    }
    /// zeroing for PID controller
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_zero(self) };
        self
    }
}

/// fuzzy PID controller operator
pub mod fuzzy {
    use crate::c_uint;
    /// min(a,b)
    pub const CAP: c_uint = 1;
    /// a*b
    pub const CAP_ALGEBRA: c_uint = 2;
    /// max(a+b-1,0)
    pub const CAP_BOUNDED: c_uint = 3;
    /// max(a,b)
    pub const CUP: c_uint = 4;
    /// a+b-a*b
    pub const CUP_ALGEBRA: c_uint = 5;
    /// min(a+b,1)
    pub const CUP_BOUNDED: c_uint = 6;
    /// sqrt(a,b)*sqrt(1-(1-a)*(1-b))
    pub const EQU: c_uint = 0;
}

/// fuzzy proportional integral derivative controller
#[repr(C)]
pub struct pid_fuzzy {
    /// proportional integral derivative controller
    pub pid: pid,
    me: *const real,
    mec: *const real,
    mkp: *const real,
    mki: *const real,
    mkd: *const real,
    idx: *mut c_uint,
    val: *mut real,
    /// fuzzy relational operator
    opr: extern "C" fn(real, real) -> real,
    /// base proportional constant
    pub kp: real,
    /// base integral constant
    pub ki: real,
    /// base derivative constant
    pub kd: real,
    /// number of order in the square matrix
    nrule: c_uint,
    /// maximum number triggered by the rule
    nfuzz: c_uint,
}

impl Default for pid_fuzzy {
    #[inline(always)]
    fn default() -> Self {
        Self {
            pid: pid::default(),
            me: null(),
            mec: null(),
            mkp: null(),
            mki: null(),
            mkd: null(),
            idx: null_mut(),
            val: null_mut(),
            opr: unsafe { a_pid_fuzzy_opr(fuzzy::EQU) },
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            nrule: 0,
            nfuzz: 0,
        }
    }
}

extern "C" {
    fn a_pid_fuzzy_opr(opr: c_uint) -> extern "C" fn(real, real) -> real;
    fn a_pid_fuzzy_set_opr(ctx: *mut pid_fuzzy, opr: c_uint);
    fn a_pid_fuzzy_bfuzz(ctx: *const pid_fuzzy) -> *mut u8;
    fn a_pid_fuzzy_set_bfuzz(ctx: *mut pid_fuzzy, ptr: *mut u8, num: usize);
    fn a_pid_fuzzy_set_rule(
        ctx: *mut pid_fuzzy,
        num: c_uint,
        me: *const real,
        mec: *const real,
        mkp: *const real,
        mki: *const real,
        mkd: *const real,
    );
    fn a_pid_fuzzy_set_kpid(ctx: *mut pid_fuzzy, kp: real, ki: real, kd: real);
    fn a_pid_fuzzy_run(ctx: *mut pid_fuzzy, set: real, fdb: real) -> real;
    fn a_pid_fuzzy_pos(ctx: *mut pid_fuzzy, set: real, fdb: real) -> real;
    fn a_pid_fuzzy_inc(ctx: *mut pid_fuzzy, set: real, fdb: real) -> real;
    fn a_pid_fuzzy_zero(ctx: *mut pid_fuzzy);
}

impl pid_fuzzy {
    /// initialize for fuzzy PID controller
    #[inline(always)]
    pub fn new() -> Self {
        Self::default()
    }
    /// set fuzzy relational operator for fuzzy PID controller
    #[inline(always)]
    pub fn set_opr(&mut self, opr: c_uint) -> &mut Self {
        unsafe { a_pid_fuzzy_set_opr(self, opr) };
        self
    }
    /// compute size of memory block for fuzzy PID controller
    #[inline(always)]
    #[allow(non_snake_case)]
    pub const fn BFUZZ(n: usize) -> usize {
        size_of::<c_uint>() * n * 2 + size_of::<real>() * n * (2 + n)
    }
    /// get memory block for fuzzy PID controller
    #[inline(always)]
    pub fn bfuzz(&mut self) -> &mut [u8] {
        unsafe { from_raw_parts_mut(a_pid_fuzzy_bfuzz(self), Self::BFUZZ(self.nfuzz as usize)) }
    }
    /// set memory block for fuzzy PID controller
    #[inline(always)]
    pub fn set_bfuzz(&mut self, ptr: &mut [u8], num: usize) -> &mut Self {
        unsafe { a_pid_fuzzy_set_bfuzz(self, ptr.as_mut_ptr(), num) };
        self
    }
    /// set rule base for fuzzy PID controller
    #[inline(always)]
    pub fn set_rule(
        &mut self,
        col: usize,
        me: &[real],
        mec: &[real],
        mkp: &[real],
        mki: &[real],
        mkd: &[real],
    ) -> &mut Self {
        unsafe {
            a_pid_fuzzy_set_rule(
                self,
                col as c_uint,
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
    #[inline(always)]
    pub fn set_kpid(&mut self, kp: real, ki: real, kd: real) -> &mut Self {
        unsafe { a_pid_fuzzy_set_kpid(self, kp, ki, kd) };
        self
    }
    /// calculate for fuzzy PID controller
    #[inline(always)]
    pub fn run(&mut self, set: real, fdb: real) -> real {
        unsafe { a_pid_fuzzy_run(self, set, fdb) }
    }
    /// calculate for positional fuzzy PID controller
    #[inline(always)]
    pub fn pos(&mut self, set: real, fdb: real) -> real {
        unsafe { a_pid_fuzzy_pos(self, set, fdb) }
    }
    /// calculate for incremental fuzzy PID controller
    #[inline(always)]
    pub fn inc(&mut self, set: real, fdb: real) -> real {
        unsafe { a_pid_fuzzy_inc(self, set, fdb) }
    }
    /// zeroing for fuzzy PID controller
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_fuzzy_zero(self) };
        self
    }
}

/// single neuron proportional integral derivative controller
#[repr(C)]
pub struct pid_neuro {
    /// proportional integral derivative controller
    pub pid: pid,
    /// proportional coefficient
    pub k: real,
    /// proportional weight
    pub wp: real,
    /// integral weight
    pub wi: real,
    /// derivative weight
    pub wd: real,
    /// error change
    pub ec: real,
}

impl Default for pid_neuro {
    #[inline(always)]
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
    fn a_pid_neuro_set_kpid(ctx: *mut pid_neuro, k: real, kp: real, ki: real, kd: real);
    fn a_pid_neuro_set_wpid(ctx: *mut pid_neuro, wp: real, wi: real, wd: real);
    fn a_pid_neuro_run(ctx: *mut pid_neuro, set: real, fdb: real) -> real;
    fn a_pid_neuro_inc(ctx: *mut pid_neuro, set: real, fdb: real) -> real;
    fn a_pid_neuro_zero(ctx: *mut pid_neuro);
}

impl pid_neuro {
    /// initialize for single neuron PID controller
    #[inline(always)]
    pub fn new() -> Self {
        Self::default()
    }
    /// set proportional integral derivative constant for single neuron PID controller
    #[inline(always)]
    pub fn set_kpid(&mut self, k: real, kp: real, ki: real, kd: real) -> &mut Self {
        unsafe { a_pid_neuro_set_kpid(self, k, kp, ki, kd) };
        self
    }
    /// set proportional integral derivative weight for single neuron PID controller
    #[inline(always)]
    pub fn set_wpid(&mut self, wp: real, wi: real, wd: real) -> &mut Self {
        unsafe { a_pid_neuro_set_wpid(self, wp, wi, wd) };
        self
    }
    /// calculate for single neuron PID controller
    #[inline(always)]
    pub fn run(&mut self, set: real, fdb: real) -> real {
        unsafe { a_pid_neuro_run(self, set, fdb) }
    }
    /// calculate for incremental single neuron PID controller
    #[inline(always)]
    pub fn inc(&mut self, set: real, fdb: real) -> real {
        unsafe { a_pid_neuro_inc(self, set, fdb) }
    }
    /// zeroing for single neuron PID controller
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_neuro_zero(self) };
        self
    }
}

/// linear regression
#[repr(C)]
pub struct regress_linear {
    /// points to regression coefficients
    coef_p: *mut real,
    /// number of regression coefficients
    coef_n: usize,
    /// intercept
    pub bias: real,
}

extern "C" {
    fn a_regress_linear_eval(ctx: *const regress_linear, val: *const real) -> real;
    fn a_regress_linear_err(
        ctx: *const regress_linear,
        n: usize,
        x: *const real,
        y: *const real,
        err: *mut real,
    );
    fn a_regress_linear_pdm(
        ctx: *const regress_linear,
        n: usize,
        x: *const real,
        pdm: *mut real,
        y_mean: real,
    );
    fn a_regress_linear_gd(ctx: *mut regress_linear, input: *const real, error: real, alpha: real);
    fn a_regress_linear_sgd(
        ctx: *mut regress_linear,
        n: usize,
        x: *const real,
        y: *const real,
        alpha: real,
    );
    fn a_regress_linear_bgd(
        ctx: *mut regress_linear,
        n: usize,
        x: *const real,
        err: *const real,
        alpha: real,
    );
    fn a_regress_linear_mgd(
        ctx: *mut regress_linear,
        n: usize,
        x: *const real,
        y: *const real,
        err: *mut real,
        delta: real,
        lrmax: real,
        lrmin: real,
        lrtim: usize,
        epoch: usize,
        batch: usize,
    );
    fn a_regress_linear_zero(ctx: *mut regress_linear);
}

impl regress_linear {
    /// initialize for linear regression
    #[inline(always)]
    pub fn new(coef: &mut [real], bias: real) -> Self {
        Self {
            coef_p: coef.as_mut_ptr(),
            coef_n: coef.len(),
            bias,
        }
    }
    /// get regression coefficients for linear regression
    #[inline(always)]
    pub fn coef(&mut self) -> &mut [real] {
        unsafe { from_raw_parts_mut(self.coef_p, self.coef_n) }
    }
    /// set regression coefficients for linear regression
    #[inline(always)]
    pub fn set_coef(&mut self, coef: &mut [real]) -> &mut Self {
        self.coef_p = coef.as_mut_ptr();
        self.coef_n = coef.len();
        self
    }
    /// calculate predicted value for linear regression
    #[inline(always)]
    pub fn eval(&self, val: &[real]) -> real {
        unsafe { a_regress_linear_eval(self, val.as_ptr()) }
    }
    /// calculate residuals for linear regression
    #[inline(always)]
    pub fn err(&self, x: &[real], y: &[real], err: &mut [real]) {
        unsafe { a_regress_linear_err(self, y.len(), x.as_ptr(), y.as_ptr(), err.as_mut_ptr()) }
    }
    /// calculate prediction deviation from mean for linear regression
    #[inline(always)]
    pub fn pdm(&self, x: &[real], pdm: &mut [real], y_mean: real) {
        let n = x.len() / self.coef_n;
        unsafe { a_regress_linear_pdm(self, n, x.as_ptr(), pdm.as_mut_ptr(), y_mean) }
    }
    /// gradient descent for linear regression
    #[inline(always)]
    pub fn gd(&mut self, input: &[real], error: real, alpha: real) -> &mut Self {
        unsafe { a_regress_linear_gd(self, input.as_ptr(), error, alpha) }
        self
    }
    /// stochastic gradient descent for linear regression
    #[inline(always)]
    pub fn sgd(&mut self, x: &[real], y: &[real], alpha: real) -> &mut Self {
        unsafe { a_regress_linear_sgd(self, y.len(), x.as_ptr(), y.as_ptr(), alpha) }
        self
    }
    /// batch gradient descent for linear regression
    #[inline(always)]
    pub fn bgd(&mut self, x: &[real], err: &[real], alpha: real) -> &mut Self {
        let n = x.len() / self.coef_n;
        unsafe { a_regress_linear_bgd(self, n, x.as_ptr(), err.as_ptr(), alpha) }
        self
    }
    /// mini-batch gradient descent for linear regression
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn mgd(
        &mut self,
        x: &[real],
        y: &[real],
        err: &mut [real],
        delta: real,
        lrmax: real,
        lrmin: real,
        lrtim: usize,
        epoch: usize,
        batch: usize,
    ) -> &mut Self {
        unsafe {
            a_regress_linear_mgd(
                self,
                y.len(),
                x.as_ptr(),
                y.as_ptr(),
                err.as_mut_ptr(),
                delta,
                lrmax,
                lrmin,
                lrtim,
                epoch,
                batch,
            )
        }
        self
    }
    /// zeroing for linear regression
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_regress_linear_zero(self) };
        self
    }
}

/// simple linear regression
#[repr(C)]
pub struct regress_simple {
    /// regression coefficient
    pub coef: real,
    /// intercept
    pub bias: real,
}

extern "C" {
    fn a_regress_simple_eval(ctx: *const regress_simple, val: real) -> real;
    fn a_regress_simple_evar(ctx: *const regress_simple, val: real) -> real;
    fn a_regress_simple_ols_(
        ctx: *mut regress_simple,
        n: usize,
        x: *const real,
        y: *const real,
        x_mean: real,
        y_mean: real,
    );
    fn a_regress_simple_olsx(
        ctx: *mut regress_simple,
        n: usize,
        x: *const real,
        y: *const real,
        x_mean: real,
    );
    fn a_regress_simple_olsy(
        ctx: *mut regress_simple,
        n: usize,
        x: *const real,
        y: *const real,
        y_mean: real,
    );
    fn a_regress_simple_ols(ctx: *mut regress_simple, n: usize, x: *const real, y: *const real);
    fn a_regress_simple_zero(ctx: *mut regress_simple);
}

impl regress_simple {
    /// initialize for simple linear regression
    #[inline(always)]
    pub fn new(coef: real, bias: real) -> Self {
        Self { coef, bias }
    }
    /// calculate predicted value for simple linear regression
    #[inline(always)]
    pub fn eval(&self, val: real) -> real {
        unsafe { a_regress_simple_eval(self, val) }
    }
    /// calculate predicted value for simple linear regression
    #[inline(always)]
    pub fn evar(&self, val: real) -> real {
        unsafe { a_regress_simple_evar(self, val) }
    }
    /// ordinary least squares for simple linear regression
    #[inline(always)]
    pub fn ols_(&mut self, x: &[real], y: &[real], x_mean: real, y_mean: real) -> &mut Self {
        let n = x.len().min(y.len());
        unsafe { a_regress_simple_ols_(self, n, x.as_ptr(), y.as_ptr(), x_mean, y_mean) };
        self
    }
    /// ordinary least squares for simple linear regression
    #[inline(always)]
    pub fn olsx(&mut self, x: &[real], y: &[real], x_mean: real) -> &mut Self {
        let n = x.len().min(y.len());
        unsafe { a_regress_simple_olsx(self, n, x.as_ptr(), y.as_ptr(), x_mean) };
        self
    }
    /// ordinary least squares for simple linear regression
    #[inline(always)]
    pub fn olsy(&mut self, x: &[real], y: &[real], y_mean: real) -> &mut Self {
        let n = x.len().min(y.len());
        unsafe { a_regress_simple_olsy(self, n, x.as_ptr(), y.as_ptr(), y_mean) };
        self
    }
    /// ordinary least squares for simple linear regression
    #[inline(always)]
    pub fn ols(&mut self, x: &[real], y: &[real]) -> &mut Self {
        let n = x.len().min(y.len());
        unsafe { a_regress_simple_ols(self, n, x.as_ptr(), y.as_ptr()) };
        self
    }
    /// zeroing for simple linear regression
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_regress_simple_zero(self) };
        self
    }
}

/// transfer function
#[repr(C)]
pub struct tf {
    /// input
    input: *mut real,
    /// output
    output: *mut real,
    /// numerator
    num_p: *const real,
    /// denominator
    den_p: *const real,
    /// numerator number
    num_n: c_uint,
    /// denominator number
    den_n: c_uint,
}

extern "C" {
    fn a_tf_set_num(ctx: *mut tf, num_n: c_uint, num_p: *const real, input: *mut real);
    fn a_tf_set_den(ctx: *mut tf, den_n: c_uint, den_p: *const real, output: *mut real);
    fn a_tf_init(
        ctx: *mut tf,
        num_n: c_uint,
        num_p: *const real,
        input: *mut real,
        den_n: c_uint,
        den_p: *const real,
        output: *mut real,
    );
    fn a_tf_iter(ctx: *const tf, x: real) -> real;
    fn a_tf_zero(ctx: *const tf);
}

impl tf {
    /// initialize for transfer function
    #[inline(always)]
    pub fn new(num: &[real], input: &mut [real], den: &[real], output: &mut [real]) -> Self {
        let mut ctx: Self = Self {
            input: null_mut(),
            output: null_mut(),
            num_p: null(),
            den_p: null(),
            num_n: 0,
            den_n: 0,
        };
        unsafe {
            a_tf_init(
                &mut ctx,
                num.len() as c_uint,
                num.as_ptr(),
                input.as_mut_ptr(),
                den.len() as c_uint,
                den.as_ptr(),
                output.as_mut_ptr(),
            )
        };
        ctx
    }
    /// calculate for transfer function
    #[inline(always)]
    pub fn iter(&mut self, x: real) -> real {
        unsafe { a_tf_iter(self, x) }
    }
    /// zeroing for transfer function
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_tf_zero(self) };
        self
    }
    /// get input for transfer function
    #[inline(always)]
    pub fn input(&self) -> &[real] {
        unsafe { from_raw_parts(self.input, self.num_n as usize) }
    }
    /// get numerator for transfer function
    #[inline(always)]
    pub fn num(&self) -> &[real] {
        unsafe { from_raw_parts(self.num_p, self.num_n as usize) }
    }
    /// set numerator for transfer function
    #[inline(always)]
    pub fn set_num(&mut self, num: &[real], input: &mut [real]) -> &mut Self {
        unsafe { a_tf_set_num(self, num.len() as c_uint, num.as_ptr(), input.as_mut_ptr()) };
        self
    }
    /// get output for transfer function
    #[inline(always)]
    pub fn output(&self) -> &[real] {
        unsafe { from_raw_parts(self.output, self.den_n as usize) }
    }
    /// get denominator for transfer function
    #[inline(always)]
    pub fn den(&self) -> &[real] {
        unsafe { from_raw_parts(self.den_p, self.den_n as usize) }
    }
    /// set denominator for transfer function
    #[inline(always)]
    pub fn set_den(&mut self, den: &[real], output: &mut [real]) -> &mut Self {
        unsafe { a_tf_set_den(self, den.len() as c_uint, den.as_ptr(), output.as_mut_ptr()) };
        self
    }
}

/// bell-shaped velocity trajectory
#[repr(C)]
pub struct trajbell {
    /// total duration
    pub t: real,
    /// constant velocity phase
    pub tv: real,
    /// acceleration phase
    pub ta: real,
    /// deceleration phase
    pub td: real,
    /// time-interval in which the jerk is constant (j max or j min ) during the acceleration phase
    pub taj: real,
    /// time-interval in which the jerk is constant (j max or j min ) during the deceleration phase
    pub tdj: real,
    /// initial position
    pub p0: real,
    /// final position
    pub p1: real,
    /// initial velocity
    pub v0: real,
    /// final velocity
    pub v1: real,
    /// maximum velocity
    pub vm: real,
    /// maximum jerk
    pub jm: real,
    /// maximum acceleration
    pub am: real,
    /// maximum deceleration
    pub dm: real,
}

impl Default for trajbell {
    #[inline(always)]
    fn default() -> Self {
        Self {
            t: 0.0,
            tv: 0.0,
            ta: 0.0,
            td: 0.0,
            taj: 0.0,
            tdj: 0.0,
            p0: 0.0,
            p1: 0.0,
            v0: 0.0,
            v1: 0.0,
            vm: 0.0,
            jm: 0.0,
            am: 0.0,
            dm: 0.0,
        }
    }
}

extern "C" {
    fn a_trajbell_gen(
        ctx: *mut trajbell,
        jm: real,
        am: real,
        vm: real,
        p0: real,
        p1: real,
        v0: real,
        v1: real,
    ) -> real;
    fn a_trajbell_pos(ctx: *const trajbell, x: real) -> real;
    fn a_trajbell_vel(ctx: *const trajbell, x: real) -> real;
    fn a_trajbell_acc(ctx: *const trajbell, x: real) -> real;
    fn a_trajbell_jer(ctx: *const trajbell, x: real) -> real;
}

impl trajbell {
    /// initialize for bell-shaped velocity trajectory
    #[inline(always)]
    pub fn new() -> Self {
        Self::default()
    }
    /// generate for bell-shaped velocity trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn gen(
        &mut self,
        jm: real,
        am: real,
        vm: real,
        p0: real,
        p1: real,
        v0: real,
        v1: real,
    ) -> real {
        unsafe { a_trajbell_gen(self, jm, am, vm, p0, p1, v0, v1) }
    }
    /// calculate position for bell-shaped velocity trajectory
    #[inline(always)]
    pub fn pos(&mut self, x: real) -> real {
        unsafe { a_trajbell_pos(self, x) }
    }
    /// calculate velocity for bell-shaped velocity trajectory
    #[inline(always)]
    pub fn vel(&mut self, x: real) -> real {
        unsafe { a_trajbell_vel(self, x) }
    }
    /// calculate acceleration for bell-shaped velocity trajectory
    #[inline(always)]
    pub fn acc(&mut self, x: real) -> real {
        unsafe { a_trajbell_acc(self, x) }
    }
    /// calculate jerk for bell-shaped velocity trajectory
    #[inline(always)]
    pub fn jer(&mut self, x: real) -> real {
        unsafe { a_trajbell_jer(self, x) }
    }
}

/// cubic polynomial trajectory
#[repr(C)]
pub struct trajpoly3 {
    /// coefficients of position
    pub p: [real; 4],
    /// coefficients of velocity
    pub v: [real; 3],
    /// coefficients of acceleration
    pub a: [real; 2],
}

extern "C" {
    fn a_trajpoly3_gen(ctx: *mut trajpoly3, ts: real, p0: real, p1: real, v0: real, v1: real);
    fn a_trajpoly3_pos(ctx: *const trajpoly3, x: real) -> real;
    fn a_trajpoly3_vel(ctx: *const trajpoly3, x: real) -> real;
    fn a_trajpoly3_acc(ctx: *const trajpoly3, x: real) -> real;
}

impl trajpoly3 {
    /// initialize for cubic polynomial trajectory
    #[inline(always)]
    pub fn new(ts: real, p0: real, p1: real, v0: real, v1: real) -> Self {
        let mut ctx: Self = Self {
            p: [0.0; 4],
            v: [0.0; 3],
            a: [0.0; 2],
        };
        unsafe { a_trajpoly3_gen(&mut ctx, ts, p0, p1, v0, v1) };
        ctx
    }
    /// generate for cubic polynomial trajectory
    #[inline(always)]
    pub fn gen(&mut self, ts: real, p0: real, p1: real, v0: real, v1: real) -> &mut Self {
        unsafe { a_trajpoly3_gen(self, ts, p0, p1, v0, v1) };
        self
    }
    /// calculate position for cubic polynomial trajectory
    #[inline(always)]
    pub fn pos(&mut self, x: real) -> real {
        unsafe { a_trajpoly3_pos(self, x) }
    }
    /// calculate velocity for cubic polynomial trajectory
    #[inline(always)]
    pub fn vel(&mut self, x: real) -> real {
        unsafe { a_trajpoly3_vel(self, x) }
    }
    /// calculate acceleration for cubic polynomial trajectory
    #[inline(always)]
    pub fn acc(&mut self, x: real) -> real {
        unsafe { a_trajpoly3_acc(self, x) }
    }
}

/// quintic polynomial trajectory
#[repr(C)]
pub struct trajpoly5 {
    /// coefficients of position
    pub p: [real; 6],
    /// coefficients of velocity
    pub v: [real; 5],
    /// coefficients of acceleration
    pub a: [real; 4],
}

extern "C" {
    fn a_trajpoly5_gen(
        ctx: *mut trajpoly5,
        ts: real,
        p0: real,
        p1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
    );
    fn a_trajpoly5_pos(ctx: *const trajpoly5, x: real) -> real;
    fn a_trajpoly5_vel(ctx: *const trajpoly5, x: real) -> real;
    fn a_trajpoly5_acc(ctx: *const trajpoly5, x: real) -> real;
}

impl trajpoly5 {
    /// initialize for quintic polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn new(ts: real, p0: real, p1: real, v0: real, v1: real, a0: real, a1: real) -> Self {
        let mut ctx: Self = Self {
            p: [0.0; 6],
            v: [0.0; 5],
            a: [0.0; 4],
        };
        unsafe { a_trajpoly5_gen(&mut ctx, ts, p0, p1, v0, v1, a0, a1) };
        ctx
    }
    /// generate for quintic polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn gen(
        &mut self,
        ts: real,
        p0: real,
        p1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
    ) -> &mut Self {
        unsafe { a_trajpoly5_gen(self, ts, p0, p1, v0, v1, a0, a1) };
        self
    }
    /// calculate position for quintic polynomial trajectory
    #[inline(always)]
    pub fn pos(&mut self, x: real) -> real {
        unsafe { a_trajpoly5_pos(self, x) }
    }
    /// calculate velocity for quintic polynomial trajectory
    #[inline(always)]
    pub fn vel(&mut self, x: real) -> real {
        unsafe { a_trajpoly5_vel(self, x) }
    }
    /// calculate acceleration for quintic polynomial trajectory
    #[inline(always)]
    pub fn acc(&mut self, x: real) -> real {
        unsafe { a_trajpoly5_acc(self, x) }
    }
}

/// hepta polynomial trajectory
#[repr(C)]
pub struct trajpoly7 {
    /// coefficients of position
    pub p: [real; 8],
    /// coefficients of velocity
    pub v: [real; 7],
    /// coefficients of acceleration
    pub a: [real; 6],
    /// coefficients of jerk
    pub j: [real; 5],
}

extern "C" {
    fn a_trajpoly7_gen(
        ctx: *mut trajpoly7,
        ts: real,
        p0: real,
        p1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
        j0: real,
        j1: real,
    );
    fn a_trajpoly7_pos(ctx: *const trajpoly7, x: real) -> real;
    fn a_trajpoly7_vel(ctx: *const trajpoly7, x: real) -> real;
    fn a_trajpoly7_acc(ctx: *const trajpoly7, x: real) -> real;
    fn a_trajpoly7_jer(ctx: *const trajpoly7, x: real) -> real;
}

impl trajpoly7 {
    /// initialize for hepta polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn new(
        ts: real,
        p0: real,
        p1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
        j0: real,
        j1: real,
    ) -> Self {
        let mut ctx: Self = Self {
            p: [0.0; 8],
            v: [0.0; 7],
            a: [0.0; 6],
            j: [0.0; 5],
        };
        unsafe { a_trajpoly7_gen(&mut ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1) };
        ctx
    }
    /// generate for hepta polynomial trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn gen(
        &mut self,
        ts: real,
        p0: real,
        p1: real,
        v0: real,
        v1: real,
        a0: real,
        a1: real,
        j0: real,
        j1: real,
    ) -> &mut Self {
        unsafe { a_trajpoly7_gen(self, ts, p0, p1, v0, v1, a0, a1, j0, j1) };
        self
    }
    /// calculate position for hepta polynomial trajectory
    #[inline(always)]
    pub fn pos(&mut self, x: real) -> real {
        unsafe { a_trajpoly7_pos(self, x) }
    }
    /// calculate velocity for hepta polynomial trajectory
    #[inline(always)]
    pub fn vel(&mut self, x: real) -> real {
        unsafe { a_trajpoly7_vel(self, x) }
    }
    /// calculate acceleration for hepta polynomial trajectory
    #[inline(always)]
    pub fn acc(&mut self, x: real) -> real {
        unsafe { a_trajpoly7_acc(self, x) }
    }
    /// calculate jerk for hepta polynomial trajectory
    #[inline(always)]
    pub fn jer(&mut self, x: real) -> real {
        unsafe { a_trajpoly7_jer(self, x) }
    }
}

/// trapezoidal velocity trajectory
#[repr(C)]
pub struct trajtrap {
    /// total duration
    pub t: real,
    /// initial position
    pub p0: real,
    /// final position
    pub p1: real,
    /// initial velocity
    pub v0: real,
    /// final velocity
    pub v1: real,
    /// constant velocity
    pub vc: real,
    /// time before constant velocity
    pub ta: real,
    /// time after constant velocity
    pub td: real,
    /// position before constant velocity
    pub pa: real,
    /// position after constant velocity
    pub pd: real,
    /// acceleration before constant velocity
    pub ac: real,
    /// acceleration after constant velocity
    pub de: real,
}

impl Default for trajtrap {
    #[inline(always)]
    fn default() -> Self {
        Self {
            t: 0.0,
            p0: 0.0,
            p1: 0.0,
            v0: 0.0,
            v1: 0.0,
            vc: 0.0,
            ta: 0.0,
            td: 0.0,
            pa: 0.0,
            pd: 0.0,
            ac: 0.0,
            de: 0.0,
        }
    }
}

extern "C" {
    fn a_trajtrap_gen(
        ctx: *mut trajtrap,
        vm: real,
        ac: real,
        de: real,
        p0: real,
        p1: real,
        v0: real,
        v1: real,
    ) -> real;
    fn a_trajtrap_pos(ctx: *const trajtrap, x: real) -> real;
    fn a_trajtrap_vel(ctx: *const trajtrap, x: real) -> real;
    fn a_trajtrap_acc(ctx: *const trajtrap, x: real) -> real;
}

impl trajtrap {
    /// initialize for trapezoidal velocity trajectory
    #[inline(always)]
    pub fn new() -> Self {
        Self::default()
    }
    /// generate for trapezoidal velocity trajectory
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub fn gen(
        &mut self,
        vm: real,
        ac: real,
        de: real,
        p0: real,
        p1: real,
        v0: real,
        v1: real,
    ) -> real {
        unsafe { a_trajtrap_gen(self, vm, ac, de, p0, p1, v0, v1) }
    }
    /// calculate position for trapezoidal velocity trajectory
    #[inline(always)]
    pub fn pos(&mut self, x: real) -> real {
        unsafe { a_trajtrap_pos(self, x) }
    }
    /// calculate velocity for trapezoidal velocity trajectory
    #[inline(always)]
    pub fn vel(&mut self, x: real) -> real {
        unsafe { a_trajtrap_vel(self, x) }
    }
    /// calculate acceleration for trapezoidal velocity trajectory
    #[inline(always)]
    pub fn acc(&mut self, x: real) -> real {
        unsafe { a_trajtrap_acc(self, x) }
    }
}

/// version
#[repr(C)]
pub struct version {
    /// major number
    pub major: c_uint,
    /// minor number
    pub minor: c_uint,
    /// third number
    pub third: c_uint,
    /// extra number
    pub extra: c_uint,
    /// alphabet
    pub alpha: [u8; 4],
}

impl Default for version {
    #[inline(always)]
    fn default() -> Self {
        Self {
            major: 0,
            minor: 0,
            third: 0,
            extra: 0,
            alpha: [b'.', 0, 0, 0],
        }
    }
}

extern "C" {
    static a_version_major: c_uint;
    static a_version_minor: c_uint;
    static a_version_patch: c_uint;
    static a_version_tweak: u32;
    fn a_version_set_alpha(ctx: *mut version, alpha: *const u8);
    fn a_version_alpha(ctx: *const version, alpha: &mut [u8; 5]);
    fn a_version_parse(ctx: *mut version, ver: *const u8) -> c_uint;
    fn a_version_tostr(ctx: *const version, p: *mut u8, n: usize) -> c_int;
    fn a_version_cmp(ctx: *const version, rhs: *const version) -> c_int;
    fn a_version_lt(ctx: *const version, rhs: *const version) -> bool;
    fn a_version_gt(ctx: *const version, rhs: *const version) -> bool;
    fn a_version_le(ctx: *const version, rhs: *const version) -> bool;
    fn a_version_ge(ctx: *const version, rhs: *const version) -> bool;
    fn a_version_eq(ctx: *const version, rhs: *const version) -> bool;
    fn a_version_check(major: c_uint, minor: c_uint, patch: c_uint) -> c_int;
}

impl version {
    /// initialize for version
    #[inline(always)]
    pub fn new(major: c_uint, minor: c_uint, third: c_uint) -> Self {
        Self {
            major,
            minor,
            third,
            ..Default::default()
        }
    }
    /// set alphabet for version
    #[inline(always)]
    pub fn set_alpha(&mut self, alpha: &[u8]) {
        unsafe { a_version_set_alpha(self, alpha.as_ptr()) }
    }
    /// get alphabet for version
    #[inline(always)]
    pub fn alpha(&self, alpha: &mut [u8; 5]) {
        unsafe { a_version_alpha(self, alpha) }
    }
    /// parse version string to version
    #[inline(always)]
    pub fn parse(&mut self, ver: &str) -> c_uint {
        unsafe { a_version_parse(self, ver.as_ptr()) }
    }
    /// convert version to string
    #[inline(always)]
    pub fn tostr(&mut self, ver: &mut [u8]) -> c_int {
        unsafe { a_version_tostr(self, ver.as_mut_ptr(), ver.len()) }
    }
    /// algorithm library version check
    #[inline(always)]
    pub fn check(major: c_uint, minor: c_uint, patch: c_uint) -> c_int {
        unsafe { a_version_check(major, minor, patch) }
    }
    /// algorithm library version major
    #[inline(always)]
    pub fn major() -> c_uint {
        unsafe { a_version_major }
    }
    /// algorithm library version minor
    #[inline(always)]
    pub fn minor() -> c_uint {
        unsafe { a_version_minor }
    }
    /// algorithm library version patch
    #[inline(always)]
    pub fn patch() -> c_uint {
        unsafe { a_version_patch }
    }
    /// algorithm library version tweak
    #[inline(always)]
    pub fn tweak() -> u32 {
        unsafe { a_version_tweak }
    }
}

impl PartialOrd for version {
    #[inline(always)]
    fn partial_cmp(&self, other: &version) -> Option<Ordering> {
        let ok: c_int = unsafe { a_version_cmp(self, other) };
        if ok > 0 {
            return Some(Ordering::Greater);
        }
        if ok < 0 {
            return Some(Ordering::Less);
        }
        Some(Ordering::Equal)
    }
    #[inline(always)]
    fn lt(&self, other: &version) -> bool {
        unsafe { a_version_lt(self, other) }
    }
    #[inline(always)]
    fn gt(&self, other: &version) -> bool {
        unsafe { a_version_gt(self, other) }
    }
    #[inline(always)]
    fn le(&self, other: &version) -> bool {
        unsafe { a_version_le(self, other) }
    }
    #[inline(always)]
    fn ge(&self, other: &version) -> bool {
        unsafe { a_version_ge(self, other) }
    }
}

impl PartialEq for version {
    #[inline(always)]
    fn eq(&self, other: &version) -> bool {
        unsafe { a_version_eq(self, other) }
    }
}
