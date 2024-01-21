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

pub mod crc;
pub mod hpf;
pub mod lpf;
pub mod mf;
pub mod pid;
pub mod polytraj;
pub mod tf;
pub mod version;

extern "C" {
    fn a_u32_sqrt(x: u32) -> u16;
    fn a_u64_sqrt(x: u64) -> u32;
}
/// square root of an unsigned integer
pub fn u32_sqrt(x: u32) -> u16 {
    unsafe { a_u32_sqrt(x) }
}
/// square root of an unsigned integer
pub fn u64_sqrt(x: u64) -> u32 {
    unsafe { a_u64_sqrt(x) }
}

extern "C" {
    fn a_f32_rsqrt(x: f32) -> f32;
    fn a_f64_rsqrt(x: f64) -> f64;
}
/// reciprocal of square-root, $ \frac{1}{\sqrt{x}} $
pub fn f32_rsqrt(x: f32) -> f32 {
    unsafe { a_f32_rsqrt(x) }
}
/// reciprocal of square-root, $ \frac{1}{\sqrt{x}} $
pub fn f64_rsqrt(x: f64) -> f64 {
    unsafe { a_f64_rsqrt(x) }
}

extern "C" {
    fn a_hash_bkdr_(pdata: *const u8, nbyte: usize, value: u32) -> u32;
    fn a_hash_sdbm_(pdata: *const u8, nbyte: usize, value: u32) -> u32;
}
/// a hash function whose prime number is 131
pub fn hash_bkdr(block: &[u8], value: u32) -> u32 {
    unsafe { a_hash_bkdr_(block.as_ptr(), block.len(), value) }
}
/// a hash function whose prime number is 65599
pub fn hash_sdbm(block: &[u8], value: u32) -> u32 {
    unsafe { a_hash_sdbm_(block.as_ptr(), block.len(), value) }
}

#[cfg(test)]
mod test {
    extern crate std;
    #[test]
    fn isqrt() {
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
