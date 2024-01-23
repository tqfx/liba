declare namespace liba {
  /**
   * square root of an unsigned integer
   * @param x independent variable
   * @return calculated result
   */
  function isqrt(x: number): number;
  /**
   * reciprocal of square-root
   * @param x independent variable
   * @return calculated result
   */
  function rsqrt(x: number): number;
  /**
   * a hash function whose prime number is 131
   * @param block block to be processed
   * @param value initial value
   * @return hash value
   */
  function hash_bkdr(block: string, value: number): number;
  /**
   * a hash function whose prime number is 65599
   * @param block block to be processed
   * @param value initial value
   * @return hash value
   */
  function hash_sdbm(block: string, value: number): number;

  interface crc8 {
    /** Cyclic Redundancy Check comparison table */
    readonly table: Uint8Array;
    /**
     * generate for 8-bit Cyclic Redundancy Check
     * @param poly polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    gen(poly: number, reversed?: boolean): crc8;
    /**
     * calculate for 8-bit Cyclic Redundancy Check
     * @param block block to be processed
     * @param value initial value
     * @return output value
     */
    eval(block: string, value: number): number;
    delete(): void;
  }
  /** constructor for 8-bit Cyclic Redundancy Check */
  let crc8: {
    /**
     * @param poly polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    new(poly: number, reversed?: boolean): crc8;
    readonly prototype: crc8;
  }

  interface crc16 {
    /** Cyclic Redundancy Check comparison table */
    readonly table: Uint16Array;
    /**
     * generate for 16-bit Cyclic Redundancy Check
     * @param poly polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    gen(poly: number, reversed?: boolean): crc16;
    /**
     * calculate for 16-bit Cyclic Redundancy Check
     * @param block block to be processed
     * @param value initial value
     * @return output value
     */
    eval(block: string, value: number): number;
    delete(): void;
  }
  /** constructor for 16-bit Cyclic Redundancy Check */
  let crc16: {
    /**
     * @param poly polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    new(poly: number, reversed?: boolean): crc16;
    readonly prototype: crc16;
  }

  interface crc32 {
    /** Cyclic Redundancy Check comparison table */
    readonly table: Uint32Array;
    /**
     * generate for 32-bit Cyclic Redundancy Check
     * @param poly polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    gen(poly: number, reversed?: boolean): crc32;
    /**
     * calculate for 32-bit Cyclic Redundancy Check
     * @param block block to be processed
     * @param value initial value
     * @return output value
     */
    eval(block: string, value: number): number;
    delete(): void;
  }
  /** constructor for 32-bit Cyclic Redundancy Check */
  let crc32: {
    /**
     * @param poly polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    new(poly: number, reversed?: boolean): crc32;
    readonly prototype: crc32;
  }

  interface crc64 {
    /** Cyclic Redundancy Check comparison table */
    readonly table: BigUint64Array;
    /**
     * generate for 64-bit Cyclic Redundancy Check
     * @param poly polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    gen(poly: bigint, reversed?: boolean): crc64;
    /**
     * calculate for 64-bit Cyclic Redundancy Check
     * @param block block to be processed
     * @param value initial value
     * @return output value
     */
    eval(block: string, value: bigint): bigint;
    delete(): void;
  }
  /** constructor for 64-bit Cyclic Redundancy Check */
  let crc64: {
    /**
     * @param poly polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    new(poly: bigint, reversed?: boolean): crc64;
    readonly prototype: crc64;
  }

  interface hpf {
    /** filter coefficient [0,1] */
    readonly alpha: number;
    /** filter output */
    readonly output: number;
    /** filter input */
    readonly input: number;
    /**
     * generate for High Pass Filter
     * @param fc cut-off frequency unit(hz)
     * @param ts sampling time unit(s)
     */
    gen(fc: number, ts: number): hpf;
    /**
     * calculate for High Pass Filter
     * @param x input value
     * @return output value
     */
    iter(x: number): number;
    /** zeroing for High Pass Filter */
    zero(): hpf;
    delete(): void;
  }
  /** constructor for High Pass Filter */
  let hpf: {
    /**
     * @param fc cut-off frequency unit(hz)
     * @param ts sampling time unit(s)
     */
    new(fc: number, ts: number): hpf
    /**
     * @param alpha filter coefficient [0,1]
     */
    new(alpha: number): hpf
    readonly prototype: hpf;
  }

  interface lpf {
    /** filter coefficient [0,1] */
    readonly alpha: number;
    /** filter output */
    readonly output: number;
    /**
     * generate for Low Pass Filter
     * @param fc cut-off frequency unit(hz)
     * @param ts sampling time unit(s)
     */
    gen(fc: number, ts: number): lpf;
    /**
     * calculate for Low Pass Filter
     * @param x input value
     * @return output value
     */
    iter(x: number): number;
    /** zeroing for Low Pass Filter */
    zero(): lpf;
    delete(): void;
  }
  /** constructor for Low Pass Filter */
  let lpf: {
    /**
     * @param fc cut-off frequency unit(hz)
     * @param ts sampling time unit(s)
     */
    new(fc: number, ts: number): lpf
    /**
     * @param alpha filter coefficient [0,1]
     */
    new(alpha: number): lpf
    readonly prototype: lpf;
  }

  /** membership function */
  let mf: {
    /** none */
    NUL: number;
    /** gaussian membership function */
    GAUSS: number;
    /** gaussian combination membership function */
    GAUSS2: number;
    /** generalized bell-shaped membership function */
    GBELL: number;
    /** sigmoidal membership function */
    SIG: number;
    /** difference between two sigmoidal membership functions */
    DSIG: number;
    /** product of two sigmoidal membership functions */
    PSIG: number;
    /** trapezoidal membership function */
    TRAP: number;
    /** triangular membership function */
    TRI: number;
    /** linear s-shaped saturation membership function */
    LINS: number;
    /** linear z-shaped saturation membership function */
    LINZ: number;
    /** s-shaped membership function */
    S: number;
    /** z-shaped membership function */
    Z: number;
    /** pi-shaped membership function */
    PI: number
    /**
     * gaussian membership function
     * @param x input value for which to compute membership value.
     * @param sigma is the standard deviation.
     * @param c is the mean.
     * @return membership value.
     */
    gauss(x: number, sigma: number, c: number): number;
    /**
     * gaussian combination membership function
     * @param x input value for which to compute membership value.
     * @param sigma1 is the standard deviation of the left gaussian function.
     * @param c1 is the mean of the left gaussian function.
     * @param sigma2 is the standard deviation of the right gaussian function.
     * @param c2 is the mean of the right gaussian function.
     * @return membership value.
     */
    gauss2(x: number, sigma1: number, c1: number, sigma2: number, c2: number): number;
    /**
     * generalized bell-shaped membership function
     * @param x input value for which to compute membership value.
     * @param a defines the width of the membership function, where a larger value creates a wider membership function.
     * @param b defines the shape of the curve on either side of the central plateau, where a larger value creates a more steep transition.
     * @param c defines the center of the membership function.
     * @return membership value.
     */
    gbell(x: number, a: number, b: number, c: number): number;
    /**
     * sigmoidal membership function
     * @param x input value for which to compute membership value.
     * @param a defines the width of the transition area.
     * @param c defines the center of the transition area.
     * @return membership value.
     */
    sig(x: number, a: number, c: number): number;
    /**
     * difference between two sigmoidal membership functions
     * @param x input value for which to compute membership value.
     * @param a1 defines the width of the first transition area.
     * @param c1 defines the center of the first transition area.
     * @param a2 defines the width of the second transition area.
     * @param c2 defines the center of the second transition area.
     * @return membership value.
     */
    dsig(x: number, a1: number, c1: number, a2: number, c2: number): number;
    /**
     * product of two sigmoidal membership functions
     * @param x input value for which to compute membership value.
     * @param a1 defines the width of the first transition area.
     * @param c1 defines the center of the first transition area.
     * @param a2 defines the width of the second transition area.
     * @param c2 defines the center of the second transition area.
     * @return membership value.
     */
    psig(x: number, a1: number, c1: number, a2: number, c2: number): number;
    /**
     * trapezoidal membership function
     * @param x input value for which to compute membership value.
     * @param a defines its left foot.
     * @param b defines its left shoulder.
     * @param c defines its right shoulder.
     * @param d defines its right foot.
     * @return membership value.
     */
    trap(x: number, a: number, b: number, c: number, d: number): number;
    /**
     * triangular membership function
     * @param x input value for which to compute membership value.
     * @param a defines its left foot.
     * @param b defines its peak.
     * @param c defines its right foot.
     * @return membership value.
     */
    tri(x: number, a: number, b: number, c: number): number;
    /**
     * linear s-shaped saturation membership function
     * @param x input value for which to compute membership value.
     * @param a defines its foot.
     * @param b defines its shoulder.
     * @return membership value.
     */
    lins(x: number, a: number, b: number): number;
    /**
     * linear z-shaped saturation membership function
     * @param x input value for which to compute membership value.
     * @param a defines its shoulder.
     * @param b defines its foot.
     * @return membership value.
     */
    linz(x: number, a: number, b: number): number;
    /**
     * s-shaped membership function
     * @param x input value for which to compute membership value.
     * @param a defines its foot.
     * @param b defines its shoulder.
     * @return membership value.
     */
    s(x: number, a: number, b: number): number;
    /**
     * z-shaped membership function
     * @param x input value for which to compute membership value.
     * @param a defines its shoulder.
     * @param b defines its foot.
     * @return membership value.
     */
    z(x: number, a: number, b: number): number;
    /**
     * pi-shaped membership function
     * @param x input value for which to compute membership value.
     * @param a defines its left foot.
     * @param b defines its left shoulder.
     * @param c defines its right shoulder.
     * @param d defines its right foot.
     * @return membership value.
     */
    pi(x: number, a: number, b: number, c: number, d: number): number;
  };

  interface pid {
    /** proportional constant */
    kp: number;
    /** integral constant */
    ki: number;
    /** derivative constant */
    kd: number;
    /** maximum integral output */
    summax: number;
    /** minimum integral output */
    summin: number;
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
     * calculate for PID controller
     * @param set setpoint value
     * @param fdb feedback value
     * @return setpoint value
     */
    run(set: number, fdb: number): number;
    /**
     * calculate for positional PID controller
     * @param set setpoint value
     * @param fdb feedback value
     * @return output value
     */
    pos(set: number, fdb: number): number;
    /**
     * calculate for incremental PID controller
     * @param set setpoint value
     * @param fdb feedback value
     * @return output value
     */
    inc(set: number, fdb: number): number;
    /** zeroing for PID controller */
    zero(): pid;
    delete(): void;
  }
  /** constructor for proportional integral derivative controller */
  let pid: {
    new(): pid;
    /** run and output setpoint */
    RUN: number;
    /** positional PID controller */
    POS: number;
    /** incremental PID controller */
    INC: number;
    readonly prototype: pid;
  }

  interface pid_fuzzy {
    /** proportional constant */
    kp: number;
    /** integral constant */
    ki: number;
    /** derivative constant */
    kd: number;
    /** maximum integral output */
    summax: number;
    /** minimum integral output */
    summin: number;
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
    /** maximum number triggered by the rule */
    joint: number;
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
    set_joint(num: number): pid_fuzzy;
    /**
     * set proportional integral derivative constant for fuzzy PID controller
     * @param kp proportional learning constant
     * @param ki integral learning constant
     * @param kd derivative learning constant
     */
    kpid(kp: number, ki: number, kd: number): pid_fuzzy;
    /**
     * calculate for fuzzy PID controller
     * @param set setpoint value
     * @param fdb feedback value
     * @return setpoint value
     */
    run(set: number, fdb: number): number;
    /**
     * calculate for positional fuzzy PID controller
     * @param set setpoint value
     * @param fdb feedback value
     * @return output value
     */
    pos(set: number, fdb: number): number;
    /**
     * calculate for incremental fuzzy PID controller
     * @param set setpoint value
     * @param fdb feedback value
     * @return output value
     */
    inc(set: number, fdb: number): number;
    /** zeroing for fuzzy PID controller */
    zero(): pid_fuzzy;
    delete(): void;
  }
  /** constructor for fuzzy PID controller */
  let pid_fuzzy: {
    new(): pid_fuzzy;
    /** min(a,b) */
    CAP: number;
    /** a*b */
    CAP_ALGEBRA: number;
    /** max(a+b-1,0) */
    CAP_BOUNDED: number;
    /** max(a,b) */
    CUP: number;
    /** a+b-a*b */
    CUP_ALGEBRA: number;
    /** min(a+b,1) */
    CUP_BOUNDED: number;
    /** sqrt(a,b)*sqrt(1-(1-a)*(1-b)) */
    EQU: number;
    readonly prototype: pid_fuzzy;
  }

  interface pid_neuro {
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
    kpid(k: number, kp: number, ki: number, kd: number): pid_neuro;
    /**
     * set proportional integral derivative weight for single neuron PID controller
     * @param wp proportional weight
     * @param wi integral weight
     * @param wd derivative weight
     */
    wpid(wp: number, wi: number, wd: number): pid_neuro;
    /**
     * calculate for single neuron PID controller
     * @param set setpoint value
     * @param fdb feedback value
     * @return setpoint value
     */
    run(set: number, fdb: number): number;
    /**
     * calculate for incremental single neuron PID controller
     * @param set setpoint value
     * @param fdb feedback value
     * @return output value
     */
    inc(set: number, fdb: number): number;
    /** zeroing for single neuron PID controller */
    zero(): pid_neuro;
    delete(): void;
  }
  /** constructor for single neuron PID controller */
  let pid_neuro: {
    new(): pid_neuro;
    readonly prototype: pid_neuro;
  }

  interface polytraj3 {
    /** coefficients of position */
    readonly q: Float64Array | Float32Array;
    /** coefficients of velocity */
    readonly v: Float64Array | Float32Array;
    /** coefficients of acceleration */
    readonly a: Float64Array | Float32Array;
    /**
     * calculate for cubic polynomial trajectory position
     * @param dt difference between current time and initial time
     */
    pos(dt: number): number;
    /**
     * calculate for cubic polynomial trajectory velocity
     * @param dt difference between current time and initial time
     */
    vel(dt: number): number;
    /**
     * calculate for cubic polynomial trajectory acceleration
     * @param dt difference between current time and initial time
     */
    acc(dt: number): number;
    delete(): void;
  }
  /** constructor for cubic polynomial trajectory */
  let polytraj3: {
    /**
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     */
    new(t0: number, t1: number, q0: number, q1: number): polytraj3;
    /**
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     */
    new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number): polytraj3;
    readonly prototype: polytraj3;
  }

  interface polytraj5 {
    /** coefficients of position */
    readonly q: Float64Array | Float32Array;
    /** coefficients of velocity */
    readonly v: Float64Array | Float32Array;
    /** coefficients of acceleration */
    readonly a: Float64Array | Float32Array;
    /**
     * calculate for quintic polynomial trajectory position
     * @param dt difference between current time and initial time
     */
    pos(dt: number): number;
    /**
     * calculate for quintic polynomial trajectory velocity
     * @param dt difference between current time and initial time
     */
    vel(dt: number): number;
    /**
     * calculate for quintic polynomial trajectory acceleration
     * @param dt difference between current time and initial time
     */
    acc(dt: number): number;
    delete(): void;
  }
  /** constructor for quintic polynomial trajectory */
  let polytraj5: {
    /**
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     */
    new(t0: number, t1: number, q0: number, q1: number): polytraj5;
    /**
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     */
    new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number): polytraj5;
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
    new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number, a0: number, a1: number): polytraj5;
    readonly prototype: polytraj5;
  }

  interface polytraj7 {
    /** coefficients of position */
    readonly q: Float64Array | Float32Array;
    /** coefficients of velocity */
    readonly v: Float64Array | Float32Array;
    /** coefficients of acceleration */
    readonly a: Float64Array | Float32Array;
    /** coefficients of jerk */
    readonly j: Float64Array | Float32Array;
    /**
     * calculate for hepta polynomial trajectory position
     * @param dt difference between current time and initial time
     */
    pos(dt: number): number;
    /**
     * calculate for hepta polynomial trajectory velocity
     * @param dt difference between current time and initial time
     */
    vel(dt: number): number;
    /**
     * calculate for hepta polynomial trajectory acceleration
     * @param dt difference between current time and initial time
     */
    acc(dt: number): number;
    /**
     * calculate for hepta polynomial trajectory jerk
     * @param dt difference between current time and initial time
     */
    jer(dt: number): number;
    delete(): void;
  }
  /** constructor for hepta polynomial trajectory */
  let polytraj7: {
    /**
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     */
    new(t0: number, t1: number, q0: number, q1: number): polytraj7;
    /**
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     */
    new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number): polytraj7;
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
    new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number, a0: number, a1: number): polytraj7;
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
    new(t0: number, t1: number, q0: number, q1: number, v0: number, v1: number, a0: number, a1: number, j0: number, j1: number): polytraj7;
    readonly prototype: polytraj7;
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
     * calculate for transfer function
     * @param x controller output
     */
    iter(x: number): number;
    /** zeroing for transfer function */
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
    /** third number */
    third: number;
    /** extra number */
    extra: number;
    /** return string representation of version */
    toString(): string;
    /**
     * parse for version string
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
     * @param third third number
     * @param extra extra number
     */
    new(major?: number, minor?: number, third?: number, extra?: number): version;
    /**
     * algorithm library version check
     * @param major required major number
     * @param minor required minor number
     * @param patch required patch number
     * @returns -3(<major),-2(<minor),-1(<patch),0,+1(>patch),+2(>minor),+3(>major)
     */
    check(major: number, minor: number, patch: number): number;
    /** algorithm library version major */
    MAJOR: number;
    /** algorithm library version minor */
    MINOR: number;
    /** algorithm library version patch */
    PATCH: number;
    /** algorithm library version tweak */
    TWEAK: number;
    readonly prototype: version;
  }

  /** algorithm library version string */
  const VERSION: string;
}
export = liba;
