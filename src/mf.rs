//! membership function

use crate::real;

/// none
pub const NUL: real = 0.0;
/// gaussian membership function
pub const GAUSS: real = 1.0;
/// generalized bell-shaped membership function
pub const GBELL: real = 2.0;
/// sigmoidal membership function
pub const SIG: real = 3.0;
/// trapezoidal membership function
pub const TRAP: real = 4.0;
/// triangular membership function
pub const TRI: real = 5.0;
/// z-shaped membership function
pub const Z: real = 6.0;

extern "C" {
    fn a_mf_gauss(x: real, sigma: real, c: real) -> real;
    fn a_mf_gbell(x: real, a: real, b: real, c: real) -> real;
    fn a_mf_sig(x: real, a: real, c: real) -> real;
    fn a_mf_trap(x: real, a: real, b: real, c: real, d: real) -> real;
    fn a_mf_tri(x: real, a: real, b: real, c: real) -> real;
    fn a_mf_z(x: real, a: real, b: real) -> real;
}

/// gaussian membership function
pub fn gauss(x: real, sigma: real, c: real) -> real {
    unsafe { a_mf_gauss(x, sigma, c) }
}

/// generalized bell-shaped membership function
pub fn gbell(x: real, a: real, b: real, c: real) -> real {
    unsafe { a_mf_gbell(x, a, b, c) }
}

/// sigmoidal membership function
pub fn sig(x: real, a: real, c: real) -> real {
    unsafe { a_mf_sig(x, a, c) }
}

/// trapezoidal membership function
pub fn trap(x: real, a: real, b: real, c: real, d: real) -> real {
    unsafe { a_mf_trap(x, a, b, c, d) }
}

/// triangular membership function
pub fn tri(x: real, a: real, b: real, c: real) -> real {
    unsafe { a_mf_tri(x, a, b, c) }
}

/// z-shaped membership function
pub fn z(x: real, a: real, b: real) -> real {
    unsafe { a_mf_z(x, a, b) }
}

#[cfg(test)]
mod test {
    #[test]
    fn gauss() {
        println!("{}", crate::mf::gauss(0.0, 1.0, 0.0));
    }
    #[test]
    fn gbell() {
        println!("{}", crate::mf::gbell(0.0, 2.0, 1.0, 0.0));
    }
    #[test]
    fn sig() {
        println!("{}", crate::mf::sig(0.0, 2.0, 0.0));
    }
    #[test]
    fn trap() {
        println!("{}", crate::mf::trap(0.0, -2.0, -1.0, 1.0, 2.0));
    }
    #[test]
    fn tri() {
        println!("{}", crate::mf::tri(0.0, -1.0, 0.0, 1.0));
    }
    #[test]
    fn z() {
        println!("{}", crate::mf::z(0.0, -1.0, 1.0));
    }
}
