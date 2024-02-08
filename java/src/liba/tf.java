package liba;

import java.nio.ByteBuffer;

/** transfer function */
public class tf {
    ByteBuffer ctx;
    ByteBuffer num;
    ByteBuffer den;
    ByteBuffer input;
    ByteBuffer output;
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
    public final native double[] num();

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
    public final native double[] den();

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
    public final native double[] input();

    /**
     * get output for transfer function
     *
     * @return output
     */
    public final native double[] output();

    /**
     * calculate for transfer function
     *
     * @param x controller output
     * @return feedback
     */
    public final native double iter(double x);

    /**
     * zeroing for transfer function
     *
     * @return {@link tf}
     */
    public final native tf zero();
}
