package liba;

/** fuzzy proportional integral derivative controller */
public final class fpid {
    /** proportional integral derivative controller */
    public pid pid;
    double[] mmp;
    double[] mkp;
    double[] mki;
    double[] mkd;
    double[] mat;
    double[] mms;
    int[] idx;
    double sigma;
    double alpha;
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
     * @param num  maximum number triggered by the rule
     * @param dt   sampling time unit(s)
     * @param mmp  points to membership function parameter table, an array
     *             terminated
     *             by {@link mf}
     * @param mkp  points to Kp's rule base table, the rule base must be square
     * @param mki  points to Ki's rule base table, the rule base must be square
     * @param mkd  points to Kd's rule base table, the rule base must be square
     * @param imin mininum input
     * @param imax maxinum input
     * @param omin mininum output
     * @param omax maxinum output
     */
    public fpid(int num, double dt, double[][] mmp,
            double[][] mkp, double[][] mki, double[][] mkd,
            double imin, double imax, double omin, double omax) {
        this.pid = new pid(dt, omin, omax);
        this.init(dt, mmp, mkp, mki, mkd, imin, imax, omin, omax).buff(num);
    }

    /**
     * construct a new {@link fpid} object
     *
     * @param num  maximum number triggered by the rule
     * @param dt   sampling time unit(s)
     * @param mmp  points to membership function parameter table, an array
     *             terminated
     *             by {@link mf}
     * @param mkp  points to Kp's rule base table, the rule base must be square
     * @param mki  points to Ki's rule base table, the rule base must be square
     * @param mkd  points to Kd's rule base table, the rule base must be square
     * @param imin mininum input
     * @param imax maxinum input
     * @param omin mininum output
     * @param omax maxinum output
     * @param sum  maximum intergral output
     */
    public fpid(int num, double dt, double[][] mmp,
            double[][] mkp, double[][] mki, double[][] mkd,
            double imin, double imax, double omin, double omax, double sum) {
        this.pid = new pid(dt, omin, omax, sum);
        this.init(dt, mmp, mkp, mki, mkd, imin, imax, omin, omax).buff(num);
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
     * set input extreme value for fuzzy PID controller
     *
     * @param min mininum input
     * @param max maxinum input
     * @return {@link fpid}
     */
    public final native fpid ilim(double min, double max);

    /**
     * set output extreme value for fuzzy PID controller
     *
     * @param min mininum output
     * @param max maxinum output
     * @return {@link fpid}
     */
    public final native fpid olim(double min, double max);

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
     * @param mmp points to membership function parameter table, an array terminated
     *            by {@link mf}
     * @param mkp points to Kp's rule base table, the rule base must be square
     * @param mki points to Ki's rule base table, the rule base must be square
     * @param mkd points to Kd's rule base table, the rule base must be square
     * @return {@link fpid}
     */
    public final native fpid base(double[][] mmp, double[][] mkp, double[][] mki, double[][] mkd);

    /**
     * initialize function for fuzzy PID controller
     *
     * @param dt   sampling time unit(s)
     * @param mmp  points to membership function parameter table, an array
     *             terminated
     *             by {@link mf}
     * @param mkp  points to Kp's rule base table, the rule base must be square
     * @param mki  points to Ki's rule base table, the rule base must be square
     * @param mkd  points to Kd's rule base table, the rule base must be square
     * @param imin mininum input
     * @param imax maxinum input
     * @param omin mininum output
     * @param omax maxinum output
     * @return {@link fpid}
     */
    public final native fpid init(double dt, double[][] mmp,
            double[][] mkp, double[][] mki, double[][] mkd,
            double imin, double imax, double omin, double omax);

    /**
     * process function for fuzzy PID controller
     *
     * @param set setpoint
     * @param fdb feedback
     * @return output
     */
    public final native double proc(double set, double fdb);

    /**
     * zero function for fuzzy PID controller
     *
     * @return {@link fpid}
     */
    public final native fpid zero();
}
