import liba.pid_neuron;

class _pid_neuron {
    public static void main(String[] args) {
        pid_neuron obj = new pid_neuron();
        obj.kpid(10, 1, 0.1, 1).wpid(1, 0, 0).zero();
        System.out.print(obj.inc(1, 0) + " ");
        System.out.println(obj.off(1, 0));
        obj.k(obj.k());
        obj.kp(obj.kp());
        obj.ki(obj.ki());
        obj.kd(obj.kd());
        obj.wp(obj.wp());
        obj.wi(obj.wi());
        obj.wd(obj.wd());
        obj.outmax(obj.outmax());
        obj.outmin(obj.outmin());
        obj.out();
        obj.fdb();
        obj.err();
        obj.ec();
    }
}
