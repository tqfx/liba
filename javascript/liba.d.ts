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
    /** generalized bell-shaped membership function */
    const MF_GBELL: number;
    /** sigmoidal membership function */
    const MF_SIG: number;
    /** trapezoidal membership function */
    const MF_TRAP: number;
    /** triangular membership function */
    const MF_TRI: number;
    /** z-shaped membership function */
    const MF_Z: number;

    /**
     * gaussian membership function
     * @param x independent variable
     * @param sigma sigma
     * @param c c
     */
    function mf_gauss(x: number, sigma: number, c: number): number;
    /**
     * generalized bell-shaped membership function
     * @param x independent variable
     * @param a a
     * @param b b
     * @param c c
     */
    function mf_gbell(x: number, a: number, b: number, c: number): number;
    /**
     * sigmoidal membership function
     * @param x independent variable
     * @param a a
     * @param b b
     */
    function mf_sig(x: number, a: number, b: number): number;
    /**
     * trapezoidal membership function
     * @param x independent variable
     * @param a a
     * @param b b
     * @param c c
     * @param d d
     */
    function mf_trap(x: number, a: number, b: number, c: number, d: number): number;
    /**
     * triangular membership function
     * @param x independent variable
     * @param a a
     * @param b b
     * @param c c
     */
    function mf_tri(x: number, a: number, b: number, c: number): number;
    /**
     * z-shaped membership function
     * @param x independent variable
     * @param a a
     * @param b b
     */
    function mf_z(x: number, a: number, b: number): number;

    /** turn off PID controller */
    const PID_OFF: number;
    /** positional PID controller */
    const PID_POS: number;
    /** incremental PID controller */
    const PID_INC: number;

    interface pid {
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
    }
    interface pid_constructor {
        /**
         * @param min minimum final output
         * @param max maximum final output
         * @param sum maximum integral output
         */
        new(min: number, max: number, sum?: number): pid;
    }
    /** constructor for proportional integral derivative controller */
    var pid: pid_constructor;

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
        delete(): undefined;
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
    }
    interface pid_fuzzy_constructor {
        /**
         * @param min minimum final output
         * @param max maximum final output
         * @param sum maximum integral output
         */
        new(min: number, max: number, sum?: number): pid_fuzzy;
    }
    /** constructor for fuzzy PID controller */
    var pid_fuzzy: pid_fuzzy_constructor;

    interface pid_neuron {
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
    }
    interface pid_neuron_constructor {
        /**
         * @param min minimum final output
         * @param max maximum final output
         */
        new(min: number, max: number): pid_neuron;
    }
    /** constructor for single neuron PID controller */
    var pid_neuron: pid_neuron_constructor;

    interface polytrack3 {
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
        out(dt: number): number[];
    }
    interface polytrack3_constructor {
        /**
         * @param t0 time for source
         * @param t1 time for target
         * @param q0 position for source
         * @param q1 position for target
         * @param v0 velocity for source
         * @param v1 velocity for target
         */
        new(t0: number, t1: number, q0: number, q1: number, v0?: number, v1?: number): polytrack3;
    }
    /** constructor for cubic polynomial trajectory */
    var polytrack3: polytrack3_constructor;

    interface polytrack5 {
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
        out(dt: number): number[];
    }
    interface polytrack5_constructor {
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
        new(t0: number, t1: number, q0: number, q1: number, v0?: number, v1?: number, a0?: number, a1?: number): polytrack5;
    }
    /** constructor for quintic polynomial trajectory */
    var polytrack5: polytrack5_constructor;

    interface polytrack7 {
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
        out(dt: number): number[];
    }
    interface polytrack7_constructor {
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
        new(t0: number, t1: number, q0: number, q1: number, v0?: number, v1?: number, a0?: number, a1?: number, j0?: number, j1?: number): polytrack7;
    }
    /** constructor for hepta polynomial trajectory */
    var polytrack7: polytrack7_constructor;

    interface tf {
        delete(): undefined;
        /** get input for transfer function */
        input(): number[];
        /** get output for transfer function */
        output(): number[];
        /** get numerator for transfer function */
        num(): number[];
        /**
         * set numerator for transfer function
         * @param num numerator
         */
        set_num(num: number[]): tf;
        /** get denominator for transfer function */
        den(): number[];
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
    }
    interface tf_constructor {
        /**
         * @param num numerator
         * @param den denominator
         */
        new(num: number[], den: number[]): tf;
    }
    /** constructor for transfer function */
    var tf: tf_constructor;

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
    }
    interface version_constructor {
        /**
         * @param major major number
         * @param minor minor number
         * @param patch patch number
         */
        new(major?: number, minor?: number, patch?: number): version;
    }
    /** constructor for version */
    var version: version_constructor;

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
