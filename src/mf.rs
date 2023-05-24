//! membership function

use crate::float;

/// none
pub const NUL: float = 0.0;
/// gaussian membership function
pub const GAUSS: float = 1.0;
/// generalized bell-shaped membership function
pub const GBELL: float = 2.0;
/// sigmoidal membership function
pub const SIG: float = 3.0;
/// trapezoidal membership function
pub const TRAP: float = 4.0;
/// triangular membership function
pub const TRI: float = 5.0;
/// z-shaped membership function
pub const Z: float = 6.0;

extern "C" {
    fn a_mf_gauss(x: float, sigma: float, c: float) -> float;
    fn a_mf_gbell(x: float, a: float, b: float, c: float) -> float;
    fn a_mf_sig(x: float, a: float, c: float) -> float;
    fn a_mf_trap(x: float, a: float, b: float, c: float, d: float) -> float;
    fn a_mf_tri(x: float, a: float, b: float, c: float) -> float;
    fn a_mf_z(x: float, a: float, b: float) -> float;
}

/// gaussian membership function
pub fn gauss(x: float, sigma: float, c: float) -> float {
    unsafe { a_mf_gauss(x, sigma, c) }
}

/// generalized bell-shaped membership function
pub fn gbell(x: float, a: float, b: float, c: float) -> float {
    unsafe { a_mf_gbell(x, a, b, c) }
}

/// sigmoidal membership function
pub fn sig(x: float, a: float, c: float) -> float {
    unsafe { a_mf_sig(x, a, c) }
}

/// trapezoidal membership function
pub fn trap(x: float, a: float, b: float, c: float, d: float) -> float {
    unsafe { a_mf_trap(x, a, b, c, d) }
}

/// triangular membership function
pub fn tri(x: float, a: float, b: float, c: float) -> float {
    unsafe { a_mf_tri(x, a, b, c) }
}

/// z-shaped membership function
pub fn z(x: float, a: float, b: float) -> float {
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
