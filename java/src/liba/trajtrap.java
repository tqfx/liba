package liba;

import java.nio.ByteBuffer;

/** trapezoidal velocity trajectory */
public class trajtrap {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        clinit();
    }

    static final native void clinit();

    final native void init();

    /**
     * get total duration for trapezoidal velocity trajectory
     *
     * @return total duration
     */
    public final native double t();

    /**
     * get initial position for trapezoidal velocity trajectory
     *
     * @return initial position
     */
    public final native double p0();

    /**
     * get final position for trapezoidal velocity trajectory
     *
     * @return final position
     */
    public final native double p1();

    /**
     * get initial velocity for trapezoidal velocity trajectory
     *
     * @return initial velocity
     */
    public final native double v0();

    /**
     * get final velocity for trapezoidal velocity trajectory
     *
     * @return final velocity
     */
    public final native double v1();

    /**
     * get constant velocity for trapezoidal velocity trajectory
     *
     * @return constant velocity
     */
    public final native double vc();

    /**
     * get time before constant velocity for trapezoidal velocity trajectory
     *
     * @return time before constant velocity
     */
    public final native double ta();

    /**
     * get time after constant velocity for trapezoidal velocity trajectory
     *
     * @return time after constant velocity
     */
    public final native double td();

    /**
     * get position before constant velocity for trapezoidal velocity trajectory
     *
     * @return position before constant velocity
     */
    public final native double pa();

    /**
     * get position after constant velocity for trapezoidal velocity trajectory
     *
     * @return position after constant velocity
     */
    public final native double pd();

    /**
     * get acceleration before constant velocity for trapezoidal velocity trajectory
     *
     * @return acceleration before constant velocity
     */
    public final native double ac();

    /**
     * get acceleration after constant velocity for trapezoidal velocity trajectory
     *
     * @return acceleration after constant velocity
     */
    public final native double de();

    /**
     * construct a new {@link trajtrap} object
     */
    public trajtrap() {
        init();
    }

    /**
     * generate for trapezoidal velocity trajectory
     *
     * @param vm defines the maximum velocity during system operation
     * @param ac defines the acceleration before constant velocity
     * @param de defines the acceleration after constant velocity
     * @param p0 defines the initial position
     * @param p1 defines the final position
     * @param v0 defines the initial velocity
     * @param v1 defines the final velocity
     * @return total duration
     */
    public final native double gen(double vm, double ac, double de, double p0, double p1, double v0, double v1);

    /**
     * compute position for trapezoidal velocity trajectory
     *
     * @param x difference between current time and initial time
     * @return position output
     */
    public final native double pos(double x);

    /**
     * compute velocity for trapezoidal velocity trajectory
     *
     * @param x difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double x);

    /**
     * compute acceleration for trapezoidal velocity trajectory
     *
     * @param x difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double x);
}
