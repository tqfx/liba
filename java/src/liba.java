/**
 * algorithm library
 */
public class liba {
    /** algorithm library version string */
    public static final String VERSION;
    /** algorithm library version major */
    public static final int VERSION_MAJOR;
    /** algorithm library version minor */
    public static final int VERSION_MINOR;
    /** algorithm library version patch */
    public static final int VERSION_PATCH;
    /** algorithm library version tweak */
    public static final long VERSION_TWEAK;
    static {
        System.loadLibrary("a");
        VERSION_TWEAK = 0;
        VERSION_PATCH = 0;
        VERSION_MINOR = 0;
        VERSION_MAJOR = 0;
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

    /**
     * algorithm library version check
     *
     * @param major major number
     * @param minor minor number
     * @param patch patch number
     * @return -3(&lt;major),-2(&lt;minor),-1(&lt;patch),0,+1(&gt;patch),+2(&gt;minor),+3(&gt;major)
     */
    public static final native int version_check(int major, int minor, int patch);
}
