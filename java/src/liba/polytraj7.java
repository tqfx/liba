package liba;

/** hepta polynomial trajectory */
public class polytraj7 {
    double[] q = new double[8];
    double[] v = new double[7];
    double[] a = new double[6];
    double[] j = new double[5];
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    /**
     * get coefficients of position for hepta polynomial trajectory
     *
     * @return coefficients of position
     */
    public final double[] q() {
        return q;
    }

    /**
     * get coefficients of velocity for hepta polynomial trajectory
     *
     * @return coefficients of velocity
     */
    public final double[] v() {
        return v;
    }

    /**
     * get coefficients of acceleration for hepta polynomial trajectory
     *
     * @return coefficients of acceleration
     */
    public final double[] a() {
        return a;
    }

    /**
     * get coefficients of jerk for hepta polynomial trajectory
     *
     * @return coefficients of jerk
     */
    public final double[] j() {
        return j;
    }

    /**
     * construct a new {@link polytraj7} object
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
    public polytraj7(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1, double j0, double j1) {
        gen(t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    }

    /**
     * generate for hepta polynomial trajectory
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
     * @return {@link polytraj7}
     */
    public final native polytraj7 gen(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1, double j0, double j1);

    /**
     * calculate for hepta polynomial trajectory position
     *
     * @param dt difference between current time and initial time
     * @return position output
     */
    public final native double pos(double dt);

    /**
     * calculate for hepta polynomial trajectory velocity
     *
     * @param dt difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double dt);

    /**
     * calculate for hepta polynomial trajectory acceleration
     *
     * @param dt difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double dt);

    /**
     * calculate for hepta polynomial trajectory jerk
     *
     * @param dt difference between current time and initial time
     * @return jerk output
     */
    public final native double jer(double dt);
}
