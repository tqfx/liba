/**
 * algorithm library
 */
public class liba {
    /** algorithm library version string */
    public static final String VERSION;
    static {
        System.loadLibrary("a");
        VERSION = "0.0.0";
        INIT();
    }

    static final native void INIT();

    /**
     * square root of an unsigned integer
     *
     * @param x independent variable
     * @return calculated result
     */
    public static final native int isqrt(int x);

    /**
     * square root of an unsigned integer
     *
     * @param x independent variable
     * @return calculated result
     */
    public static final native int isqrt(long x);

    /**
     * reciprocal of square-root
     *
     * @param x independent variable
     * @return calculated result
     */
    public static final native float rsqrt(float x);

    /**
     * reciprocal of square-root
     *
     * @param x independent variable
     * @return calculated result
     */
    public static final native double rsqrt(double x);
}
