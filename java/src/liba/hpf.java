package liba;

import java.nio.ByteBuffer;

/** High Pass Filter */
public class hpf {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    /**
     * construct a new {@link hpf} object
     *
     * @param fc cut-off frequency unit(hz)
     * @param ts sampling time unit(s)
     */
    public hpf(double fc, double ts) {
        init(fc, ts);
    }

    final native void init(double fc, double ts);

    /**
     * get coefficient for High Pass Filter
     *
     * @return filter coefficient [0,1]
     */
    public final native double alpha();

    /**
     * get output for High Pass Filter
     *
     * @return filter output
     */
    public final native double output();

    /**
     * get input for High Pass Filter
     *
     * @return filter input
     */
    public final native double input();

    /**
     * generate for High Pass Filter
     *
     * @param fc cut-off frequency unit(hz)
     * @param ts sampling time unit(s)
     * @return {@link hpf}
     */
    public final native hpf gen(double fc, double ts);

    /**
     * calculate for High Pass Filter
     *
     * @param x input value
     * @return output value
     */
    public final native double iter(double x);

    /**
     * zeroing for High Pass Filter
     *
     * @return {@link hpf}
     */
    public final native hpf zero();
}
