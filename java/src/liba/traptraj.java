package liba;

import java.nio.ByteBuffer;

/** trapezoidal velocity profile trajectory */
public class traptraj {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    /**
     * get total time for trapezoidal velocity profile trajectory
     *
     * @return total time
     */
    public final native double t();

    /**
     * get initial position for trapezoidal velocity profile
     * trajectory
     *
     * @return initial position
     */
    public final native double q0();

    /**
     * get final position for trapezoidal velocity profile
     * trajectory
     *
     * @return final position
     */
    public final native double q1();

    /**
     * get initial velocity for trapezoidal velocity profile trajectory
     *
     * @return initial velocity
     */
    public final native double v0();

    /**
     * get final velocity for trapezoidal velocity profile trajectory
     *
     * @return final velocity
     */
    public final native double v1();

    /**
     * get constant velocity for trapezoidal velocity profile trajectory
     *
     * @return constant velocity
     */
    public final native double vc();

    /**
     * get time before constant velocity for trapezoidal velocity profile trajectory
     *
     * @return time before constant velocity
     */
    public final native double ta();

    /**
     * get time after constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return time after constant velocity
     */
    public final native double td();

    /**
     * get position before constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return position before constant velocity
     */
    public final native double qa();

    /**
     * get position after constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return position after constant velocity
     */
    public final native double qd();

    /**
     * get acceleration before constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return acceleration before constant velocity
     */
    public final native double ac();

    /**
     * get acceleration after constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return acceleration after constant velocity
     */
    public final native double de();

    /**
     * construct a new {@link traptraj} object
     *
     * @param vm defines the maximum velocity at which the system can work
     * @param ac defines the acceleration before constant velocity
     * @param de defines the acceleration after constant velocity
     * @param q0 defines the initial position
     * @param q1 defines the final position
     * @param v0 defines the initial velocity
     * @param v0 defines the final velocity
     */
    public traptraj(double vm, double ac, double de, double q0, double q1, double v0, double v1) {
        gen(vm, ac, de, q0, q1, v0, v1);
    }

    /**
     * generate for trapezoidal velocity profile trajectory
     *
     * @param vm defines the maximum velocity at which the system can work
     * @param ac defines the acceleration before constant velocity
     * @param de defines the acceleration after constant velocity
     * @param q0 defines the initial position
     * @param q1 defines the final position
     * @param v0 defines the initial velocity
     * @param v0 defines the final velocity
     * @return total time
     */
    public final native double gen(double vm, double ac, double de, double q0, double q1, double v0, double v1);

    /**
     * calculate for trapezoidal velocity profile trajectory position
     *
     * @param dt difference between current time and initial time
     * @return position output
     */
    public final native double pos(double dt);

    /**
     * calculate for trapezoidal velocity profile trajectory velocity
     *
     * @param dt difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double dt);

    /**
     * calculate for trapezoidal velocity profile trajectory acceleration
     *
     * @param dt difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double dt);
}
