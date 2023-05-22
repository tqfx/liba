package liba;

/** transfer function */
public class tf {
    /** numerator */
    public double num[];
    /** denominator */
    public double den[];
    double u[];
    double v[];
    static {
        System.loadLibrary("a");
    }

    /**
     * construct a new {@link tf} object
     *
     * @param num numerator
     * @param den denominator
     */
    public tf(double num[], double den[]) {
        this.init(num, den);
    }

    /**
     * initialize function for transfer function
     *
     * @param num numerator
     * @param den denominator
     * @return {@link tf}
     */
    public final native tf init(double num[], double den[]);

    /**
     * calculate function for transfer function
     *
     * @param x controller output
     * @return feedback
     */
    public final native double iter(double x);

    /**
     * zero function for transfer function
     *
     * @return {@link tf}
     */
    public final native tf zero();
}
