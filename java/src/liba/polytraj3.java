package liba;

/** cubic polynomial trajectory */
public class polytraj3 {
    double[] k = new double[4];
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    /**
     * get coefficients for cubic polynomial trajectory,
     * q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3
     *
     * @return coefficients
     */
    public final double[] k() {
        return k;
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
     * calculate for cubic polynomial trajectory
     *
     * @param dt difference between current time and initial time
     * @return current output
     */
    public final native double[] out(double dt);

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
