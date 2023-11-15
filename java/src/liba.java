/**
 * algorithm library
 */
public class liba {
    static {
        System.loadLibrary("a");
    }

    /**
     * algorithm library version string
     *
     * @return version string
     */
    public static final native String version();

    /**
     * algorithm library version major
     *
     * @return major number
     */
    public static final native int version_major();

    /**
     * algorithm library version minor
     *
     * @return minor number
     */
    public static final native int version_minor();

    /**
     * algorithm library version patch
     *
     * @return patch number
     */
    public static final native int version_patch();

    /**
     * algorithm library version tweak
     *
     * @return tweak number
     */
    public static final native long version_tweak();

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
