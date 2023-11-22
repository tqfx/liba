package liba;

/** hepta polynomial trajectory */
public class polytrack7 {
    double[] k = new double[8];
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    /**
     * get coefficients for hepta polynomial trajectory,
     * q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3+k_4(t-t_0)^4+k_5(t-t_0)^5+k_6(t-t_0)^6+k_7(t-t_0)^7
     *
     * @return coefficients
     */
    public final double[] k() {
        return k;
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
     * @return {@link polytrack7}
     */
    public final native polytrack7 gen(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1, double j0, double j1);

    /**
     * calculate for hepta polynomial trajectory
     *
     * @param dt difference between current time and initial time
     * @return current output
     */
    public final native double[] out(double dt);

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
