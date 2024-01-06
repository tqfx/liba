package liba;

/** Low Pass Filter */
public class lpf {
    byte[] ctx;
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    /**
     * construct a new {@link lpf} object
     *
     * @param fc cut-off frequency unit(hz)
     * @param ts sampling time unit(s)
     */
    public lpf(double fc, double ts) {
        init(fc, ts);
    }

    final native void init(double fc, double ts);

    /**
     * get coefficient for Low Pass Filter
     *
     * @return filter coefficient [0,1]
     */
    public final native double alpha();

    /**
     * get output for Low Pass Filter
     *
     * @return filter output
     */
    public final native double output();

    /**
     * generate for Low Pass Filter
     *
     * @param fc cut-off frequency unit(hz)
     * @param ts sampling time unit(s)
     * @return {@link lpf}
     */
    public final native lpf gen(double fc, double ts);

    /**
     * calculate for Low Pass Filter
     *
     * @param x input value
     * @return output value
     */
    public final native double iter(double x);

    /**
     * zeroing for Low Pass Filter
     *
     * @return {@link lpf}
     */
    public final native lpf zero();
}
