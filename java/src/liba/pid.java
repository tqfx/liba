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
        init(0, 0, 0, -1.0 / 0.0, 1.0 / 0.0, 0);
    }

    /**
     * construct a new {@link pid} object
     *
     * @param min minimum output
     * @param max maximum output
     */
    public pid(double min, double max) {
        init(0, 0, 0, min, max, 0);
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
