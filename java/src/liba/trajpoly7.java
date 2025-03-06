package liba;

import java.nio.ByteBuffer;

/** hepta polynomial trajectory */
public class trajpoly7 {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        clinit();
    }

    static final native void clinit();

    /**
     * get coefficients of position for hepta polynomial trajectory
     *
     * @return coefficients of position
     */
    public final native double[] c0();

    /**
     * get coefficients of velocity for hepta polynomial trajectory
     *
     * @return coefficients of velocity
     */
    public final native double[] c1();

    /**
     * get coefficients of acceleration for hepta polynomial trajectory
     *
     * @return coefficients of acceleration
     */
    public final native double[] c2();

    /**
     * get coefficients of jerk for hepta polynomial trajectory
     *
     * @return coefficients of jerk
     */
    public final native double[] c3();

    /**
     * construct a new {@link trajpoly7} object
     *
     * @param ts difference between final time and initial time
     * @param p0 initial position
     * @param p1 final position
     * @param v0 initial velocity
     * @param v1 final velocity
     * @param a0 initial acceleration
     * @param a1 final acceleration
     * @param j0 initial jerk
     * @param j1 final jerk
     */
    public trajpoly7(double ts, double p0, double p1, double v0, double v1,
            double a0, double a1, double j0, double j1) {
        gen(ts, p0, p1, v0, v1, a0, a1, j0, j1);
    }

    /**
     * generate for hepta polynomial trajectory
     *
     * @param ts difference between final time and initial time
     * @param p0 initial position
     * @param p1 final position
     * @param v0 initial velocity
     * @param v1 final velocity
     * @param a0 initial acceleration
     * @param a1 final acceleration
     * @param j0 initial jerk
     * @param j1 final jerk
     * @return {@link trajpoly7}
     */
    public final native trajpoly7 gen(double ts, double p0, double p1, double v0, double v1,
            double a0, double a1, double j0, double j1);

    /**
     * compute position for hepta polynomial trajectory
     *
     * @param x difference between current time and initial time
     * @return position output
     */
    public final native double pos(double x);

    /**
     * compute velocity for hepta polynomial trajectory
     *
     * @param x difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double x);

    /**
     * compute acceleration for hepta polynomial trajectory
     *
     * @param x difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double x);

    /**
     * compute jerk for hepta polynomial trajectory
     *
     * @param x difference between current time and initial time
     * @return jerk output
     */
    public final native double jer(double x);
}
