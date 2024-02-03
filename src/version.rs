//! version
//!
//! ## Examples
//!
//! ```
//! println!(
//!     "version {}.{}.{}+{}",
//!     liba::version::major(),
//!     liba::version::minor(),
//!     liba::version::patch(),
//!     liba::version::tweak()
//! );
//! ```

use crate::int;
use crate::uint;

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

/// version
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
    use crate::version::version;
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
