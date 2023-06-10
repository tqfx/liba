package liba;

/** quintic polynomial trajectory */
public class polytrack5 {
    /** quantity */
    public double[] k = new double[6];
    static {
        System.loadLibrary("a");
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
        this.gen(t0, t1, q0, q1, v0, v1, a0, a1);
    }

    /**
     * generation function for quintic polynomial trajectory
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
    public final native polytrack5 gen(double t0, double t1, double q0, double q1, double v0, double v1,
            double a0, double a1);

    /**
     * calculate function for quintic polynomial trajectory
     *
     * @param dt difference between current time and initial time
     * @return current output
     */
    public final native double[] out(double dt);

    /**
     * calculate function for quintic polynomial trajectory position
     *
     * @param dt difference between current time and initial time
     * @return position output
     */
    public final native double pos(double dt);

    /**
     * calculate function for quintic polynomial trajectory velocity
     *
     * @param dt difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double dt);

    /**
     * calculate function for quintic polynomial trajectory acceleration
     *
     * @param dt difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double dt);
}
