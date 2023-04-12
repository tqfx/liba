package liba;

/** quintic polynomial trajectory */
public class polytrack5 {
    /** quantity */
    public double[] k = new double[6];
    /** time */
    public double[] t = new double[2];
    /** position */
    public double[] q = new double[2];
    /** velocity */
    public double[] v = new double[2];
    /** acceleration */
    public double[] a = new double[2];

    /**
     * construct a new {@link polytrack5} object
     *
     * @param source source for trajectory
     * @param target target for trajectory
     */
    public polytrack5(double[] source, double[] target) {
        this.init(source, target);
    }

    /**
     * construct a new {@link polytrack5} object
     *
     * @param t time
     * @param q position
     * @param v velocity
     */
    public polytrack5(double[] t, double[] q, double[] v) {
        this.init(t, q, v);
    }

    /**
     * construct a new {@link polytrack5} object
     *
     * @param t time
     * @param q position
     * @param v velocity
     * @param a acceleration
     */
    public polytrack5(double[] t, double[] q, double[] v, double[] a) {
        this.init(t, q, v, a);
    }

    /**
     * construct a new {@link polytrack5} object
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     */
    public polytrack5(double t0, double t1, double q0, double q1) {
        this.init(t0, t1, q0, q1);
    }

    /**
     * construct a new {@link polytrack5} object
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     */
    public polytrack5(double t0, double t1, double q0, double q1, double v0, double v1) {
        this.init(t0, t1, q0, q1, v0, v1);
    }

    /**
     * construct a new {@link polytrack5} object
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
    public polytrack5(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1) {
        this.init(t0, t1, q0, q1, v0, v1, a0, a1);
    }

    /**
     * initialize function for quintic polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     * @param a0 acceleration for source
     * @param a1 acceleration for target
     * @return {@link polytrack5}
     */
    public final native polytrack5 init(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1);

    /**
     * initialize function for quintic polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     * @return {@link polytrack5}
     */
    public final native polytrack5 init(double t0, double t1, double q0, double q1, double v0, double v1);

    /**
     * initialize function for quintic polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @return {@link polytrack5}
     */
    public final native polytrack5 init(double t0, double t1, double q0, double q1);

    /**
     * initialize function for quintic polynomial trajectory
     *
     * @param t time
     * @param q position
     * @param v velocity
     * @param a acceleration
     * @return {@link polytrack5}
     */
    public final native polytrack5 init(double[] t, double[] q, double[] v, double[] a);

    /**
     * initialize function for quintic polynomial trajectory
     *
     * @param t time
     * @param q position
     * @param v velocity
     * @return {@link polytrack5}
     */
    public final native polytrack5 init(double[] t, double[] q, double[] v);

    /**
     * initialize function for quintic polynomial trajectory
     *
     * @param source source for trajectory
     * @param target target for trajectory
     * @return {@link polytrack5}
     */
    public final native polytrack5 init(double[] source, double[] target);

    /**
     * process function for quintic polynomial trajectory
     *
     * @param ts current time unit(s)
     * @return current output
     */
    public final native double[] out(double ts);

    /**
     * process function for quintic polynomial trajectory position
     *
     * @param ts current time unit(s)
     * @return position output
     */
    public final native double pos(double ts);

    /**
     * process function for quintic polynomial trajectory velocity
     *
     * @param ts current time unit(s)
     * @return velocity output
     */
    public final native double vec(double ts);

    /**
     * process function for quintic polynomial trajectory acceleration
     *
     * @param ts current time unit(s)
     * @return acceleration output
     */
    public final native double acc(double ts);
}
