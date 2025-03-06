package liba;

import java.nio.ByteBuffer;

/** quintic polynomial trajectory */
public class trajpoly5 {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        clinit();
    }

    static final native void clinit();

    /**
     * get coefficients of position for quintic polynomial trajectory
     *
     * @return coefficients of position
     */
    public final native double[] c0();

    /**
     * get coefficients of velocity for quintic polynomial trajectory
     *
     * @return coefficients of velocity
     */
    public final native double[] c1();

    /**
     * get coefficients of acceleration for quintic polynomial trajectory
     *
     * @return coefficients of acceleration
     */
    public final native double[] c2();

    /**
     * construct a new {@link trajpoly5} object
     *
     * @param ts difference between final time and initial time
     * @param p0 initial position
     * @param p1 final position
     * @param v0 initial velocity
     * @param v1 final velocity
     * @param a0 initial acceleration
     * @param a1 final acceleration
     */
    public trajpoly5(double ts, double p0, double p1, double v0, double v1,
            double a0, double a1) {
        gen(ts, p0, p1, v0, v1, a0, a1);
    }

    /**
     * generate for quintic polynomial trajectory
     *
     * @param ts difference between final time and initial time
     * @param p0 initial position
     * @param p1 final position
     * @param v0 initial velocity
     * @param v1 final velocity
     * @param a0 initial acceleration
     * @param a1 final acceleration
     * @return {@link trajpoly5}
     */
    public final native trajpoly5 gen(double ts, double p0, double p1, double v0, double v1,
            double a0, double a1);

    /**
     * compute position for quintic polynomial trajectory
     *
     * @param x difference between current time and initial time
     * @return position output
     */
    public final native double pos(double x);

    /**
     * compute velocity for quintic polynomial trajectory
     *
     * @param x difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double x);

    /**
     * compute acceleration for quintic polynomial trajectory
     *
     * @param x difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double x);
}
