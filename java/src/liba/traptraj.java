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
     * get time period of increased velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return time period of increased velocity
     */
    public final native double ta();

    /**
     * get displacement as velocity increases for trapezoidal velocity profile
     * trajectory
     *
     * @return displacement as velocity increases
     */
    public final native double qa();

    /**
     * get time period of constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return time period of constant velocity
     */
    public final native double tc();

    /**
     * get displacement at constant velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return displacement at constant velocity
     */
    public final native double qc();

    /**
     * get time period of decreased velocity for trapezoidal velocity profile
     * trajectory
     *
     * @return time period of decreased velocity
     */
    public final native double td();

    /**
     * get displacement as velocity decreases for trapezoidal velocity profile
     * trajectory
     *
     * @return displacement as velocity decreases
     */
    public final native double qd();

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
