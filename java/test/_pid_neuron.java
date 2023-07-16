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
    }
}
