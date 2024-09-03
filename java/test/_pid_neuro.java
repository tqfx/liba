import liba.pid_neuro;

class _pid_neuro {
    public static void main(String[] args) {
        pid_neuro obj = new pid_neuro();
        obj.set_kpid(10, 1, 0.1, 1).set_wpid(1, 0, 0).zero();
        System.out.print(obj.inc(1, 0) + " ");
        System.out.println(obj.run(1, 0));
        obj.set_k(obj.k());
        obj.set_kp(obj.kp());
        obj.set_ki(obj.ki());
        obj.set_kd(obj.kd());
        obj.set_wp(obj.wp());
        obj.set_wi(obj.wi());
        obj.set_wd(obj.wd());
        obj.set_outmax(obj.outmax());
        obj.set_outmin(obj.outmin());
        obj.out();
        obj.fdb();
        obj.err();
        obj.ec();
    }
}
