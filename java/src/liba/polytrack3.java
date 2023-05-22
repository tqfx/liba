package liba;

/** cubic polynomial trajectory */
public class polytrack3 {
    /** quantity */
    public double[] k = new double[4];
    static {
        System.loadLibrary("a");
    }

    /**
     * construct a new {@link polytrack3} object
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     */
    public polytrack3(double t0, double t1, double q0, double q1, double v0, double v1) {
        this.gen(t0, t1, q0, q1, v0, v1);
    }

    /**
     * generation function for cubic polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     * @return {@link polytrack3}
     */
    public final native polytrack3 gen(double t0, double t1, double q0, double q1, double v0, double v1);

    /**
     * calculate function for cubic polynomial trajectory
     *
     * @param dt difference between current time and initial time
     * @return current output
     */
    public final native double[] out(double dt);

    /**
     * calculate function for cubic polynomial trajectory position
     *
     * @param dt difference between current time and initial time
     * @return position output
     */
    public final native double pos(double dt);

    /**
     * calculate function for cubic polynomial trajectory velocity
     *
     * @param dt difference between current time and initial time
     * @return velocity output
     */
    public final native double vec(double dt);

    /**
     * calculate function for cubic polynomial trajectory acceleration
     *
     * @param dt difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double dt);
}
