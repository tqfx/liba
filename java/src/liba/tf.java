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
     * get numerator for transfer function
     *
     * @return numerator
     */
    public final double[] num() {
        return num;
    }

    /**
     * set numerator for transfer function
     *
     * @param num numerator
     * @return {@link tf}
     */
    public final native tf num(double[] num);

    /**
     * get denominator for transfer function
     *
     * @return denominator
     */
    public final double[] den() {
        return den;
    }

    /**
     * set denominator for transfer function
     *
     * @param den denominator
     * @return {@link tf}
     */
    public final native tf den(double[] den);

    /**
     * get input for transfer function
     *
     * @return input
     */
    public final double[] input() {
        return input;
    }

    /**
     * get output for transfer function
     *
     * @return output
     */
    public final double[] output() {
        return output;
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
