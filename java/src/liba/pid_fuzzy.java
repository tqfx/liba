package liba;

/** fuzzy proportional integral derivative controller */
public class pid_fuzzy {
    /** sqrt(a,b)*sqrt(1-(1-a)*(1-b)) */
    public static final int EQU;
    /** min(a,b) */
    public static final int CAP;
    /** a*b */
    public static final int CAP_ALGEBRA;
    /** max(a+b-1,0) */
    public static final int CAP_BOUNDED;
    /** max(a,b) */
    public static final int CUP;
    /** a+b-a*b */
    public static final int CUP_ALGEBRA;
    /** min(a+b,1) */
    public static final int CUP_BOUNDED;
    byte[] ctx;
    double[] me;
    double[] mec;
    double[] mkp;
    double[] mki;
    double[] mkd;
    double[] val;
    byte[] idx;
    static {
        System.loadLibrary("a");
        EQU = 0;
        CAP = 1;
        CAP_ALGEBRA = 2;
        CAP_BOUNDED = 3;
        CUP = 4;
        CUP_ALGEBRA = 5;
        CUP_BOUNDED = 6;
        INIT();
    }

    static final native void INIT();

    final native void init(double min, double max, double sum);

    /**
     * construct a new {@link pid_fuzzy} object
     *
     */
    public pid_fuzzy() {
        init(-1.0 / 0.0, 1.0 / 0.0, 0);
    }

    /**
     * construct a new {@link pid_fuzzy} object
     *
     * @param min mininum output
     * @param max maxinum output
     */
    public pid_fuzzy(double min, double max) {
        init(min, max, 0);
    }

    /**
     * construct a new {@link pid_fuzzy} object
     *
     * @param min mininum output
     * @param max maxinum output
     * @param sum maximum intergral output
     */
    public pid_fuzzy(double min, double max, double sum) {
        init(min, max, sum);
    }

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
    public final native pid_fuzzy rule(double[][] me, double[][] mec, double[][] mkp, double[][] mki, double[][] mkd);

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
     * set fuzzy relational operator for fuzzy PID controller
     *
     * @param op enumeration for fuzzy PID controller operator
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy op(int op);

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
