package liba;

import java.nio.ByteBuffer;

/** hepta polynomial trajectory */
public class polytraj7 {
    ByteBuffer ctx;
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
    public final native double[] q();

    /**
     * get coefficients of velocity for hepta polynomial trajectory
     *
     * @return coefficients of velocity
     */
    public final native double[] v();

    /**
     * get coefficients of acceleration for hepta polynomial trajectory
     *
     * @return coefficients of acceleration
     */
    public final native double[] a();

    /**
     * get coefficients of jerk for hepta polynomial trajectory
     *
     * @return coefficients of jerk
     */
    public final native double[] j();

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
