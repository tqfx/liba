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
     * get position before constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return position before constant velocity
     */
    public final native double q1();

    /**
     * get position after constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return position after constant velocity
     */
    public final native double q2();

    /**
     * get time before constant velocity for trapezoidal velocity profile trajectory
     *
     * @return time before constant velocity
     */
    public final native double t1();

    /**
     * get time after constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return time after constant velocity
     */
    public final native double t2();

    /**
     * get initial velocity for trapezoidal velocity profile trajectory
     *
     * @return initial velocity
     */
    public final native double vs();

    /**
     * get constant velocity for trapezoidal velocity profile trajectory
     *
     * @return constant velocity
     */
    public final native double vc();

    /**
     * get final velocity for trapezoidal velocity profile trajectory
     *
     * @return final velocity
     */
    public final native double ve();

    /**
     * get final position for trapezoidal velocity profile
     * trajectory
     *
     * @return final position
     */
    public final native double q();

    /**
     * get total time for trapezoidal velocity profile trajectory
     *
     * @return total time
     */
    public final native double t();

    /**
     * construct a new {@link traptraj} object
     *
     * @param qm defines the distance from the start point to the end point
     * @param vm defines the maximum velocity at which the system can work
     * @param ac defines the acceleration before constant velocity
     * @param de defines the acceleration after constant velocity
     * @param vs defines the starting velocity
     * @param ve defines the ending velocity
     */
    public traptraj(double qm, double vm, double ac, double de, double vs, double ve) {
        gen(qm, vm, ac, de, vs, ve);
    }

    /**
     * generate for trapezoidal velocity profile trajectory
     *
     * @param qm defines the distance from the start point to the end point
     * @param vm defines the maximum velocity at which the system can work
     * @param ac defines the acceleration before constant velocity
     * @param de defines the acceleration after constant velocity
     * @param vs defines the starting velocity
     * @param ve defines the ending velocity
     * @return total time
     */
    public final native double gen(double qm, double vm, double ac, double de, double vs, double ve);

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
