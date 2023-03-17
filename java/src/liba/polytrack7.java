package liba;

/** hepta polynomial trajectory */
public final class polytrack7 {
    /** quantity */
    public double[] k = new double[8];
    /** time */
    public double[] t = new double[2];
    /** position */
    public double[] q = new double[2];
    /** velocity */
    public double[] v = new double[2];
    /** acceleration */
    public double[] a = new double[2];
    /** jerk */
    public double[] j = new double[2];

    /**
     * construct a new {@link polytrack7} object
     *
     * @param source source for trajectory
     * @param target target for trajectory
     */
    public polytrack7(double[] source, double[] target) {
        this.init(source, target);
    }

    /**
     * construct a new {@link polytrack7} object
     *
     * @param t time
     * @param q position
     * @param v velocity
     */
    public polytrack7(double[] t, double[] q, double[] v) {
        this.init(t, q, v);
    }

    /**
     * construct a new {@link polytrack7} object
     *
     * @param t time
     * @param q position
     * @param v velocity
     * @param a acceleration
     */
    public polytrack7(double[] t, double[] q, double[] v, double[] a) {
        this.init(t, q, v, a);
    }

    /**
     * construct a new {@link polytrack7} object
     *
     * @param t time
     * @param q position
     * @param v velocity
     * @param a acceleration
     * @param j jerk
     */
    public polytrack7(double[] t, double[] q, double[] v, double[] a, double[] j) {
        this.init(t, q, v, a, j);
    }

    /**
     * construct a new {@link polytrack7} object
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     */
    public polytrack7(double t0, double t1, double q0, double q1) {
        this.init(t0, t1, q0, q1);
    }

    /**
     * construct a new {@link polytrack7} object
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     */
    public polytrack7(double t0, double t1, double q0, double q1, double v0, double v1) {
        this.init(t0, t1, q0, q1, v0, v1);
    }

    /**
     * construct a new {@link polytrack7} object
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     * @param a0 acceleration for source
     * @param a1 acceleration for target
     */
    public polytrack7(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1) {
        this.init(t0, t1, q0, q1, v0, v1, a0, a1);
    }

    /**
     * construct a new {@link polytrack7} object
     *
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
    public polytrack7(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1, double j0, double j1) {
        this.init(t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    }

    /**
     * initialize function for hepta polynomial trajectory
     *
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
     * @return {@link polytrack7}
     */
    public final native polytrack7 init(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1, double j0, double j1);

    /**
     * initialize function for hepta polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     * @param a0 acceleration for source
     * @param a1 acceleration for target
     * @return {@link polytrack7}
     */
    public final native polytrack7 init(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1);

    /**
     * initialize function for hepta polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     * @return {@link polytrack7}
     */
    public final native polytrack7 init(double t0, double t1, double q0, double q1, double v0, double v1);

    /**
     * initialize function for hepta polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @return {@link polytrack7}
     */
    public final native polytrack7 init(double t0, double t1, double q0, double q1);

    /**
     * initialize function for hepta polynomial trajectory
     *
     * @param t time
     * @param q position
     * @param v velocity
     * @param a acceleration
     * @param j jerk
     * @return {@link polytrack7}
     */
    public final native polytrack7 init(double[] t, double[] q, double[] v, double[] a, double[] j);

    /**
     * initialize function for hepta polynomial trajectory
     *
     * @param t time
     * @param q position
     * @param v velocity
     * @param a acceleration
     * @return {@link polytrack7}
     */
    public final native polytrack7 init(double[] t, double[] q, double[] v, double[] a);

    /**
     * initialize function for hepta polynomial trajectory
     *
     * @param t time
     * @param q position
     * @param v velocity
     * @return {@link polytrack7}
     */
    public final native polytrack7 init(double[] t, double[] q, double[] v);

    /**
     * initialize function for hepta polynomial trajectory
     *
     * @param source source for trajectory
     * @param target target for trajectory
     * @return {@link polytrack7}
     */
    public final native polytrack7 init(double[] source, double[] target);

    /**
     * process function for hepta polynomial trajectory
     *
     * @param ts current time unit(s)
     * @return current output
     */
    public final native double[] out(double ts);

    /**
     * process function for hepta polynomial trajectory position
     *
     * @param ts current time unit(s)
     * @return position output
     */
    public final native double pos(double ts);

    /**
     * process function for hepta polynomial trajectory velocity
     *
     * @param ts current time unit(s)
     * @return velocity output
     */
    public final native double vec(double ts);

    /**
     * process function for hepta polynomial trajectory acceleration
     *
     * @param ts current time unit(s)
     * @return acceleration output
     */
    public final native double acc(double ts);

    /**
     * process function for hepta polynomial trajectory jerk
     *
     * @param ts current time unit(s)
     * @return jerk output
     */
    public final native double jer(double ts);
}
