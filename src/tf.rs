//! transfer function

use crate::Real;
use crate::Uint;

/// transfer function
#[repr(C)]
pub struct TF {
    /// input
    u: *mut Real,
    /// output
    v: *mut Real,
    /// numerator
    num: *const Real,
    /// denominator
    den: *const Real,
    /// numerator number
    m: Uint,
    /// denominator number
    n: Uint,
}

extern "C" {
    fn a_tf_set_num(ctx: *mut TF, m: Uint, num: *const Real, u: *mut Real);
    fn a_tf_set_den(ctx: *mut TF, n: Uint, den: *const Real, v: *mut Real);
    fn a_tf_init(
        ctx: *mut TF,
        m: Uint,
        num: *const Real,
        u: *mut Real,
        n: Uint,
        den: *const Real,
        v: *mut Real,
    ) -> *mut TF;
    fn a_tf_iter(ctx: *mut TF, x: Real) -> Real;
    fn a_tf_zero(ctx: *mut TF) -> *mut TF;
}

impl TF {
    /// initialize function for transfer function
    pub fn new(num: &[Real], u: &mut [Real], den: &[Real], v: &mut [Real]) -> Self {
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
                num.len() as Uint,
                num.as_ptr(),
                u.as_mut_ptr(),
                den.len() as Uint,
                den.as_ptr(),
                v.as_mut_ptr(),
            )
        };
        ctx
    }

    /// calculate function for transfer function
    pub fn iter(&mut self, x: Real) -> Real {
        unsafe { a_tf_iter(self, x) }
    }

    /// zero function for transfer function
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_tf_zero(self).as_mut().unwrap_unchecked() }
    }

    /// get input for transfer function
    pub fn u(&self) -> &mut [Real] {
        unsafe { std::slice::from_raw_parts_mut(self.u, self.m as usize) }
    }

    /// get numerator for transfer function
    pub fn num(&self) -> &[Real] {
        unsafe { std::slice::from_raw_parts(self.num, self.m as usize) }
    }

    /// set numerator for transfer function
    pub fn set_num(&mut self, num: &[Real], u: &mut [Real]) -> &mut Self {
        unsafe { a_tf_set_num(self, num.len() as Uint, num.as_ptr(), u.as_mut_ptr()) };
        self
    }

    /// get output for transfer function
    pub fn v(&self) -> &mut [Real] {
        unsafe { std::slice::from_raw_parts_mut(self.v, self.n as usize) }
    }

    /// get denominator for transfer function
    pub fn den(&self) -> &[Real] {
        unsafe { std::slice::from_raw_parts(self.den, self.n as usize) }
    }

    /// set denominator for transfer function
    pub fn set_den(&mut self, den: &[Real], v: &mut [Real]) -> &mut Self {
        unsafe { a_tf_set_den(self, den.len() as Uint, den.as_ptr(), v.as_mut_ptr()) };
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
