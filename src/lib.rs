/*!
An algorithm library based on C/C++ language

## Installation

Add this to your `Cargo.toml`:

```toml
[dependencies]
liba = "0.1"
```
*/

#![warn(missing_docs)]
#![allow(non_camel_case_types)]
#![cfg_attr(not(features = "std"), no_std)]

/// Equivalent to C’s int type.
pub type int = core::ffi::c_int;
/// Equivalent to C’s unsigned int type.
pub type uint = core::ffi::c_uint;
/// floating-point number stored using `f64`
#[cfg(not(feature = "float"))]
pub type float = f64;
/// floating-point number stored using `f32`
#[cfg(feature = "float")]
pub type float = f32;

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

/// reciprocal of square-root, $ \frac{1}{\sqrt{x}} $
#[inline(always)]
pub fn f32_rsqrt(x: f32) -> f32 {
    unsafe { a_f32_rsqrt(x) }
}
/// reciprocal of square-root, $ \frac{1}{\sqrt{x}} $
#[inline(always)]
pub fn f64_rsqrt(x: f64) -> f64 {
    unsafe { a_f64_rsqrt(x) }
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

mod test {
    extern crate std;
    #[test]
    fn usqrt() {
        std::println!("{}", crate::u32_sqrt(u32::MAX));
        std::println!("{}", crate::u64_sqrt(u64::MAX));
    }
    #[test]
    fn rsqrt() {
        std::println!("1/sqrt({})={}", 4, crate::f32_rsqrt(4.0));
        std::println!("1/sqrt({})={}", 4, crate::f64_rsqrt(4.0));
    }
    #[test]
    fn hash() {
        let text: [u8; 10] = *b"0123456789";
        std::println!("{}", crate::hash_bkdr(&text, 0));
        std::println!("{}", crate::hash_sdbm(&text, 0));
    }
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

#[test]
fn crc8() {
    extern crate std;
    {
        let ctx = crate::crc8::new_msb(0x07);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x45);
    }
    {
        let ctx = crate::crc8::new_lsb(0x31);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x75);
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

#[test]
fn crc16() {
    extern crate std;
    {
        let ctx = crate::crc16::new_msb(0x1021);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x9C58);
    }
    {
        let ctx = crate::crc16::new_lsb(0x8005);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x443D);
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

#[test]
fn crc32() {
    extern crate std;
    {
        let ctx = crate::crc32::new_msb(0x1EDC6F41);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x512B456E);
    }
    {
        let ctx = crate::crc32::new_lsb(0x04C11DB7);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x450EAFB0);
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

#[test]
fn crc64() {
    extern crate std;
    {
        let ctx = crate::crc64::new_msb(0x000000000000001B);
        assert_eq!(ctx.eval(b"0123456789", 0), 0xE4FFBEA588AFC790);
    }
    {
        let ctx = crate::crc64::new_lsb(0x42F0E1EBA9EA3693);
        assert_eq!(ctx.eval(b"0123456789", 0), 0xDA60676A5CDE0008);
    }
}

#[allow(clippy::excessive_precision)]
const TAU: float = 6.28318530717958647692528676655900577;

/// High Pass Filter
#[repr(C)]
pub struct hpf {
    /// filter coefficient
    pub alpha: float,
    /// filter output
    pub output: float,
    /// filter input
    pub input: float,
}

impl hpf {
    /// initialize for High Pass Filter
    #[inline(always)]
    pub fn new(fc: float, ts: float) -> Self {
        Self {
            alpha: 1.0 / (TAU * fc * ts + 1.0),
            output: 0.0,
            input: 0.0,
        }
    }
    /// generate for High Pass Filter
    #[inline(always)]
    pub fn gen(&mut self, fc: float, ts: float) -> &mut Self {
        self.alpha = 1.0 / (TAU * fc * ts + 1.0);
        self
    }
    /// calculate for High Pass Filter
    #[inline(always)]
    pub fn iter(&mut self, x: float) -> float {
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

#[test]
fn hpf() {
    extern crate std;
    let mut a = crate::hpf::new(10.0, 0.01);
    a.gen(10.0, 0.01).zero().iter(1.0);
}

#[allow(clippy::excessive_precision)]
const _1_TAU: float = 0.159154943091895335768883763372514362;

/// Low Pass Filter
#[repr(C)]
pub struct lpf {
    /// filter coefficient
    pub alpha: float,
    /// filter output
    pub output: float,
}

impl lpf {
    /// initialize for Low Pass Filter
    #[inline(always)]
    pub fn new(fc: float, ts: float) -> Self {
        Self {
            alpha: ts / (_1_TAU / fc + ts),
            output: 0.0,
        }
    }
    /// generate for Low Pass Filter
    #[inline(always)]
    pub fn gen(&mut self, fc: float, ts: float) -> &mut Self {
        self.alpha = ts / (_1_TAU / fc + ts);
        self
    }
    /// calculate for Low Pass Filter
    #[inline(always)]
    pub fn iter(&mut self, x: float) -> float {
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

#[test]
fn lpf() {
    extern crate std;
    let mut a = crate::lpf::new(10.0, 0.01);
    a.gen(10.0, 0.01).zero().iter(1.0);
}

/// membership function
pub mod mf {
    use crate::int;
    /// none
    pub const NUL: int = 0;
    /// gaussian membership function
    pub const GAUSS: int = 1;
    /// gaussian combination membership function
    pub const GAUSS2: int = 2;
    /// generalized bell-shaped membership function
    pub const GBELL: int = 3;
    /// sigmoidal membership function
    pub const SIG: int = 4;
    /// difference between two sigmoidal membership functions
    pub const DSIG: int = 5;
    /// product of two sigmoidal membership functions
    pub const PSIG: int = 6;
    /// trapezoidal membership function
    pub const TRAP: int = 7;
    /// triangular membership function
    pub const TRI: int = 8;
    /// linear s-shaped saturation membership function
    pub const LINS: int = 9;
    /// linear z-shaped saturation membership function
    pub const LINZ: int = 10;
    /// s-shaped membership function
    pub const S: int = 11;
    /// z-shaped membership function
    pub const Z: int = 12;
    /// pi-shaped membership function
    pub const PI: int = 13;

    use crate::float;
    extern "C" {
        fn a_mf_gauss(x: float, sigma: float, c: float) -> float;
        fn a_mf_gauss2(x: float, sigma1: float, c1: float, sigma2: float, c2: float) -> float;
        fn a_mf_gbell(x: float, a: float, b: float, c: float) -> float;
        fn a_mf_sig(x: float, a: float, c: float) -> float;
        fn a_mf_dsig(x: float, a1: float, c1: float, a2: float, c2: float) -> float;
        fn a_mf_psig(x: float, a1: float, c1: float, a2: float, c2: float) -> float;
        fn a_mf_trap(x: float, a: float, b: float, c: float, d: float) -> float;
        fn a_mf_tri(x: float, a: float, b: float, c: float) -> float;
        fn a_mf_lins(x: float, a: float, b: float) -> float;
        fn a_mf_linz(x: float, a: float, b: float) -> float;
        fn a_mf_s(x: float, a: float, b: float) -> float;
        fn a_mf_z(x: float, a: float, b: float) -> float;
        fn a_mf_pi(x: float, a: float, b: float, c: float, d: float) -> float;
    }

    /// gaussian membership function
    #[inline(always)]
    pub fn gauss(x: float, sigma: float, c: float) -> float {
        unsafe { a_mf_gauss(x, sigma, c) }
    }
    /// gaussian combination membership function
    #[inline(always)]
    pub fn gauss2(x: float, sigma1: float, c1: float, sigma2: float, c2: float) -> float {
        unsafe { a_mf_gauss2(x, sigma1, c1, sigma2, c2) }
    }
    /// generalized bell-shaped membership function
    #[inline(always)]
    pub fn gbell(x: float, a: float, b: float, c: float) -> float {
        unsafe { a_mf_gbell(x, a, b, c) }
    }
    /// sigmoidal membership function
    #[inline(always)]
    pub fn sig(x: float, a: float, c: float) -> float {
        unsafe { a_mf_sig(x, a, c) }
    }
    /// difference between two sigmoidal membership functions
    #[inline(always)]
    pub fn dsig(x: float, a1: float, c1: float, a2: float, c2: float) -> float {
        unsafe { a_mf_dsig(x, a1, c1, a2, c2) }
    }
    /// product of two sigmoidal membership functions
    #[inline(always)]
    pub fn psig(x: float, a1: float, c1: float, a2: float, c2: float) -> float {
        unsafe { a_mf_psig(x, a1, c1, a2, c2) }
    }
    /// trapezoidal membership function
    #[inline(always)]
    pub fn trap(x: float, a: float, b: float, c: float, d: float) -> float {
        unsafe { a_mf_trap(x, a, b, c, d) }
    }
    /// triangular membership function
    #[inline(always)]
    pub fn tri(x: float, a: float, b: float, c: float) -> float {
        unsafe { a_mf_tri(x, a, b, c) }
    }
    /// linear s-shaped saturation membership function
    #[inline(always)]
    pub fn lins(x: float, a: float, b: float) -> float {
        unsafe { a_mf_lins(x, a, b) }
    }
    /// linear z-shaped saturation membership function
    #[inline(always)]
    pub fn linz(x: float, a: float, b: float) -> float {
        unsafe { a_mf_linz(x, a, b) }
    }
    /// s-shaped membership function
    #[inline(always)]
    pub fn s(x: float, a: float, b: float) -> float {
        unsafe { a_mf_s(x, a, b) }
    }
    /// z-shaped membership function
    #[inline(always)]
    pub fn z(x: float, a: float, b: float) -> float {
        unsafe { a_mf_z(x, a, b) }
    }
    /// pi-shaped membership function
    #[inline(always)]
    pub fn pi(x: float, a: float, b: float, c: float, d: float) -> float {
        unsafe { a_mf_pi(x, a, b, c, d) }
    }

    #[cfg(test)]
    mod test {
        extern crate std;
        #[test]
        fn gauss2() {
            for i in -4..=4 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::gauss2(x, 1.0, -1.0, 1.0, 1.0));
            }
        }
        #[test]
        fn gbell() {
            for i in -4..=4 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::gbell(x, 2.0, 4.0, 0.0));
            }
        }
        #[test]
        fn sig() {
            for i in -4..=4 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::sig(x, 2.0, 0.0));
            }
        }
        #[test]
        fn dsig() {
            for i in -4..=4 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::dsig(x, 5.0, -2.0, 5.0, 2.0));
            }
        }
        #[test]
        fn psig() {
            for i in -4..=4 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::psig(x, 5.0, -2.0, -5.0, 2.0));
            }
        }
        #[test]
        fn trap() {
            for i in -3..=3 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::trap(x, -2.0, -1.0, 1.0, 2.0));
            }
        }
        #[test]
        fn tri() {
            for i in -2..=2 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::tri(x, -1.0, 0.0, 1.0));
            }
        }
        #[test]
        fn lins() {
            for i in -2..=2 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::lins(x, -1.0, 1.0));
            }
        }
        #[test]
        fn linz() {
            for i in -2..=2 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::linz(x, -1.0, 1.0));
            }
        }
        #[test]
        fn s() {
            for i in -2..=2 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::s(x, -1.0, 1.0));
            }
        }
        #[test]
        fn z() {
            for i in -2..=2 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::z(x, -1.0, 1.0));
            }
        }
        #[test]
        fn pi() {
            for i in -3..=3 {
                let x = i as crate::float;
                std::println!("{:+} {}", x, crate::mf::pi(x, -2.0, -1.0, 1.0, 2.0));
            }
        }
    }
}

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
    #[inline(always)]
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
    fn a_pid_run(ctx: *mut pid, set: float, fdb: float) -> float;
    fn a_pid_pos(ctx: *mut pid, set: float, fdb: float) -> float;
    fn a_pid_inc(ctx: *mut pid, set: float, fdb: float) -> float;
    fn a_pid_zero(ctx: *mut pid);
}

impl pid {
    /// initialize for PID controller
    #[inline(always)]
    pub fn new() -> Self {
        Self { ..Self::default() }
    }
    /// set proportional integral derivative constant for PID controller
    #[inline(always)]
    pub fn kpid(&mut self, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_kpid(self, kp, ki, kd) };
        self
    }
    /// calculate for PID controller
    #[inline(always)]
    pub fn run(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_run(self, set, fdb) }
    }
    /// calculate for positional PID controller
    #[inline(always)]
    pub fn pos(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_pos(self, set, fdb) }
    }
    /// calculate for incremental PID controller
    #[inline(always)]
    pub fn inc(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_inc(self, set, fdb) }
    }
    /// zeroing for PID controller
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_zero(self) };
        self
    }
}

#[test]
fn pid() {
    extern crate std;
    let mut a = crate::pid::new();
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
    pub pid: pid,
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
    #[inline(always)]
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
    fn a_pid_fuzzy_run(ctx: *mut pid_fuzzy, set: float, fdb: float) -> float;
    fn a_pid_fuzzy_pos(ctx: *mut pid_fuzzy, set: float, fdb: float) -> float;
    fn a_pid_fuzzy_inc(ctx: *mut pid_fuzzy, set: float, fdb: float) -> float;
    fn a_pid_fuzzy_zero(ctx: *mut pid_fuzzy);
}

impl pid_fuzzy {
    /// initialize for fuzzy PID controller
    #[inline(always)]
    pub fn new() -> Self {
        Self { ..Self::default() }
    }
    /// set rule base for fuzzy PID controller
    #[inline(always)]
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
    #[inline(always)]
    pub fn kpid(&mut self, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_fuzzy_kpid(self, kp, ki, kd) };
        self
    }
    /// set joint buffer for fuzzy PID controller
    #[inline(always)]
    pub fn set_joint(&mut self, ptr: &mut [u8], num: usize) -> &mut Self {
        unsafe { a_pid_fuzzy_set_joint(self, ptr.as_mut_ptr(), num) };
        self
    }
    /// get joint buffer for fuzzy PID controller
    #[inline(always)]
    pub fn joint(&mut self) -> &mut [u8] {
        unsafe {
            core::slice::from_raw_parts_mut(
                a_pid_fuzzy_joint(self),
                PID_FUZZY_JOINT!(self.joint as usize),
            )
        }
    }
    /// set fuzzy relational operator for fuzzy PID controller
    #[inline(always)]
    pub fn op(&mut self, op: uint) -> &mut Self {
        unsafe { a_pid_fuzzy_set_op(self, op) };
        self
    }
    /// calculate for fuzzy PID controller
    #[inline(always)]
    pub fn run(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_fuzzy_run(self, set, fdb) }
    }
    /// calculate for positional fuzzy PID controller
    #[inline(always)]
    pub fn pos(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_fuzzy_pos(self, set, fdb) }
    }
    /// calculate for incremental fuzzy PID controller
    #[inline(always)]
    pub fn inc(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_fuzzy_inc(self, set, fdb) }
    }
    /// zeroing for fuzzy PID controller
    #[inline(always)]
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
    a.op(crate::fuzzy::EQU).zero();
    std::println!("{} {}", a.pos(1.0, 0.0), a.pos(1.0, 0.0));
    a.op(crate::fuzzy::EQU).zero();
    std::println!("{} {}", a.inc(1.0, 0.0), a.inc(1.0, 0.0));
}

/// single neuron proportional integral derivative controller
#[repr(C)]
pub struct pid_neuro {
    /// proportional integral derivative controller
    pub pid: pid,
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
    fn a_pid_neuro_kpid(ctx: *mut pid_neuro, k: float, kp: float, ki: float, kd: float);
    fn a_pid_neuro_wpid(ctx: *mut pid_neuro, wp: float, wi: float, wd: float);
    fn a_pid_neuro_run(ctx: *mut pid_neuro, set: float, fdb: float) -> float;
    fn a_pid_neuro_inc(ctx: *mut pid_neuro, set: float, fdb: float) -> float;
    fn a_pid_neuro_zero(ctx: *mut pid_neuro);
}

impl pid_neuro {
    /// initialize for single neuron PID controller
    #[inline(always)]
    pub fn new() -> Self {
        Self { ..Self::default() }
    }
    /// set proportional integral derivative constant for single neuron PID controller
    #[inline(always)]
    pub fn kpid(&mut self, k: float, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_neuro_kpid(self, k, kp, ki, kd) };
        self
    }
    /// set proportional integral derivative weight for single neuron PID controller
    #[inline(always)]
    pub fn wpid(&mut self, wp: float, wi: float, wd: float) -> &mut Self {
        unsafe { a_pid_neuro_wpid(self, wp, wi, wd) };
        self
    }
    /// calculate for single neuron PID controller
    #[inline(always)]
    pub fn run(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_neuro_run(self, set, fdb) }
    }
    /// calculate for incremental single neuron PID controller
    #[inline(always)]
    pub fn inc(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_neuro_inc(self, set, fdb) }
    }
    /// zeroing for single neuron PID controller
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_neuro_zero(self) };
        self
    }
}

#[test]
fn pid_neuro() {
    extern crate std;
    let mut a = crate::pid_neuro::new();
    a.kpid(10.0, 1.0, 0.1, 1.0).wpid(1.0, 0.0, 0.0);
    std::println!("{}", a.inc(1.0, 0.0));
    a.zero();
}

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
        let mut a = crate::polytraj3::new(1.0, 0.0, 1.0, 0.0, 1.0);
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
        let mut a = crate::polytraj5::new(1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
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
        let mut a = crate::polytraj7::new(1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        let jer = a.jer(dt);
        std::println!("[{}, {}, {}, {}]", pos, vel, acc, jer);
    }
}

/// transfer function
#[repr(C)]
pub struct tf {
    /// input
    input: *mut float,
    /// output
    output: *mut float,
    /// numerator
    num_p: *const float,
    /// denominator
    den_p: *const float,
    /// numerator number
    num_n: uint,
    /// denominator number
    den_n: uint,
}

extern "C" {
    fn a_tf_set_num(ctx: *mut tf, num_n: uint, num_p: *const float, input: *mut float);
    fn a_tf_set_den(ctx: *mut tf, den_n: uint, den_p: *const float, output: *mut float);
    fn a_tf_init(
        ctx: *mut tf,
        num_n: uint,
        num_p: *const float,
        input: *mut float,
        den_n: uint,
        den_p: *const float,
        output: *mut float,
    );
    fn a_tf_iter(ctx: *const tf, x: float) -> float;
    fn a_tf_zero(ctx: *const tf);
}

impl tf {
    /// initialize for transfer function
    #[inline(always)]
    pub fn new(num: &[float], input: &mut [float], den: &[float], output: &mut [float]) -> Self {
        let mut ctx: Self = Self {
            input: core::ptr::null_mut(),
            output: core::ptr::null_mut(),
            num_p: core::ptr::null(),
            den_p: core::ptr::null(),
            num_n: 0,
            den_n: 0,
        };
        unsafe {
            a_tf_init(
                &mut ctx,
                num.len() as uint,
                num.as_ptr(),
                input.as_mut_ptr(),
                den.len() as uint,
                den.as_ptr(),
                output.as_mut_ptr(),
            )
        };
        ctx
    }
    /// calculate for transfer function
    #[inline(always)]
    pub fn iter(&mut self, x: float) -> float {
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
    pub fn input(&self) -> &[float] {
        unsafe { core::slice::from_raw_parts(self.input, self.num_n as usize) }
    }
    /// get numerator for transfer function
    #[inline(always)]
    pub fn num(&self) -> &[float] {
        unsafe { core::slice::from_raw_parts(self.num_p, self.num_n as usize) }
    }
    /// set numerator for transfer function
    #[inline(always)]
    pub fn set_num(&mut self, num: &[float], input: &mut [float]) -> &mut Self {
        unsafe { a_tf_set_num(self, num.len() as uint, num.as_ptr(), input.as_mut_ptr()) };
        self
    }
    /// get output for transfer function
    #[inline(always)]
    pub fn output(&self) -> &[float] {
        unsafe { core::slice::from_raw_parts(self.output, self.den_n as usize) }
    }
    /// get denominator for transfer function
    #[inline(always)]
    pub fn den(&self) -> &[float] {
        unsafe { core::slice::from_raw_parts(self.den_p, self.den_n as usize) }
    }
    /// set denominator for transfer function
    #[inline(always)]
    pub fn set_den(&mut self, den: &[float], output: &mut [float]) -> &mut Self {
        unsafe { a_tf_set_den(self, den.len() as uint, den.as_ptr(), output.as_mut_ptr()) };
        self
    }
}

#[test]
fn tf() {
    extern crate std;
    let num = [6.59492796e-05, 6.54019884e-05];
    let den = [-1.97530991, 0.97530991];
    let mut input = [0.0; 2];
    let mut output = [0.0; 2];
    let mut a = crate::tf::new(&num, &mut input, &den, &mut output);
    a.set_num(&num, &mut input).set_den(&den, &mut output);
    std::println!("{} {}", a.iter(10.0), a.iter(10.0));
    std::println!("{:?} {:?}", a.num(), a.input());
    std::println!("{:?} {:?}", a.den(), a.output());
    a.zero();
}

/// trapezoidal velocity profile trajectory
#[repr(C)]
pub struct traptraj {
    /// acceleration before constant velocity
    pub ac: float,
    /// acceleration after constant velocity
    pub de: float,
    /// position before constant velocity
    pub q1: float,
    /// position after constant velocity
    pub q2: float,
    /// time before constant velocity
    pub t1: float,
    /// time after constant velocity
    pub t2: float,
    /// initial velocity
    pub vs: float,
    /// constant velocity
    pub vc: float,
    /// final velocity
    pub ve: float,
    /// final position
    pub q: float,
    /// total time
    pub t: float,
}

extern "C" {
    fn a_traptraj_gen(
        ctx: *mut traptraj,
        qm: float,
        vm: float,
        ac: float,
        de: float,
        vs: float,
        ve: float,
    ) -> float;
    fn a_traptraj_pos(ctx: *const traptraj, dt: float) -> float;
    fn a_traptraj_vel(ctx: *const traptraj, dt: float) -> float;
    fn a_traptraj_acc(ctx: *const traptraj, dt: float) -> float;
}

impl traptraj {
    /// initialize for trapezoidal velocity profile trajectory
    #[inline(always)]
    pub fn new(qm: float, vm: float, ac: float, de: float, vs: float, ve: float) -> Self {
        let mut ctx: Self = Self {
            ac: 0.0,
            de: 0.0,
            q1: 0.0,
            q2: 0.0,
            t1: 0.0,
            t2: 0.0,
            vs: 0.0,
            vc: 0.0,
            ve: 0.0,
            q: 0.0,
            t: 0.0,
        };
        unsafe { a_traptraj_gen(&mut ctx, qm, vm, ac, de, vs, ve) };
        ctx
    }
    /// generate for trapezoidal velocity profile trajectory
    #[inline(always)]
    pub fn gen(
        &mut self,
        qm: float,
        vm: float,
        ac: float,
        de: float,
        vs: float,
        ve: float,
    ) -> float {
        unsafe { a_traptraj_gen(self, qm, vm, ac, de, vs, ve) }
    }
    /// calculate for trapezoidal velocity profile trajectory position
    #[inline(always)]
    pub fn pos(&mut self, dt: float) -> float {
        unsafe { a_traptraj_pos(self, dt) }
    }
    /// calculate for trapezoidal velocity profile trajectory velocity
    #[inline(always)]
    pub fn vel(&mut self, dt: float) -> float {
        unsafe { a_traptraj_vel(self, dt) }
    }
    /// calculate for trapezoidal velocity profile trajectory acceleration
    #[inline(always)]
    pub fn acc(&mut self, dt: float) -> float {
        unsafe { a_traptraj_acc(self, dt) }
    }
}

#[test]
fn traptraj() {
    extern crate std;
    let dt = 0.5;
    {
        let mut a = crate::traptraj::new(10.0, 2.0, 2.0, -2.0, 0.0, 0.0);
        let pos = a.pos(dt);
        let vel = a.vel(dt);
        let acc = a.acc(dt);
        std::println!("[{}, {}, {}]", pos, vel, acc);
    }
}

/// version
///
/// ## Examples
///
/// ```
/// println!(
///     "version {}.{}.{}+{}",
///     liba::version::major(),
///     liba::version::minor(),
///     liba::version::patch(),
///     liba::version::tweak()
/// );
/// ```
#[repr(C)]
pub struct version {
    /// major number
    pub major: uint,
    /// minor number
    pub minor: uint,
    /// third number
    pub third: uint,
    /// extra number
    pub extra: uint,
}

extern "C" {
    static a_version_major: uint;
    static a_version_minor: uint;
    static a_version_patch: uint;
    static a_version_tweak: u32;
    fn a_version_check(major: uint, minor: uint, patch: uint) -> int;
    fn a_version_cmp(lhs: *const version, rhs: *const version) -> int;
    fn a_version_lt(lhs: *const version, rhs: *const version) -> bool;
    fn a_version_gt(lhs: *const version, rhs: *const version) -> bool;
    fn a_version_le(lhs: *const version, rhs: *const version) -> bool;
    fn a_version_ge(lhs: *const version, rhs: *const version) -> bool;
    fn a_version_eq(lhs: *const version, rhs: *const version) -> bool;
}

impl version {
    /// initialize for version
    #[inline(always)]
    pub fn new(major: uint, minor: uint, third: uint) -> Self {
        Self {
            major,
            minor,
            third,
            extra: 0,
        }
    }
    /// algorithm library version check
    #[inline(always)]
    pub fn check(major: uint, minor: uint, patch: uint) -> int {
        unsafe { a_version_check(major, minor, patch) }
    }
    /// algorithm library version major
    #[inline(always)]
    pub fn major() -> uint {
        unsafe { a_version_major }
    }
    /// algorithm library version minor
    #[inline(always)]
    pub fn minor() -> uint {
        unsafe { a_version_minor }
    }
    /// algorithm library version patch
    #[inline(always)]
    pub fn patch() -> uint {
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
    fn partial_cmp(&self, other: &version) -> Option<core::cmp::Ordering> {
        let ok: int = unsafe { a_version_cmp(self, other) };
        if ok > 0 {
            return Some(core::cmp::Ordering::Greater);
        }
        if ok < 0 {
            return Some(core::cmp::Ordering::Less);
        }
        Some(core::cmp::Ordering::Equal)
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

#[test]
fn version() {
    extern crate std;
    impl core::fmt::Debug for version {
        fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
            f.debug_struct("version")
                .field("major", &self.major)
                .field("minor", &self.minor)
                .field("third", &self.third)
                .field("extra", &self.extra)
                .finish()
        }
    }
    std::println!("{}", crate::version::check(0, 0, 0));
    std::println!("major {}", crate::version::major());
    std::println!("minor {}", crate::version::minor());
    std::println!("patch {}", crate::version::patch());
    std::println!("tweak {}", crate::version::tweak());
    let v000 = version::new(0, 0, 0);
    let v001 = version::new(0, 0, 1);
    std::println!("{:?}", v001);
    assert!(v001 > v000);
    assert!(v000 < v001);
    assert!(v000 >= v000);
    assert!(v000 <= v000);
    assert!(v000 == v000);
    assert!(v000 != v001);
}
