package liba;

/** proportional integral derivative controller */
public class pid {
    /** turn off PID controller */
    public static final int OFF;
    /** positional PID controller */
    public static final int POS;
    /** incremental PID controller */
    public static final int INC;
    byte[] ctx;
    static {
        System.loadLibrary("a");
        OFF = 0;
        POS = 1;
        INC = 3;
        INIT();
    }

    static final native void INIT();

    final native void init(double kp, double ki, double kd, double min, double max, double sum);

    /**
     * construct a new {@link pid} object
     */
    public pid() {
        init(0, 0, 0, -1.0 / 0.0, 1.0 / 0.0, 1.0 / 0.0);
    }

    /**
     * construct a new {@link pid} object
     *
     * @param min minimum output
     * @param max maximum output
     */
    public pid(double min, double max) {
        init(0, 0, 0, min, max, 1.0 / 0.0);
    }

    /**
     * construct a new {@link pid} object
     *
     * @param min minimum output
     * @param max maximum output
     * @param sum maximum intergral output
     */
    public pid(double min, double max, double sum) {
        init(0, 0, 0, min, max, sum);
    }

    /**
     * construct a new {@link pid} object
     *
     * @param kp  proportional constant
     * @param ki  integral constant
     * @param kd  derivative constant
     * @param min minimum output
     * @param max maximum output
     */
    public pid(double kp, double ki, double kd, double min, double max) {
        init(kp, ki, kd, min, max, 0);
    }

    /**
     * construct a new {@link pid} object
     *
     * @param kp  proportional constant
     * @param ki  integral constant
     * @param kd  derivative constant
     * @param min minimum output
     * @param max maximum output
     * @param sum maximum intergral output
     */
    public pid(double kp, double ki, double kd, double min, double max, double sum) {
        init(kp, ki, kd, min, max, sum);
    }

    /**
     * get mode for PID controller
     *
     * @return mode
     */
    public final native int mode();

    /**
     * set mode for PID controller
     *
     * @param mode mode
     * @return {@link pid}
     */
    public final native pid mode(int mode);

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
     * get output cached for PID controller
     *
     * @return output cached
     */
    public final native double out();

    /**
     * get feedback cached for PID controller
     *
     * @return feedback cached
     */
    public final native double fdb();

    /**
     * get error cached for PID controller
     *
     * @return error cached
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
    public final native pid kpid(double kp, double ki, double kd);

    /**
     * calculate function for PID controller
     *
     * @param set setpoint
     * @param fdb feedback
     * @return output
     */
    public final native double iter(double set, double fdb);

    /**
     * zero clear function for PID controller
     *
     * @return {@link pid}
     */
    public final native pid zero();
}
