package liba;

import java.nio.ByteBuffer;

/** proportional integral derivative controller */
public class pid {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        clinit();
    }

    static final native void clinit();

    final native void init();

    /**
     * construct a new {@link pid} object
     */
    public pid() {
        init();
    }

    /**
     * get proportional constant for PID controller
     *
     * @return proportional constant
     */
    public final native double kp();

    /**
     * set proportional constant for PID controller
     *
     * @param kp proportional constant
     * @return {@link pid}
     */
    public final native pid kp(double kp);

    /**
     * get integral constant for PID controller
     *
     * @return integral constant
     */
    public final native double ki();

    /**
     * set integral constant for PID controller
     *
     * @param ki integral constant
     * @return {@link pid}
     */
    public final native pid ki(double ki);

    /**
     * get derivative constant for PID controller
     *
     * @return derivative constant
     */
    public final native double kd();

    /**
     * set derivative constant for PID controller
     *
     * @param kd derivative constant
     * @return {@link pid}
     */
    public final native pid kd(double kd);

    /**
     * get maximum integral output for PID controller
     *
     * @return maximum integral output
     */
    public final native double summax();

    /**
     * set maximum integral output for PID controller
     *
     * @param max maximum integral output
     * @return {@link pid}
     */
    public final native pid summax(double max);

    /**
     * get minimum integral output for PID controller
     *
     * @return minimum integral output
     */
    public final native double summin();

    /**
     * set minimum integral output for PID controller
     *
     * @param min minimum integral output
     * @return {@link pid}
     */
    public final native pid summin(double min);

    /**
     * get cached integral output for PID controller
     *
     * @return cached integral output
     */
    public final native double sum();

    /**
     * get maximum final output for PID controller
     *
     * @return maximum final output
     */
    public final native double outmax();

    /**
     * set maximum final output for PID controller
     *
     * @param max maximum final output
     * @return {@link pid}
     */
    public final native pid outmax(double max);

    /**
     * get minimum final output for PID controller
     *
     * @return minimum final output
     */
    public final native double outmin();

    /**
     * set minimum final output for PID controller
     *
     * @param min minimum final output
     * @return {@link pid}
     */
    public final native pid outmin(double min);

    /**
     * get cached output for PID controller
     *
     * @return cached output
     */
    public final native double out();

    /**
     * get cached feedback for PID controller
     *
     * @return cached feedback
     */
    public final native double fdb();

    /**
     * get cached error for PID controller
     *
     * @return cached error
     */
    public final native double err();

    /**
     * set proportional integral derivative constant for PID controller
     *
     * @param kp proportional constant
     * @param ki integral constant
     * @param kd derivative constant
     * @return {@link pid}
     */
    public final native pid set_kpid(double kp, double ki, double kd);

    /**
     * calculate for PID controller
     *
     * @param set setpoint value
     * @param fdb feedback value
     * @return setpoint value
     */
    public final native double run(double set, double fdb);

    /**
     * calculate for positional PID controller
     *
     * @param set setpoint value
     * @param fdb feedback value
     * @return output value
     */
    public final native double pos(double set, double fdb);

    /**
     * calculate for incremental PID controller
     *
     * @param set setpoint value
     * @param fdb feedback value
     * @return output value
     */
    public final native double inc(double set, double fdb);

    /**
     * zeroing for PID controller
     *
     * @return {@link pid}
     */
    public final native pid zero();
}
