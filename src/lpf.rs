//! Low Pass Filter

use crate::float;
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
    let mut a = crate::lpf::lpf::new(10.0, 0.01);
    a.gen(10.0, 0.01).zero().iter(1.0);
}
