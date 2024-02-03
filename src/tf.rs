//! transfer function

use crate::float;
use crate::uint;

/// transfer function
#[repr(C)]
pub struct tf {
    /// input
    input: *mut float,
    /// output
    output: *mut float,
    /// numerator
    num_p: *const float,
    /// denominator
    den_p: *const float,
    /// numerator number
    num_n: uint,
    /// denominator number
    den_n: uint,
}

extern "C" {
    fn a_tf_set_num(ctx: *mut tf, num_n: uint, num_p: *const float, input: *mut float);
    fn a_tf_set_den(ctx: *mut tf, den_n: uint, den_p: *const float, output: *mut float);
    fn a_tf_init(
        ctx: *mut tf,
        num_n: uint,
        num_p: *const float,
        input: *mut float,
        den_n: uint,
        den_p: *const float,
        output: *mut float,
    );
    fn a_tf_iter(ctx: *const tf, x: float) -> float;
    fn a_tf_zero(ctx: *const tf);
}

impl tf {
    /// initialize for transfer function
    #[inline(always)]
    pub fn new(num: &[float], input: &mut [float], den: &[float], output: &mut [float]) -> Self {
        let mut ctx: Self = Self {
            input: core::ptr::null_mut(),
            output: core::ptr::null_mut(),
            num_p: core::ptr::null(),
            den_p: core::ptr::null(),
            num_n: 0,
            den_n: 0,
        };
        unsafe {
            a_tf_init(
                &mut ctx,
                num.len() as uint,
                num.as_ptr(),
                input.as_mut_ptr(),
                den.len() as uint,
                den.as_ptr(),
                output.as_mut_ptr(),
            )
        };
        ctx
    }

    /// calculate for transfer function
    #[inline(always)]
    pub fn iter(&mut self, x: float) -> float {
        unsafe { a_tf_iter(self, x) }
    }

    /// zeroing for transfer function
    #[inline(always)]
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_tf_zero(self) };
        self
    }

    /// get input for transfer function
    #[inline(always)]
    pub fn input(&self) -> &[float] {
        unsafe { core::slice::from_raw_parts(self.input, self.num_n as usize) }
    }

    /// get numerator for transfer function
    #[inline(always)]
    pub fn num(&self) -> &[float] {
        unsafe { core::slice::from_raw_parts(self.num_p, self.num_n as usize) }
    }

    /// set numerator for transfer function
    #[inline(always)]
    pub fn set_num(&mut self, num: &[float], input: &mut [float]) -> &mut Self {
        unsafe { a_tf_set_num(self, num.len() as uint, num.as_ptr(), input.as_mut_ptr()) };
        self
    }

    /// get output for transfer function
    #[inline(always)]
    pub fn output(&self) -> &[float] {
        unsafe { core::slice::from_raw_parts(self.output, self.den_n as usize) }
    }

    /// get denominator for transfer function
    #[inline(always)]
    pub fn den(&self) -> &[float] {
        unsafe { core::slice::from_raw_parts(self.den_p, self.den_n as usize) }
    }

    /// set denominator for transfer function
    #[inline(always)]
    pub fn set_den(&mut self, den: &[float], output: &mut [float]) -> &mut Self {
        unsafe { a_tf_set_den(self, den.len() as uint, den.as_ptr(), output.as_mut_ptr()) };
        self
    }
}

#[test]
fn tf() {
    extern crate std;
    let num = [6.59492796e-05, 6.54019884e-05];
    let den = [-1.97530991, 0.97530991];
    let mut input = [0.0; 2];
    let mut output = [0.0; 2];
    let mut a = crate::tf::tf::new(&num, &mut input, &den, &mut output);
    a.set_num(&num, &mut input).set_den(&den, &mut output);
    std::println!("{} {}", a.iter(10.0), a.iter(10.0));
    std::println!("{:?} {:?}", a.num(), a.input());
    std::println!("{:?} {:?}", a.den(), a.output());
    a.zero();
}
