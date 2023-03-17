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
#[allow(missing_docs)]
pub type Uint = libc::c_uint;
#[allow(missing_docs)]
pub type Real = f64;

pub mod mf;
pub mod tf;
pub use crate::tf::TF;
pub mod pid;
pub use crate::pid::PID;
pub mod fpid;
pub use crate::fpid::FPID;
pub mod polytrack;
pub use crate::polytrack::PolyTrack3;
pub use crate::polytrack::PolyTrack5;
pub use crate::polytrack::PolyTrack7;

extern "C" {
    fn a_version() -> *const libc::c_char;
    fn a_version_major() -> Uint;
    fn a_version_minor() -> Uint;
    fn a_version_patch() -> Uint;
}

/**
algorithm library version

## Examples

```
println!("version {}", liba::version());
```
*/
pub fn version() -> String {
    let c_str: &std::ffi::CStr = unsafe { std::ffi::CStr::from_ptr(a_version()) };
    let str_slice: &str = c_str.to_str().unwrap();
    let str_buf: String = str_slice.to_owned();
    str_buf
}

/// algorithm library version major
pub fn version_major() -> u32 {
    unsafe { a_version_major() as u32 }
}

/// algorithm library version minor
pub fn version_minor() -> u32 {
    unsafe { a_version_minor() as u32 }
}

/// algorithm library version patch
pub fn version_patch() -> u32 {
    unsafe { a_version_patch() as u32 }
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
