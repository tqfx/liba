import liba.pid;

class _pid {
    public static void main(String[] args) {
        pid obj = new pid();
        obj.kpid(10, 0.1, 1);
        System.out.print(obj.zero().pos(1, 0) + " ");
        System.out.print(obj.zero().inc(1, 0) + " ");
        System.out.println(obj.zero().off(1, 0));
        obj.kp(obj.kp());
        obj.ki(obj.ki());
        obj.kd(obj.kd());
        obj.summax(obj.summax());
        obj.summin(obj.summin());
        obj.outmax(obj.outmax());
        obj.outmin(obj.outmin());
        obj.out();
        obj.fdb();
        obj.err();
    }
}
