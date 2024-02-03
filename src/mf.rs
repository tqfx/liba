//! membership function

use crate::float;
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
    fn gauss() {
        for i in -4..=4 {
            let x = i as crate::float;
            std::println!("{:+} {}", x, crate::mf::gauss(x, 1.0, 0.0));
        }
    }
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
