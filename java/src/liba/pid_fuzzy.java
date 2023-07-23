package liba;

/** fuzzy proportional integral derivative controller */
public class pid_fuzzy {
    static {
        System.loadLibrary("a");
    }
    /** sqrt(a,b)*sqrt(1-(1-a)*(1-b)) */
    public static final int EQU = 0;
    /** min(a,b) */
    public static final int CAP = 1;
    /** a*b */
    public static final int CAP_ALGEBRA = 2;
    /** max(a+b-1,0) */
    public static final int CAP_BOUNDED = 3;
    /** max(a,b) */
    public static final int CUP = 4;
    /** a+b-a*b */
    public static final int CUP_ALGEBRA = 5;
    /** min(a+b,1) */
    public static final int CUP_BOUNDED = 6;
    /** proportional integral derivative controller */
    public pid pid;
    double[] me;
    double[] mec;
    double[] mkp;
    double[] mki;
    double[] mkd;
    int[] idx;
    double[] val;
    long op = 0;
    /** base proportional constant */
    public double kp = 0;
    /** base integral constant */
    public double ki = 0;
    /** base derivative constant */
    public double kd = 0;
    int col = 0;
    int buf = 0;

    /**
     * construct a new {@link pid_fuzzy} object
     *
     */
    public pid_fuzzy() {
        this.pid = new pid();
        this.op(EQU);
    }

    /**
     * construct a new {@link pid_fuzzy} object
     *
     * @param min mininum output
     * @param max maxinum output
     */
    public pid_fuzzy(double min, double max) {
        this.pid = new pid();
        this.init(min, max, 0);
    }

    /**
     * construct a new {@link pid_fuzzy} object
     *
     * @param min mininum output
     * @param max maxinum output
     * @param sum maximum intergral output
     */
    public pid_fuzzy(double min, double max, double sum) {
        this.pid = new pid();
        this.init(min, max, sum);
    }

    /**
     * initialize function for fuzzy PID controller
     *
     * @param min minimum output
     * @param max maximum output
     * @param sum maximum intergral output
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy init(double min, double max, double sum);

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
