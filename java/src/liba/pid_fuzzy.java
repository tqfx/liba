package liba;

/** fuzzy proportional integral derivative controller */
public class pid_fuzzy {
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
    /** sqrt(a,b)*sqrt(1-(1-a)*(1-b)) */
    public static final int EQU;
    byte[] ctx;
    double[] me;
    double[] mec;
    double[] mkp;
    double[] mki;
    double[] mkd;
    byte[] joint;
    static {
        System.loadLibrary("a");
        CAP = 1;
        CAP_ALGEBRA = 2;
        CAP_BOUNDED = 3;
        CUP = 4;
        CUP_ALGEBRA = 5;
        CUP_BOUNDED = 6;
        EQU = 0;
        INIT();
    }

    static final native void INIT();

    /**
     * construct a new {@link pid_fuzzy} object
     *
     */
    public pid_fuzzy() {
        init(-1.0 / 0.0, 1.0 / 0.0, 1.0 / 0.0);
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

    final native void init(double min, double max, double sum);

    /**
     * get mode for fuzzy PID controller
     *
     * @return mode
     */
    public final native int mode();

    /**
     * set mode for fuzzy PID controller
     *
     * @param mode mode
     * @return {@link pid}
     */
    public final native pid mode(int mode);

    /**
     * get proportional constant for fuzzy PID controller
     *
     * @return proportional constant
     */
    public final native double kp();

    /**
     * set proportional constant for fuzzy PID controller
     *
     * @param kp proportional constant
     * @return {@link pid}
     */
    public final native pid kp(double kp);

    /**
     * get integral constant for fuzzy PID controller
     *
     * @return integral constant
     */
    public final native double ki();

    /**
     * set integral constant for fuzzy PID controller
     *
     * @param ki integral constant
     * @return {@link pid}
     */
    public final native pid ki(double ki);

    /**
     * get derivative constant for fuzzy PID controller
     *
     * @return derivative constant
     */
    public final native double kd();

    /**
     * set derivative constant for fuzzy PID controller
     *
     * @param kd derivative constant
     * @return {@link pid}
     */
    public final native pid kd(double kd);

    /**
     * get maximum integral output for fuzzy PID controller
     *
     * @return maximum integral output
     */
    public final native double summax();

    /**
     * set maximum integral output for fuzzy PID controller
     *
     * @param max maximum integral output
     * @return {@link pid}
     */
    public final native pid summax(double max);

    /**
     * get maximum final output for fuzzy PID controller
     *
     * @return maximum final output
     */
    public final native double outmax();

    /**
     * set maximum final output for fuzzy PID controller
     *
     * @param max maximum final output
     * @return {@link pid}
     */
    public final native pid outmax(double max);

    /**
     * get minimum final output for fuzzy PID controller
     *
     * @return minimum final output
     */
    public final native double outmin();

    /**
     * set minimum final output for fuzzy PID controller
     *
     * @param min minimum final output
     * @return {@link pid}
     */
    public final native pid outmin(double min);

    /**
     * get output cached for fuzzy PID controller
     *
     * @return output cached
     */
    public final native double out();

    /**
     * get feedback cached for fuzzy PID controller
     *
     * @return feedback cached
     */
    public final native double fdb();

    /**
     * get error cached for fuzzy PID controller
     *
     * @return error cached
     */
    public final native double err();

    /**
     * get number of order in the square matrix for fuzzy PID controller
     *
     * @return number of order in the square matrix
     */
    public final native int order();

    /**
     * set fuzzy relational operator for fuzzy PID controller
     *
     * @param op enumeration for fuzzy PID controller operator
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy op(int op);

    /**
     * set rule base for fuzzy PID controller
     *
     * @param me  membership function parameter table, terminated by {@link mf}
     * @param mec membership function parameter table, terminated by {@link mf}
     * @param mkp Kp's rule base table which must be a square matrix
     * @param mki Ki's rule base table which must be a square matrix
     * @param mkd Kd's rule base table which must be a square matrix
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy rule(double[][] me, double[][] mec, double[][] mkp, double[][] mki, double[][] mkd);

    /**
     * get maximum number triggered by the rule for fuzzy PID controller
     *
     * @return maximum number triggered by the rule
     */
    public final native int joint();

    /**
     * set maximum number triggered by the rule for fuzzy PID controller
     *
     * @param num maximum number triggered by the rule
     * @return {@link pid_fuzzy}
     */
    public final native pid_fuzzy joint(int num);

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
