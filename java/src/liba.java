/**
 * algorithm library
 */
public class liba {
    /** algorithm library version string */
    public static final String VERSION;
    static {
        System.loadLibrary("a");
        VERSION = "";
        INIT();
    }

    static final native void INIT();

    /**
     * reciprocal of square-root
     *
     * @param x independent variable
     * @return calculated result
     */
    public static final native float f32_rsqrt(float x);

    /**
     * reciprocal of square-root
     *
     * @param x independent variable
     * @return calculated result
     */
    public static final native double f64_rsqrt(double x);
}
