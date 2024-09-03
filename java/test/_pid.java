import liba.pid;

class _pid {
    public static void main(String[] args) {
        pid obj = new pid();
        obj.set_kpid(10, 0.1, 1);
        System.out.print(obj.zero().pos(1, 0) + " ");
        System.out.print(obj.zero().inc(1, 0) + " ");
        System.out.println(obj.zero().run(1, 0));
        obj.set_kp(obj.kp());
        obj.set_ki(obj.ki());
        obj.set_kd(obj.kd());
        obj.set_summax(obj.summax());
        obj.set_summin(obj.summin());
        obj.sum();
        obj.set_outmax(obj.outmax());
        obj.set_outmin(obj.outmin());
        obj.out();
        obj.fdb();
        obj.err();
    }
}
