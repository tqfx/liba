//! single neuron proportional integral derivative controller

use crate::float;
use crate::uint;
use crate::Float;
use crate::PID;

/// single neuron proportional integral derivative controller
#[repr(C)]
pub struct PID_neuron {
    /// proportional integral derivative controller
    pub pid: PID,
    /// error change
    pub ec: Float,
    /// proportional weight
    pub wp: Float,
    /// integral weight
    pub wi: Float,
    /// derivative weight
    pub wd: Float,
    /// proportional coefficient
    pub k: float,
}

extern "C" {
    fn a_pid_neuron_chan(
        ctx: *mut PID_neuron,
        num: uint,
        out: *mut float,
        fdb: *mut float,
        tmp: *mut float,
        err: *mut float,
        ec: *mut float,
        wp: *mut float,
        wi: *mut float,
        wd: *mut float,
    );
    fn a_pid_neuron_kpid(ctx: *mut PID_neuron, k: float, kp: float, ki: float, kd: float);
    fn a_pid_neuron_wpid(ctx: *mut PID_neuron, wp: float, wi: float, wd: float);
    fn a_pid_neuron_outf(ctx: *mut PID_neuron, set: float, fdb: float) -> float;
    fn a_pid_neuron_outp(
        ctx: *const PID_neuron,
        set: *const float,
        fdb: *const float,
    ) -> *const float;
    fn a_pid_neuron_zero(ctx: *mut PID_neuron);
}

impl PID_neuron {
    /// initialize function for single neuron PID controller
    pub fn new(min: float, max: float, sum: float) -> Self {
        PID_neuron {
            pid: PID::new(min, max, sum),
            ec: Float { f: 0.0 },
            wp: Float { f: 0.0 },
            wi: Float { f: 0.0 },
            wd: Float { f: 0.0 },
            k: 0.0,
        }
    }

    /// set buffer for multichannel single neuron PID controller
    pub fn chan(
        &mut self,
        out: &mut [float],
        fdb: &mut [float],
        tmp: &mut [float],
        err: &mut [float],
        ec: &mut [float],
        wp: &mut [float],
        wi: &mut [float],
        wd: &mut [float],
    ) -> &mut Self {
        unsafe {
            a_pid_neuron_chan(
                self,
                out.len() as uint,
                out.as_mut_ptr(),
                fdb.as_mut_ptr(),
                tmp.as_mut_ptr(),
                err.as_mut_ptr(),
                ec.as_mut_ptr(),
                wp.as_mut_ptr(),
                wi.as_mut_ptr(),
                wd.as_mut_ptr(),
            )
        };
        self
    }

    /// set proportional integral derivative constant for single neuron PID controller
    pub fn kpid(&mut self, k: float, kp: float, ki: float, kd: float) -> &mut Self {
        unsafe { a_pid_neuron_kpid(self, k, kp, ki, kd) };
        self
    }

    /// set proportional integral derivative weight for single neuron PID controller
    pub fn wpid(&mut self, wp: float, wi: float, wd: float) -> &mut Self {
        unsafe { a_pid_neuron_wpid(self, wp, wi, wd) };
        self
    }

    /// calculate function for single neuron PID controller
    pub fn outf(&mut self, set: float, fdb: float) -> float {
        unsafe { a_pid_neuron_outf(self, set, fdb) }
    }
    /// calculate function for multichannel single neuron PID controller
    pub fn outp(&self, set: &[float], fdb: &[float]) -> &[float] {
        unsafe {
            std::slice::from_raw_parts(
                a_pid_neuron_outp(self, set.as_ptr(), fdb.as_ptr()),
                self.pid.chan as usize,
            )
        }
    }

    /// zero clear function for single neuron PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_neuron_zero(self) };
        self
    }
}

#[test]
#[allow(non_snake_case)]
fn pid_neuron() {
    let mut a = PID_neuron::new(-10.0, 10.0, 0.0);
    a.kpid(10.0, 1.0, 0.1, 1.0).wpid(1.0, 0.0, 0.0);
    assert!(a.pid.mode == crate::pid::INC);
    println!("{}", a.outf(1.0, 0.0));
    a.zero();
    {
        let mut out: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut fdb: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut tmp: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut err: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut ec: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut wp: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut wi: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        let mut wd: [float; 4] = [0.0, 0.0, 0.0, 0.0];
        a.chan(
            &mut out, &mut fdb, &mut tmp, &mut err, &mut ec, &mut wp, &mut wi, &mut wd,
        )
        .wpid(1.0, 0.0, 0.0);
        a.outp(&[0.1, 0.2, 0.3, 0.4], &[0.0, 0.0, 0.0, 0.0]);
        println!("{:?}", out);
    }
}
