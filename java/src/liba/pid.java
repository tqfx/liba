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
    public double kp;
    /** integral constant */
    public double ki;
    /** derivative constant */
    public double kd;
    /** maximum integral output */
    public double summax;
    /** maximum final output */
    public double outmax;
    /** minimum final output */
    public double outmin;
    /** controller output */
    public double out;
    /** cache feedback */
    public double fdb;
    /** cache variable */
    double tmp;
    /** cache error */
    public double err;
    int chan;
    /** controller mode */
    public int mode;

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
