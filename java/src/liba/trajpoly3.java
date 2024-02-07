package liba;

import java.nio.ByteBuffer;

/** cubic polynomial trajectory */
public class trajpoly3 {
    ByteBuffer ctx;
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
    public final native double[] q();

    /**
     * get coefficients of velocity for cubic polynomial trajectory
     *
     * @return coefficients of velocity
     */
    public final native double[] v();

    /**
     * get coefficients of acceleration for cubic polynomial trajectory
     *
     * @return coefficients of acceleration
     */
    public final native double[] a();

    /**
     * construct a new {@link trajpoly3} object
     *
     * @param ts difference between final time and initial time
     * @param q0 initial position
     * @param q1 final position
     * @param v0 initial velocity
     * @param v1 final velocity
     */
    public trajpoly3(double ts, double q0, double q1, double v0, double v1) {
        gen(ts, q0, q1, v0, v1);
    }

    /**
     * generate for cubic polynomial trajectory
     *
     * @param ts difference between final time and initial time
     * @param q0 initial position
     * @param q1 final position
     * @param v0 initial velocity
     * @param v1 final velocity
     * @return {@link trajpoly3}
     */
    public final native trajpoly3 gen(double ts, double q0, double q1, double v0, double v1);

    /**
     * calculate position for cubic polynomial trajectory
     *
     * @param dt difference between current time and initial time
     * @return position output
     */
    public final native double pos(double dt);

    /**
     * calculate velocity for cubic polynomial trajectory
     *
     * @param dt difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double dt);

    /**
     * calculate acceleration for cubic polynomial trajectory
     *
     * @param dt difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double dt);
}
