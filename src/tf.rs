//! transfer function

use crate::float;
use crate::uint;

/// transfer function
#[repr(C)]
pub struct TF {
    /// input
    u: *mut float,
    /// output
    v: *mut float,
    /// numerator
    num: *const float,
    /// denominator
    den: *const float,
    /// numerator number
    m: uint,
    /// denominator number
    n: uint,
}

extern "C" {
    fn a_tf_set_num(ctx: *mut TF, m: uint, num: *const float, u: *mut float);
    fn a_tf_set_den(ctx: *mut TF, n: uint, den: *const float, v: *mut float);
    fn a_tf_init(
        ctx: *mut TF,
        m: uint,
        num: *const float,
        u: *mut float,
        n: uint,
        den: *const float,
        v: *mut float,
    ) -> *mut TF;
    fn a_tf_iter(ctx: *mut TF, x: float) -> float;
    fn a_tf_zero(ctx: *mut TF) -> *mut TF;
}

impl TF {
    /// initialize function for transfer function
    pub fn new(num: &[float], u: &mut [float], den: &[float], v: &mut [float]) -> Self {
        let mut ctx: Self = Self {
            u: std::ptr::null_mut(),
            v: std::ptr::null_mut(),
            num: std::ptr::null(),
            den: std::ptr::null(),
            m: 0,
            n: 0,
        };
        unsafe {
            a_tf_init(
                &mut ctx,
                num.len() as uint,
                num.as_ptr(),
                u.as_mut_ptr(),
                den.len() as uint,
                den.as_ptr(),
                v.as_mut_ptr(),
            )
        };
        ctx
    }

    /// calculate function for transfer function
    pub fn iter(&mut self, x: float) -> float {
        unsafe { a_tf_iter(self, x) }
    }

    /// zero function for transfer function
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_tf_zero(self).as_mut().unwrap_unchecked() }
    }

    /// get input for transfer function
    pub fn u(&self) -> &[float] {
        unsafe { std::slice::from_raw_parts(self.u, self.m as usize) }
    }

    /// get numerator for transfer function
    pub fn num(&self) -> &[float] {
        unsafe { std::slice::from_raw_parts(self.num, self.m as usize) }
    }

    /// set numerator for transfer function
    pub fn set_num(&mut self, num: &[float], u: &mut [float]) -> &mut Self {
        unsafe { a_tf_set_num(self, num.len() as uint, num.as_ptr(), u.as_mut_ptr()) };
        self
    }

    /// get output for transfer function
    pub fn v(&self) -> &[float] {
        unsafe { std::slice::from_raw_parts(self.v, self.n as usize) }
    }

    /// get denominator for transfer function
    pub fn den(&self) -> &[float] {
        unsafe { std::slice::from_raw_parts(self.den, self.n as usize) }
    }

    /// set denominator for transfer function
    pub fn set_den(&mut self, den: &[float], v: &mut [float]) -> &mut Self {
        unsafe { a_tf_set_den(self, den.len() as uint, den.as_ptr(), v.as_mut_ptr()) };
        self
    }
}

#[test]
fn tf() {
    let num = [6.59492796e-05, 6.54019884e-05];
    let den = [-1.97530991, 0.97530991];
    let mut u = [0.0; 2];
    let mut v = [0.0; 2];
    let mut a = crate::TF::new(&num, &mut u, &den, &mut v);
    println!("{} {}", a.iter(10.0), a.iter(10.0));
    println!("{:?} {:?}", a.num(), a.u());
    println!("{:?} {:?}", a.den(), a.v());
    a.zero();
}
