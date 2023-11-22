package liba;

/** single neuron proportional integral derivative controller */
public class pid_neuron {
    byte[] ctx;
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    /**
     * construct a new {@link pid_neuron} object
     *
     */
    public pid_neuron() {
        init();
    }

    final native void init();

    /**
     * get proportional output coefficient for single neuron PID controller
     *
     * @return proportional output coefficient
     */
    public final native double k();

    /**
     * set proportional output coefficient for single neuron PID controller
     *
     * @param k proportional output coefficient
     * @return {@link pid}
     */
    public final native pid k(double k);

    /**
     * get proportional constant for single neuron PID controller
     *
     * @return proportional constant
     */
    public final native double kp();

    /**
     * set proportional constant for single neuron PID controller
     *
     * @param kp proportional constant
     * @return {@link pid}
     */
    public final native pid kp(double kp);

    /**
     * get integral constant for single neuron PID controller
     *
     * @return integral constant
     */
    public final native double ki();

    /**
     * set integral constant for single neuron PID controller
     *
     * @param ki integral constant
     * @return {@link pid}
     */
    public final native pid ki(double ki);

    /**
     * get derivative constant for single neuron PID controller
     *
     * @return derivative constant
     */
    public final native double kd();

    /**
     * set derivative constant for single neuron PID controller
     *
     * @param kd derivative constant
     * @return {@link pid}
     */
    public final native pid kd(double kd);

    /**
     * get proportional weight for single neuron PID controller
     *
     * @return proportional weight
     */
    public final native double wp();

    /**
     * set proportional weight for single neuron PID controller
     *
     * @param wp proportional weight
     * @return {@link pid}
     */
    public final native pid wp(double wp);

    /**
     * get integral weight for single neuron PID controller
     *
     * @return integral weight
     */
    public final native double wi();

    /**
     * set integral weight for single neuron PID controller
     *
     * @param wi integral weight
     * @return {@link pid}
     */
    public final native pid wi(double wi);

    /**
     * get derivative weight for single neuron PID controller
     *
     * @return derivative weight
     */
    public final native double wd();

    /**
     * set derivative weight for single neuron PID controller
     *
     * @param wd derivative weight
     * @return {@link pid}
     */
    public final native pid wd(double wd);

    /**
     * get maximum final output for single neuron PID controller
     *
     * @return maximum final output
     */
    public final native double outmax();

    /**
     * set maximum final output for single neuron PID controller
     *
     * @param max maximum final output
     * @return {@link pid}
     */
    public final native pid outmax(double max);

    /**
     * get minimum final output for single neuron PID controller
     *
     * @return minimum final output
     */
    public final native double outmin();

    /**
     * set minimum final output for single neuron PID controller
     *
     * @param min minimum final output
     * @return {@link pid}
     */
    public final native pid outmin(double min);

    /**
     * get cached output for single neuron PID controller
     *
     * @return cached output
     */
    public final native double out();

    /**
     * get cached feedback for single neuron PID controller
     *
     * @return cached feedback
     */
    public final native double fdb();

    /**
     * get cached error for single neuron PID controller
     *
     * @return cached error
     */
    public final native double err();

    /**
     * get error cached change for single neuron PID controller
     *
     * @return error cached change
     */
    public final native double ec();

    /**
     * set proportional integral derivative constant for single neuron PID
     * controller
     *
     * @param k  proportional output coefficient
     * @param kp proportional learning constant
     * @param ki integral learning constant
     * @param kd derivative learning constant
     * @return {@link pid_neuron}
     */
    public final native pid_neuron kpid(double k, double kp, double ki, double kd);

    /**
     * set proportional integral derivative weight for single neuron PID
     * controller
     *
     * @param wp proportional weight
     * @param wi integral weight
     * @param wd derivative weight
     * @return {@link pid_neuron}
     */
    public final native pid_neuron wpid(double wp, double wi, double wd);

    /**
     * calculate for single neuron PID controller
     *
     * @param set setpoint value
     * @param fdb feedback value
     * @return setpoint value
     */
    public final native double off(double set, double fdb);

    /**
     * calculate for incremental single neuron PID controller
     *
     * @param set setpoint value
     * @param fdb feedback value
     * @return output value
     */
    public final native double inc(double set, double fdb);

    /**
     * zeroing for single neuron PID controller
     *
     * @return {@link pid_neuron}
     */
    public final native pid_neuron zero();
}
