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

use std::os::raw::c_char;
/// Equivalent to C’s unsigned int type.
pub type uint = std::os::raw::c_uint;
/// floating-point number stored using `f64`
#[cfg(not(feature = "float"))]
pub type float = f64;
/// floating-point number stored using `f32`
#[cfg(feature = "float")]
pub type float = f32;
/// floating-point number union
#[repr(C)]
pub union Float {
    /// as a floating-point number
    pub f: float,
    /// as a floating-point array
    pub p: *mut float,
}

pub mod mf;
pub mod tf;
pub use crate::tf::TF;
pub mod crc;
pub use crate::crc::crc16;
pub use crate::crc::crc32;
pub use crate::crc::crc64;
pub use crate::crc::crc8;
pub mod pid;
pub use crate::pid::PID;
pub mod pid_fuzzy;
pub use crate::pid_fuzzy::PID_fuzzy;
pub mod polytrack;
pub use crate::polytrack::polytrack3;
pub use crate::polytrack::polytrack5;
pub use crate::polytrack::polytrack7;

extern "C" {
    fn a_version() -> *const c_char;
    fn a_version_major() -> uint;
    fn a_version_minor() -> uint;
    fn a_version_patch() -> uint;
}

/**
algorithm library version

## Examples

```
println!("version {}", liba::version());
```
*/
pub fn version() -> &'static str {
    unsafe { std::ffi::CStr::from_ptr(a_version()).to_str().unwrap() }
}

/// algorithm library version major
pub fn version_major() -> uint {
    unsafe { a_version_major() }
}

/// algorithm library version minor
pub fn version_minor() -> uint {
    unsafe { a_version_minor() }
}

/// algorithm library version patch
pub fn version_patch() -> uint {
    unsafe { a_version_patch() }
}

extern "C" {
    fn a_f32_rsqrt(x: f32) -> f32;
    fn a_f64_rsqrt(x: f64) -> f64;
}

/// fast inverse square-root, $ \frac{1}{\sqrt{x}} $
pub fn f32_rsqrt(x: f32) -> f32 {
    unsafe { a_f32_rsqrt(x) }
}

/// fast inverse square-root, $ \frac{1}{\sqrt{x}} $
pub fn f64_rsqrt(x: f64) -> f64 {
    unsafe { a_f64_rsqrt(x) }
}

#[cfg(test)]
mod test {
    #[test]
    fn version() {
        println!("version {}", crate::version());
        println!("major {}", crate::version_major());
        println!("minor {}", crate::version_minor());
        println!("patch {}", crate::version_patch());
    }
    #[test]
    fn rsqrt() {
        println!("1/sqrt({})={}", 4, crate::f32_rsqrt(4.0));
        println!("1/sqrt({})={}", 4, crate::f64_rsqrt(4.0));
    }
}
