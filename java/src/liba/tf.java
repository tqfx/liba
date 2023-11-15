package liba;

/** transfer function */
public class tf {
    byte[] ctx;
    double[] num;
    double[] den;
    double[] input;
    double[] output;
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    final native void init(double[] num, double[] den);

    /**
     * construct a new {@link tf} object
     *
     * @param num numerator
     * @param den denominator
     */
    public tf(double[] num, double[] den) {
        init(num, den);
    }

    /**
     * calculate function for transfer function
     *
     * @param x controller output
     * @return feedback
     */
    public final native double iter(double x);

    /**
     * zero clear function for transfer function
     *
     * @return {@link tf}
     */
    public final native tf zero();
}
