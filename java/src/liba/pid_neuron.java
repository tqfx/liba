package liba;

/** single neuron proportional integral derivative controller */
public class pid_neuron {
    static {
        System.loadLibrary("a");
    }
    /** proportional integral derivative controller */
    public pid pid;
    /** error change */
    double ec = 0;
    /** proportional weight */
    double wp = 0;
    /** integral weight */
    double wi = 0;
    /** derivative weight */
    double wd = 0;
    /** proportional output coefficient */
    double k = 0;

    /**
     * construct a new {@link pid_neuron} object
     *
     */
    public pid_neuron() {
        this.pid = new pid();
    }

    /**
     * construct a new {@link pid_neuron} object
     *
     * @param min mininum output
     * @param max maxinum output
     */
    public pid_neuron(double min, double max) {
        this.pid = new pid();
        this.init(min, max, 0);
    }

    /**
     * construct a new {@link pid_neuron} object
     *
     * @param min mininum output
     * @param max maxinum output
     * @param sum maximum intergral output
     */
    public pid_neuron(double min, double max, double sum) {
        this.pid = new pid();
        this.init(min, max, sum);
    }

    /**
     * initialize function for single neuron PID controller
     *
     * @param min minimum output
     * @param max maximum output
     * @param sum maximum intergral output
     * @return {@link pid_neuron}
     */
    public final native pid_neuron init(double min, double max, double sum);

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
     * calculate function for single neuron PID controller
     *
     * @param set setpoint
     * @param fdb feedback
     * @return output
     */
    public final native double iter(double set, double fdb);

    /**
     * zero clear function for single neuron PID controller
     *
     * @return {@link pid_neuron}
     */
    public final native pid_neuron zero();
}
