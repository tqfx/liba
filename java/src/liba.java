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
     * algorithm library version check
     *
     * @param major major number
     * @param minor minor number
     * @param patch patch number
     * @return -3,-2,-1,0,+1,+2,+3
     */
    public static final native int version_check(int major, int minor, int patch);

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
