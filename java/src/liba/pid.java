package liba;

/** proportional integral derivative controller */
public class pid {
    static {
        System.loadLibrary("a");
    }
    /** turn off PID controller */
    public static final int OFF = 0;
    /** positional PID controller */
    public static final int POS = 1;
    /** incremental PID controller */
    public static final int INC = 2;
    /** proportional constant */
    public double kp = 0;
    /** integral constant */
    public double ki = 0;
    /** derivative constant */
    public double kd = 0;
    /** maximum integral output */
    public double summax = 0;
    /** maximum final output */
    public double outmax = 0;
    /** minimum final output */
    public double outmin = 0;
    /** controller output */
    public double out = 0;
    /** cache feedback */
    public double fdb = 0;
    /** cache variable */
    double tmp = 0;
    /** cache error */
    public double err = 0;
    int chan = 0;
    /** controller mode */
    public int mode = OFF;

    /**
     * construct a new {@link pid} object
     */
    public pid() {
    }

    /**
     * construct a new {@link pid} object
     *
     * @param min minimum output
     * @param max maximum output
     */
    public pid(double min, double max) {
        this.init(min, max, 0);
    }

    /**
     * construct a new {@link pid} object
     *
     * @param min minimum output
     * @param max maximum output
     * @param sum maximum intergral output
     */
    public pid(double min, double max, double sum) {
        this.init(min, max, sum);
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
        this.init(min, max, 0).kpid(kp, ki, kd);
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
        this.init(min, max, sum).kpid(kp, ki, kd);
    }

    /**
     * initialize function for PID controller
     *
     * @param min minimum output
     * @param max maximum output
     * @param sum maximum intergral output
     * @return {@link pid}
     */
    public final native pid init(double min, double max, double sum);

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
