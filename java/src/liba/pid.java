package liba;

/** proportional integral derivative controller */
public class pid {
    /** turn off PID controller */
    public static final int OFF = 0;
    /** positional PID controller */
    public static final int POS = 1;
    /** incremental PID controller */
    public static final int INC = 2;
    /** sampling time unit(s) */
    public double dt;
    /** proportional constant */
    public double kp;
    /** integral constant */
    public double ki;
    /** derivative constant */
    public double kd;
    /** minimum final output */
    public double outmin;
    /** maximum integral output */
    public double outmax;
    /** maximum integral output */
    public double summax;
    /** (integral) output item sum */
    public double sum;
    /** controller output */
    public double out;
    /** cache feedback */
    public double fdb;
    /** error change */
    public double ec;
    /** error input */
    public double e;
    int num;
    int reg;

    /**
     * construct a new {@link pid} object
     *
     * @param dt  sampling time unit(s)
     * @param min minimum output
     * @param max maximum output
     */
    public pid(double dt, double min, double max) {
        this.init(dt, min, max).inc();
    }

    /**
     * construct a new {@link pid} object
     *
     * @param dt  sampling time unit(s)
     * @param min minimum output
     * @param max maximum output
     * @param sum maximum intergral output
     */
    public pid(double dt, double min, double max, double sum) {
        this.init(dt, min, max).pos(sum);
    }

    /**
     * construct a new {@link pid} object
     *
     * @param dt  sampling time unit(s)
     * @param kp  proportional constant
     * @param ki  integral constant
     * @param kd  derivative constant
     * @param min minimum output
     * @param max maximum output
     */
    public pid(double dt, double kp, double ki, double kd, double min, double max) {
        this.init(dt, min, max).kpid(kp, ki, kd).inc();
    }

    /**
     * construct a new {@link pid} object
     *
     * @param dt  sampling time unit(s)
     * @param kp  proportional constant
     * @param ki  integral constant
     * @param kd  derivative constant
     * @param min minimum output
     * @param max maximum output
     * @param sum maximum intergral output
     */
    public pid(double dt, double kp, double ki, double kd, double min, double max, double sum) {
        this.init(dt, min, max).kpid(kp, ki, kd).pos(sum);
    }

    /**
     * turn off PID controller
     *
     * @return {@link pid}
     */
    public final native pid off();

    /**
     * incremental PID controller
     *
     * @return {@link pid}
     */
    public final native pid inc();

    /**
     * positional PID controller
     *
     * @param max maximum intergral output
     * @return {@link pid}
     */
    public final native pid pos(double max);

    /**
     * set register for PID controller directly
     *
     * @param mode enumeration for PID controller register
     * @return {@link pid}
     */
    public final native pid mode(int mode);

    /**
     * set sampling period for PID controller
     *
     * @param dt sampling time unit(s)
     * @return {@link pid}
     */
    public final native pid time(double dt);

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
     * initialize function for PID controller
     *
     * @param dt  sampling time unit(s)
     * @param min minimum output
     * @param max maximum output
     * @return {@link pid}
     */
    public final native pid init(double dt, double min, double max);

    /**
     * process function for PID controller
     *
     * @param set setpoint
     * @param fdb feedback
     * @return output
     */
    public final native double proc(double set, double fdb);

    /**
     * zero function for PID controller
     *
     * @return {@link pid}
     */
    public final native pid zero();
}
