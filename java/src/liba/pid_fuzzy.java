package liba;

/** fuzzy proportional integral derivative controller */
public class pid_fuzzy {
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
    static {
        System.loadLibrary("a");
    }

    /**
     * construct a new {@link pid_fuzzy} object
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
    public pid_fuzzy(int num, double dt, double[][] me, double[][] mec,
            double[][] mkp, double[][] mki, double[][] mkd, double min, double max) {
        this.pid = new pid(dt, min, max);
        this.init(dt, me, mec, mkp, mki, mkd, min, max).buff(num);
    }

    /**
     * construct a new {@link pid_fuzzy} object
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
    public pid_fuzzy(int num, double dt, double[][] me, double[][] mec,
            double[][] mkp, double[][] mki, double[][] mkd, double min, double max, double sum) {
        this.pid = new pid(dt, min, max, sum);
        this.init(dt, me, mec, mkp, mki, mkd, min, max).buff(num);
    }

    /**
     * turn off fuzzy PID controller
     *
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy off();

    /**
     * incremental fuzzy PID controller
     *
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy inc();

    /**
     * positional fuzzy PID controller
     *
     * @param max maximum intergral output
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy pos(double max);

    /**
     * set register for fuzzy PID controller directly
     *
     * @param mode enumeration for fuzzy PID controller register
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy mode(int mode);

    /**
     * set sampling period for fuzzy PID controller
     *
     * @param dt sampling time unit(s)
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy time(double dt);

    /**
     * set proportional integral derivative constant for fuzzy PID controller
     *
     * @param kp proportional constant
     * @param ki integral constant
     * @param kd derivative constant
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy kpid(double kp, double ki, double kd);

    /**
     * set buffer for fuzzy PID controller
     *
     * @param num maximum number triggered by the rule
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy buff(int num);

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
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy base(double[][] me, double[][] mec, double[][] mkp, double[][] mki, double[][] mkd);

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
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy init(double dt, double[][] me, double[][] mec,
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
     * zero clear function for fuzzy PID controller
     *
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy zero();
}
