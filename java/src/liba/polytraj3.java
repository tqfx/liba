package liba;

/** cubic polynomial trajectory */
public class polytraj3 {
    double[] q = new double[4];
    double[] v = new double[3];
    double[] a = new double[2];
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    /**
     * get coefficients of position for cubic polynomial trajectory
     *
     * @return coefficients of position
     */
    public final double[] q() {
        return q;
    }

    /**
     * get coefficients of velocity for cubic polynomial trajectory
     *
     * @return coefficients of velocity
     */
    public final double[] v() {
        return v;
    }

    /**
     * get coefficients of acceleration for cubic polynomial trajectory
     *
     * @return coefficients of acceleration
     */
    public final double[] a() {
        return a;
    }

    /**
     * construct a new {@link polytraj3} object
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     */
    public polytraj3(double t0, double t1, double q0, double q1, double v0, double v1) {
        gen(t0, t1, q0, q1, v0, v1);
    }

    /**
     * generate for cubic polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     * @return {@link polytraj3}
     */
    public final native polytraj3 gen(double t0, double t1, double q0, double q1, double v0, double v1);

    /**
     * calculate for cubic polynomial trajectory position
     *
     * @param dt difference between current time and initial time
     * @return position output
     */
    public final native double pos(double dt);

    /**
     * calculate for cubic polynomial trajectory velocity
     *
     * @param dt difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double dt);

    /**
     * calculate for cubic polynomial trajectory acceleration
     *
     * @param dt difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double dt);
}
