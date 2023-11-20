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
     * fast inverse square-root
     *
     * @param x independent variable
     * @return calculated result
     */
    public static final native float f32_rsqrt(float x);

    /**
     * fast inverse square-root
     *
     * @param x independent variable
     * @return calculated result
     */
    public static final native double f64_rsqrt(double x);
}
