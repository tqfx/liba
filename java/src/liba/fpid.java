package liba;

/** fuzzy proportional integral derivative controller */
public class fpid {
    /** proportional integral derivative controller */
    public pid pid;
    double[] me;
    double[] mec;
    double[] mkp;
    double[] mki;
    double[] mkd;
    int[] idx;
    double[] val;
    /** base proportional constant */
    public double kp;
    /** base integral constant */
    public double ki;
    /** base derivative constant */
    public double kd;
    long op;

    /**
     * construct a new {@link fpid} object
     *
     * @param num maximum number triggered by the rule
     * @param dt  sampling time unit(s)
     * @param me  points to membership function parameter table, terminated by
     *            {@link mf}
     * @param mec points to membership function parameter table, terminated by
     *            {@link mf}
     * @param mkp points to Kp's rule base table, the rule base must be square
     * @param mki points to Ki's rule base table, the rule base must be square
     * @param mkd points to Kd's rule base table, the rule base must be square
     * @param min mininum output
     * @param max maxinum output
     */
    public fpid(int num, double dt, double[][] me, double[][] mec,
            double[][] mkp, double[][] mki, double[][] mkd, double min, double max) {
        this.pid = new pid(dt, min, max);
        this.init(dt, me, mec, mkp, mki, mkd, min, max).buff(num);
    }

    /**
     * construct a new {@link fpid} object
     *
     * @param num maximum number triggered by the rule
     * @param dt  sampling time unit(s)
     * @param me  points to membership function parameter table, terminated by
     *            {@link mf}
     * @param mec points to membership function parameter table, terminated by
     *            {@link mf}
     * @param mkp points to Kp's rule base table, the rule base must be square
     * @param mki points to Ki's rule base table, the rule base must be square
     * @param mkd points to Kd's rule base table, the rule base must be square
     * @param min mininum output
     * @param max maxinum output
     * @param sum maximum intergral output
     */
    public fpid(int num, double dt, double[][] me, double[][] mec,
            double[][] mkp, double[][] mki, double[][] mkd, double min, double max, double sum) {
        this.pid = new pid(dt, min, max, sum);
        this.init(dt, me, mec, mkp, mki, mkd, min, max).buff(num);
    }

    /**
     * turn off fuzzy PID controller
     *
     * @return {@link fpid}
     */
    public final native fpid off();

    /**
     * incremental fuzzy PID controller
     *
     * @return {@link fpid}
     */
    public final native fpid inc();

    /**
     * positional fuzzy PID controller
     *
     * @param max maximum intergral output
     * @return {@link fpid}
     */
    public final native fpid pos(double max);

    /**
     * set register for fuzzy PID controller directly
     *
     * @param mode enumeration for fuzzy PID controller register
     * @return {@link fpid}
     */
    public final native fpid mode(int mode);

    /**
     * set sampling period for fuzzy PID controller
     *
     * @param dt sampling time unit(s)
     * @return {@link fpid}
     */
    public final native fpid time(double dt);

    /**
     * set proportional integral derivative constant for fuzzy PID controller
     *
     * @param kp proportional constant
     * @param ki integral constant
     * @param kd derivative constant
     * @return {@link fpid}
     */
    public final native fpid kpid(double kp, double ki, double kd);

    /**
     * set buffer for fuzzy PID controller
     *
     * @param num maximum number triggered by the rule
     * @return {@link fpid}
     */
    public final native fpid buff(int num);

    /**
     * set rule base for fuzzy PID controller
     *
     * @param me  points to membership function parameter table, terminated by
     *            {@link mf}
     * @param mec points to membership function parameter table, terminated by
     *            {@link mf}
     * @param mkp points to Kp's rule base table, the rule base must be square
     * @param mki points to Ki's rule base table, the rule base must be square
     * @param mkd points to Kd's rule base table, the rule base must be square
     * @return {@link fpid}
     */
    public final native fpid base(double[][] me, double[][] mec, double[][] mkp, double[][] mki, double[][] mkd);

    /**
     * initialize function for fuzzy PID controller
     *
     * @param dt  sampling time unit(s)
     * @param me  points to membership function parameter table, terminated by
     *            {@link mf}
     * @param mec points to membership function parameter table, terminated by
     *            {@link mf}
     * @param mkp points to Kp's rule base table, the rule base must be square
     * @param mki points to Ki's rule base table, the rule base must be square
     * @param mkd points to Kd's rule base table, the rule base must be square
     * @param min mininum output
     * @param max maxinum output
     * @return {@link fpid}
     */
    public final native fpid init(double dt, double[][] me, double[][] mec,
            double[][] mkp, double[][] mki, double[][] mkd, double min, double max);

    /**
     * calculate function for fuzzy PID controller
     *
     * @param set setpoint
     * @param fdb feedback
     * @return output
     */
    public final native double iter(double set, double fdb);

    /**
     * zero function for fuzzy PID controller
     *
     * @return {@link fpid}
     */
    public final native fpid zero();
}
