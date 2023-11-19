declare namespace liba {
    /**
     * fast inverse square-root
     * @param x independent variable
     */
    function f32_rsqrt(x: number): number;
    /**
     * fast inverse square-root
     * @param x independent variable
     */
    function f64_rsqrt(x: number): number;

    /** none */
    const MF_NUL: number;
    /** gaussian membership function */
    const MF_GAUSS: number;
    /** gaussian combination membership function */
    const MF_GAUSS2: number;
    /** generalized bell-shaped membership function */
    const MF_GBELL: number;
    /** sigmoidal membership function */
    const MF_SIG: number;
    /** difference between two sigmoidal membership functions */
    const MF_DSIG: number;
    /** product of two sigmoidal membership functions */
    const MF_PSIG: number;
    /** trapezoidal membership function */
    const MF_TRAP: number;
    /** triangular membership function */
    const MF_TRI: number;
    /** linear s-shaped saturation membership function */
    const MF_LINS: number;
    /** linear z-shaped saturation membership function */
    const MF_LINZ: number;
    /** s-shaped membership function */
    const MF_S: number;
    /** z-shaped membership function */
    const MF_Z: number;
    /** pi-shaped membership function */
    const MF_PI: number;

    /**
     * gaussian membership function
     * @param x input value for which to compute membership value.
     * @param sigma is the standard deviation.
     * @param c is the mean.
     * @return membership value.
     */
    function mf_gauss(x: number, sigma: number, c: number): number;
    /**
     * gaussian combination membership function
     * @param x input value for which to compute membership value.
     * @param sigma1 is the standard deviation of the left gaussian function.
     * @param c1 is the mean of the left gaussian function.
     * @param sigma2 is the standard deviation of the right gaussian function.
     * @param c2 is the mean of the right gaussian function.
     * @return membership value.
     */
    function mf_gauss2(x: number, sigma1: number, c1: number, sigma2: number, c2: number): number;
    /**
     * generalized bell-shaped membership function
     * @param x input value for which to compute membership value.
     * @param a defines the width of the membership function, where a larger value creates a wider membership function.
     * @param b defines the shape of the curve on either side of the central plateau, where a larger value creates a more steep transition.
     * @param c defines the center of the membership function.
     * @return membership value.
     */
    function mf_gbell(x: number, a: number, b: number, c: number): number;
    /**
     * sigmoidal membership function
     * @param x input value for which to compute membership value.
     * @param a defines the width of the transition area.
     * @param c defines the center of the transition area.
     * @return membership value.
     */
    function mf_sig(x: number, a: number, c: number): number;
    /**
     * difference between two sigmoidal membership functions
     * @param x input value for which to compute membership value.
     * @param a1 defines the width of the first transition area.
     * @param c1 defines the center of the first transition area.
     * @param a2 defines the width of the second transition area.
     * @param c2 defines the center of the second transition area.
     * @return membership value.
     */
    function mf_dsig(x: number, a1: number, c1: number, a2: number, c2: number): number;
    /**
     * product of two sigmoidal membership functions
     * @param x input value for which to compute membership value.
     * @param a1 defines the width of the first transition area.
     * @param c1 defines the center of the first transition area.
     * @param a2 defines the width of the second transition area.
     * @param c2 defines the center of the second transition area.
     * @return membership value.
     */
    function mf_psig(x: number, a1: number, c1: number, a2: number, c2: number): number;
    /**
     * trapezoidal membership function
     * @param x input value for which to compute membership value.
     * @param a defines its left foot.
     * @param b defines its left shoulder.
     * @param c defines its right shoulder.
     * @param d defines its right foot.
     * @return membership value.
     */
    function mf_trap(x: number, a: number, b: number, c: number, d: number): number;
    /**
     * triangular membership function
     * @param x input value for which to compute membership value.
     * @param a defines its left foot.
     * @param b defines its peak.
     * @param c defines its right foot.
     * @return membership value.
     */
    function mf_tri(x: number, a: number, b: number, c: number): number;
    /**
     * linear s-shaped saturation membership function
     * @param x input value for which to compute membership value.
     * @param a defines its foot.
     * @param b defines its shoulder.
     * @return membership value.
     */
    function mf_lins(x: number, a: number, b: number): number;
    /**
     * linear z-shaped saturation membership function
     * @param x input value for which to compute membership value.
     * @param a defines its shoulder.
     * @param b defines its foot.
     * @return membership value.
     */
    function mf_linz(x: number, a: number, b: number): number;
    /**
     * s-shaped membership function
     * @param x input value for which to compute membership value.
     * @param a defines its foot.
     * @param b defines its shoulder.
     * @return membership value.
     */
    function mf_s(x: number, a: number, b: number): number;
    /**
     * z-shaped membership function
     * @param x input value for which to compute membership value.
     * @param a defines its shoulder.
     * @param b defines its foot.
     * @return membership value.
     */
    function mf_z(x: number, a: number, b: number): number;
    /**
     * pi-shaped membership function
     * @param x input value for which to compute membership value.
     * @param a defines its left foot.
     * @param b defines its left shoulder.
     * @param c defines its right shoulder.
     * @param d defines its right foot.
     * @return membership value.
     */
    function mf_pi(x: number, a: number, b: number, c: number, d: number): number;

    /** turn off PID controller */
    const PID_OFF: number;
    /** positional PID controller */
    const PID_POS: number;
    /** incremental PID controller */
    const PID_INC: number;

    interface pid {
        /** PID_OFF PID_POS PID_INC */
        mode: number;
        /** proportional constant */
        kp: number;
        /** integral constant */
        ki: number;
        /** derivative constant */
        kd: number;
        /** maximum integral output */
        summax: number;
        /** maximum final output */
        outmax: number;
        /** minimum final output */
        outmin: number;
        /** controller output */
        readonly out: number;
        /** cache feedback */
        readonly fdb: number;
        /** cache error */
        readonly err: number;
        /**
         * set proportional integral derivative constant for PID controller
         * @param kp proportional constant
         * @param ki integral constant
         * @param kd derivative constant
         */
        kpid(kp: number, ki: number, kd: number): pid;
        /**
         * calculate function for PID controller
         * @param set setpoint
         * @param fdb feedback
         */
        iter(set: number, fdb: number): number;
        /** zero clear function for PID controller */
        zero(): pid;
        delete(): void;
    }
    /** constructor for proportional integral derivative controller */
    let pid: {
        new(): pid;
        /**
         * @param min minimum final output
         * @param max maximum final output
         * @param sum maximum integral output
         */
        new(min: number, max: number, sum?: number): pid;
        readonly prototype: pid;
    }

    /** min(a,b) */
    const PID_FUZZY_CAP: number;
    /** a*b */
    const PID_FUZZY_CAP_ALGEBRA: number;
    /** max(a+b-1,0) */
    const PID_FUZZY_CAP_BOUNDED: number;
    /** max(a,b) */
    const PID_FUZZY_CUP: number;
    /** a+b-a*b */
    const PID_FUZZY_CUP_ALGEBRA: number;
    /** min(a+b,1) */
    const PID_FUZZY_CUP_BOUNDED: number;
    /** sqrt(a,b)*sqrt(1-(1-a)*(1-b)) */
    const PID_FUZZY_EQU: number;

    interface pid_fuzzy {
        /** PID_OFF PID_POS PID_INC */
        mode: number;
        /** proportional constant */
        kp: number;
        /** integral constant */
        ki: number;
        /** derivative constant */
        kd: number;
        /** maximum integral output */
        summax: number;
        /** maximum final output */
        outmax: number;
        /** minimum final output */
        outmin: number;
        /** controller output */
        readonly out: number;
        /** cache feedback */
        readonly fdb: number;
        /** cache error */
        readonly err: number;
        /** number of order in the square matrix */
        readonly order: number;
        /**
         * set fuzzy relational operator for fuzzy PID controller
         * @param op enumeration for fuzzy PID controller operator
         */
        op(op: number): pid_fuzzy;
        /**
         * set rule base for fuzzy PID controller
         * @param me e's membership function parameter table
         * @param mec ec's membership function parameter table
         * @param mkp Kp's rule base table which must be a square matrix
         * @param mki Ki's rule base table which must be a square matrix
         * @param mkd Kd's rule base table which must be a square matrix
         */
        rule(me: number[][], mec: number[][], mkp: number[][], mki: number[][], mkd: number[][]): pid_fuzzy;
        /**
         * set joint buffer for fuzzy PID controller
         * @param num the maximum number triggered by the rule
         */
        joint(num: number): pid_fuzzy;
        /**
         * set proportional integral derivative constant for fuzzy PID controller
         * @param kp proportional learning constant
         * @param ki integral learning constant
         * @param kd derivative learning constant
         */
        kpid(kp: number, ki: number, kd: number): pid_fuzzy;
        /**
         * calculate function for fuzzy PID controller
         * @param set setpoint
         * @param fdb feedback
         */
        iter(set: number, fdb: number): number;
        /** zero clear function for fuzzy PID controller */
        zero(): pid_fuzzy;
        delete(): void;
    }
    /** constructor for fuzzy PID controller */
    let pid_fuzzy: {
        new(): pid_fuzzy;
        /**
         * @param min minimum final output
         * @param max maximum final output
         * @param sum maximum integral output
         */
        new(min: number, max: number, sum?: number): pid_fuzzy;
        readonly prototype: pid_fuzzy;
    }

    interface pid_neuron {
        /** PID_OFF PID_POS PID_INC */
        mode: number;
        /** proportional output coefficient */
        k: number;
        /** proportional learning constant */
        kp: number;
        /** integral learning constant */
        ki: number;
        /** derivative learning constant */
        kd: number;
        /** proportional weight */
        wp: number;
        /** integral weight */
        wi: number;
        /** derivative weight */
        wd: number;
        /** maximum integral output */
        summax: number;
        /** maximum final output */
        outmax: number;
        /** minimum final output */
        outmin: number;
        /** controller output */
        readonly out: number;
        /** cache feedback */
        readonly fdb: number;
        /** cache error */
        readonly err: number;
        /** error change */
        readonly ec: number;
        /**
         * set proportional integral derivative constant for single neuron PID controller
         * @param k proportional output coefficient
         * @param kp proportional learning constant
         * @param ki integral learning constant
         * @param kd derivative learning constant
         */
        kpid(k: number, kp: number, ki: number, kd: number): pid_neuron;
        /**
         * set proportional integral derivative weight for single neuron PID controller
         * @param wp proportional weight
         * @param wi integral weight
         * @param wd derivative weight
         */
        wpid(wp: number, wi: number, wd: number): pid_neuron;
        /**
         * calculate function for single neuron PID controller
         * @param set setpoint
         * @param fdb feedback
         */
        iter(set: number, fdb: number): number;
        /** zero clear function for single neuron PID controller */
        zero(): pid_neuron;
        delete(): void;
    }
    /** constructor for single neuron PID controller */
    let pid_neuron: {
        new(): pid_neuron;
        /**
         * @param min minimum final output
         * @param max maximum final output
         */
        new(min: number, max: number): pid_neuron;
        readonly prototype: pid_neuron;
    }

    interface polytrack3 {
        /** coefficients, q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3 */
        readonly k: Float64Array | Float32Array;
        /**
         * calculate function for cubic polynomial trajectory position
         * @param dt difference between current time and initial time
         */
        pos(dt: number): number;
        /**
         * calculate function for cubic polynomial trajectory velocity
         * @param dt difference between current time and initial time
         */
        vel(dt: number): number;
        /**
         * calculate function for cubic polynomial trajectory acceleration
         * @param dt difference between current time and initial time
         */
        acc(dt: number): number;
        /**
         * calculate function for cubic polynomial trajectory
         * @param dt difference between current time and initial time
         */
        out(dt: number): Float64Array | Float32Array;
        delete(): void;
    }
    /** constructor for cubic polynomial trajectory */
    let polytrack3: {
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         */
        new(t0: number, t1: number, q0: number, q1: number): polytrack3;
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         * @param v0 velocity for source
         * @param v1 velocity for target
         */
        new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number): polytrack3;
        readonly prototype: polytrack3;
    }

    interface polytrack5 {
        /** coefficients, q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3+k_4(t-t_0)^4+k_5(t-t_0)^5 */
        readonly k: Float64Array | Float32Array;
        /**
         * calculate function for quintic polynomial trajectory position
         * @param dt difference between current time and initial time
         */
        pos(dt: number): number;
        /**
         * calculate function for quintic polynomial trajectory velocity
         * @param dt difference between current time and initial time
         */
        vel(dt: number): number;
        /**
         * calculate function for quintic polynomial trajectory acceleration
         * @param dt difference between current time and initial time
         */
        acc(dt: number): number;
        /**
         * calculate function for quintic polynomial trajectory
         * @param dt difference between current time and initial time
         */
        out(dt: number): Float64Array | Float32Array;
        delete(): void;
    }
    /** constructor for quintic polynomial trajectory */
    let polytrack5: {
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         */
        new(t0: number, t1: number, q0: number, q1: number): polytrack5;
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         * @param v0 velocity for source
         * @param v1 velocity for target
         */
        new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number): polytrack5;
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         * @param v0 velocity for source
         * @param v1 velocity for target
         * @param a0 acceleration for source
         * @param a1 acceleration for target
         */
        new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number, a0: number, a1: number): polytrack5;
        readonly prototype: polytrack5;
    }

    interface polytrack7 {
        /** coefficients, q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3+k_4(t-t_0)^4+k_5(t-t_0)^5+k_6(t-t_0)^6+k_7(t-t_0)^7 */
        readonly k: Float64Array | Float32Array;
        /**
         * calculate function for hepta polynomial trajectory position
         * @param dt difference between current time and initial time
         */
        pos(dt: number): number;
        /**
         * calculate function for hepta polynomial trajectory velocity
         * @param dt difference between current time and initial time
         */
        vel(dt: number): number;
        /**
         * calculate function for hepta polynomial trajectory acceleration
         * @param dt difference between current time and initial time
         */
        acc(dt: number): number;
        /**
         * calculate function for hepta polynomial trajectory jerk
         * @param dt difference between current time and initial time
         */
        jer(dt: number): number;
        /**
         * calculate function for hepta polynomial trajectory
         * @param dt difference between current time and initial time
         */
        out(dt: number): Float64Array | Float32Array;
        delete(): void;
    }
    /** constructor for hepta polynomial trajectory */
    let polytrack7: {
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         */
        new(t0: number, t1: number, q0: number, q1: number): polytrack7;
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         * @param v0 velocity for source
         * @param v1 velocity for target
         */
        new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number): polytrack7;
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         * @param v0 velocity for source
         * @param v1 velocity for target
         * @param a0 acceleration for source
         * @param a1 acceleration for target
         */
        new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number, a0: number, a1: number): polytrack7;
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         * @param v0 velocity for source
         * @param v1 velocity for target
         * @param a0 acceleration for source
         * @param a1 acceleration for target
         * @param j0 jerk for source
         * @param j1 jerk for target
         */
        new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number, a0: number, a1: number, j0: number, j1: number): polytrack7;
        readonly prototype: polytrack7;
    }

    interface tf {
        /** input for transfer function */
        readonly input: Float64Array | Float32Array;
        /** output for transfer function */
        readonly output: Float64Array | Float32Array;
        /** numerator for transfer function */
        num: Float64Array | Float32Array;
        /** denominator for transfer function */
        den: Float64Array | Float32Array;
        /**
         * set numerator for transfer function
         * @param num numerator
         */
        set_num(num: number[]): tf;
        /**
         * set denominator for transfer function
         * @param den denominator
         */
        set_den(den: number[]): tf;
        /**
         * calculate function for transfer function
         * @param x controller output
         */
        iter(x: number): number;
        /** zero clear function for transfer function */
        zero(): tf;
        delete(): void;
    }
    /** constructor for transfer function */
    let tf: {
        /**
         * @param num numerator
         * @param den denominator
         */
        new(num: number[], den: number[]): tf;
        readonly prototype: tf;
    }

    interface version {
        /** major number */
        major: number;
        /** minor number */
        minor: number;
        /** patch number */
        patch: number;
        /** return string representation of version */
        toString(): string;
        /**
         * parse function for version string
         * @param ver version string to be parsed
         */
        parse(ver: string): version;
        /**
         * compare this version with other versions
         * @param ver other version to be compared
         */
        cmp(ver: version): number;
        /**
         * this version is less than other version
         * @param ver other version to be compared
         */
        lt(ver: version): boolean;
        /**
         * this version is greater than other version
         * @param ver other version to be compared
         */
        gt(ver: version): boolean;
        /**
         * this version is less than or equal to other version
         * @param ver other version to be compared
         */
        le(ver: version): boolean;
        /**
         * this version is greater than or equal to other version
         * @param ver other version to be compared
         */
        ge(ver: version): boolean;
        /**
         * this version is equal to other version
         * @param ver other version to be compared
         */
        eq(ver: version): boolean;
        /**
         * this version is not equal to other version
         * @param ver other version to be compared
         */
        ne(ver: version): boolean;
        delete(): void;
    }
    /** constructor for version */
    let version: {
        /**
         * @param major major number
         * @param minor minor number
         * @param patch patch number
         */
        new(major?: number, minor?: number, patch?: number): version;
        readonly prototype: version;
    }

    /** algorithm library version string */
    const VERSION: string;
    /** algorithm library version major */
    const VERSION_MAJOR: number;
    /** algorithm library version minor */
    const VERSION_MINOR: number;
    /** algorithm library version patch */
    const VERSION_PATCH: number;
    /** algorithm library version tweak */
    const VERSION_TWEAK: string;

    /**
     * algorithm library version check
     * @param major required major number
     * @param minor required minor number
     * @param patch required patch number
     * @returns -3(<major),-2(<minor),-1(<patch),0,+1(>patch),+2(>minor),+3(>major)
     */
    function version_check(major: number, minor: number, patch: number): number;
}
export = liba;
