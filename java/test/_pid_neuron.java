import liba.pid_neuron;

class _pid_neuron {
    public static void main(String[] args) {
        {
            pid_neuron obj = new pid_neuron();
            System.out.print(obj.iter(1, 0) + " ");
            obj.kpid(10, 1, 0.1, 1).wpid(1, 0, 0).zero();
            System.out.println(obj.iter(1, 0));
        }
        {
            pid_neuron obj = new pid_neuron(-10, +10);
            System.out.print(obj.iter(1, 0) + " ");
            obj.kpid(10, 1, 0.1, 1).wpid(1, 0, 0).zero();
            System.out.println(obj.iter(1, 0));
        }
        pid_neuron obj = new pid_neuron();
        obj.mode(obj.mode());
        obj.k(obj.k());
        obj.kp(obj.kp());
        obj.ki(obj.ki());
        obj.kd(obj.kd());
        obj.wp(obj.wp());
        obj.wi(obj.wi());
        obj.wd(obj.wd());
        obj.summax(obj.summax());
        obj.outmax(obj.outmax());
        obj.outmin(obj.outmin());
        obj.out();
        obj.fdb();
        obj.err();
        obj.ec();
    }
}
