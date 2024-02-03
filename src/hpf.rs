//! High Pass Filter

use crate::float;
#[cfg(feature = "float")]
use core::f32::consts::PI;
#[cfg(not(feature = "float"))]
use core::f64::consts::PI;

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
            alpha: 1.0 / (2.0 * PI * fc * ts + 1.0),
            output: 0.0,
            input: 0.0,
        }
    }
    /// generate for High Pass Filter
    #[inline(always)]
    pub fn gen(&mut self, fc: float, ts: float) -> &mut Self {
        self.alpha = 1.0 / (2.0 * PI * fc * ts + 1.0);
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
    let mut a = crate::hpf::hpf::new(10.0, 0.01);
    a.gen(10.0, 0.01).zero().iter(1.0);
}
