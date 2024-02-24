package liba;

import java.nio.ByteBuffer;

/** bell-shaped velocity trajectory */
public class trajbell {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        clinit();
    }

    static final native void clinit();

    final native void init();

    /**
     * get total duration for bell-shaped velocity trajectory
     *
     * @return total duration
     */
    public final native double t();

    /**
     * get constant velocity phase for bell-shaped velocity trajectory
     *
     * @return constant velocity phase
     */
    public final native double tv();

    /**
     * get acceleration phase for bell-shaped velocity trajectory
     *
     * @return acceleration phase
     */
    public final native double ta();

    /**
     * get deceleration phase for bell-shaped velocity trajectory
     *
     * @return deceleration phase
     */
    public final native double td();

    /**
     * get time-interval in which the jerk is constant (j max or j min ) during the
     * acceleration phase for bell-shaped velocity trajectory
     *
     * @return time-interval in which the jerk is constant (j max or j min ) during
     *         the acceleration phase
     */
    public final native double taj();

    /**
     * get time-interval in which the jerk is constant (j max or j min ) during the
     * deceleration phase for bell-shaped velocity trajectory
     *
     * @return time-interval in which the jerk is constant (j max or j min ) during
     *         the deceleration phase
     */
    public final native double tdj();

    /**
     * get initial position for bell-shaped velocity trajectory
     *
     * @return initial position
     */
    public final native double p0();

    /**
     * get final position for bell-shaped velocity trajectory
     *
     * @return final position
     */
    public final native double p1();

    /**
     * get initial velocity for bell-shaped velocity trajectory
     *
     * @return initial velocity
     */
    public final native double v0();

    /**
     * get final velocity for bell-shaped velocity trajectory
     *
     * @return final velocity
     */
    public final native double v1();

    /**
     * get maximum velocity for bell-shaped velocity trajectory
     *
     * @return maximum velocity
     */
    public final native double vm();

    /**
     * get maximum jerk for bell-shaped velocity trajectory
     *
     * @return maximum jerk
     */
    public final native double jm();

    /**
     * get maximum acceleration for bell-shaped velocity trajectory
     *
     * @return maximum acceleration
     */
    public final native double am();

    /**
     * get maximum deceleration for bell-shaped velocity trajectory
     *
     * @return maximum deceleration
     */
    public final native double dm();

    /**
     * construct a new {@link trajtrap} object
     */
    public trajbell() {
        init();
    }

    /**
     * generate for bell-shaped velocity trajectory
     *
     * @param jm defines the maximum jerk during system operation
     * @param am defines the maximum acceleration during system operation
     * @param vm defines the maximum velocity during system operation
     * @param p0 defines the initial position
     * @param p1 defines the final position
     * @param v0 defines the initial velocity
     * @param v1 defines the final velocity
     * @return total duration
     */
    public final native double gen(double jm, double am, double vm, double p0, double p1, double v0, double v1);

    /**
     * calculate position for bell-shaped velocity trajectory
     *
     * @param dt difference between current time and initial time
     * @return position output
     */
    public final native double pos(double dt);

    /**
     * calculate velocity for bell-shaped velocity trajectory
     *
     * @param dt difference between current time and initial time
     * @return velocity output
     */
    public final native double vel(double dt);

    /**
     * calculate acceleration for bell-shaped velocity trajectory
     *
     * @param dt difference between current time and initial time
     * @return acceleration output
     */
    public final native double acc(double dt);

    /**
     * calculate jerk for bell-shaped velocity trajectory
     *
     * @param dt difference between current time and initial time
     * @return jerk output
     */
    public final native double jer(double dt);
}
