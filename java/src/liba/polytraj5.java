package liba;

import java.nio.ByteBuffer;

/** quintic polynomial trajectory */
public class polytraj5 {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    /**
     * get coefficients of position for quintic polynomial trajectory
     *
     * @return coefficients of position
     */
    public final native double[] q();

    /**
     * get coefficients of velocity for quintic polynomial trajectory
     *
     * @return coefficients of velocity
     */
    public final native double[] v();

    /**
     * get coefficients of acceleration for quintic polynomial trajectory
     *
     * @return coefficients of acceleration
     */
    public final native double[] a();

    /**
     * construct a new {@link polytraj5} object
     *
     * @param ts difference between final time and initial time
     * @param q0 initial position
     * @param q1 final position
     * @param v0 initial velocity
     * @param v1 final velocity
     * @param a0 initial acceleration
     * @param a1 final acceleration
     */
    public polytraj5(double ts, double q0, double q1, double v0, double v1,
            double a0, double a1) {
        gen(ts, q0, q1, v0, v1, a0, a1);
    }

    /**
     * generate for quintic polynomial trajectory
     *
     * @param ts difference between final time and initial time
     * @param q0 initial position
     * @param q1 final position
     * @param v0 initial velocity
     * @param v1 final velocity
     * @param a0 initial acceleration
     * @param a1 final acceleration
     * @return {@link polytraj5}
     */
    public final native polytraj5 gen(double ts, double q0, double q1, double v0, double v1,
            double a0, double a1);

    /**
     * calculate for quintic polynomial trajectory position
     *
     * @param dt difference between current time and initial time
     * @return position output
     */
    public final native double pos(double dt);

    /**
     * calculate for quintic polynomial trajectory velocity
     *
     * @param dt difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double dt);

    /**
     * calculate for quintic polynomial trajectory acceleration
     *
     * @param dt difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double dt);
}
