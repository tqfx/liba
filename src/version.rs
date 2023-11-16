//! version

use crate::int;
use crate::uint;

/// version
#[repr(C)]
pub struct version {
    /// major number
    pub major: uint,
    /// minor number
    pub minor: uint,
    /// patch number
    pub patch: uint,
}

extern "C" {
    fn a_version_cmp(lhs: *const version, rhs: *const version) -> int;
    fn a_version_lt(lhs: *const version, rhs: *const version) -> bool;
    fn a_version_gt(lhs: *const version, rhs: *const version) -> bool;
    fn a_version_le(lhs: *const version, rhs: *const version) -> bool;
    fn a_version_ge(lhs: *const version, rhs: *const version) -> bool;
    fn a_version_eq(lhs: *const version, rhs: *const version) -> bool;
}

impl PartialOrd for version {
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
    fn lt(&self, other: &version) -> bool {
        unsafe { a_version_lt(self, other) }
    }
    fn gt(&self, other: &version) -> bool {
        unsafe { a_version_gt(self, other) }
    }
    fn le(&self, other: &version) -> bool {
        unsafe { a_version_le(self, other) }
    }
    fn ge(&self, other: &version) -> bool {
        unsafe { a_version_ge(self, other) }
    }
}

impl PartialEq for version {
    fn eq(&self, other: &version) -> bool {
        unsafe { a_version_eq(self, other) }
    }
}

impl version {
    /// initialize function for version
    pub fn new(major: uint, minor: uint, patch: uint) -> Self {
        Self {
            major,
            minor,
            patch,
        }
    }
}

#[test]
fn version() {
    extern crate std;
    use crate::version::version;
    impl std::fmt::Debug for version {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            f.debug_struct("version")
                .field("major", &self.major)
                .field("minor", &self.minor)
                .field("patch", &self.patch)
                .finish()
        }
    }
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
