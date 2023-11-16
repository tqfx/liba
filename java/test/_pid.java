import liba.pid;

class _pid {
    public static void main(String[] args) {
        {
            pid obj = new pid();
            System.out.print(obj.iter(1, 0) + " ");
            obj.kpid(10, 0.1, 1).zero();
            System.out.println(obj.iter(1, 0));
        }
        {
            pid obj = new pid(-10, +10);
            System.out.print(obj.iter(1, 0) + " ");
            obj.kpid(10, 0.1, 1).zero();
            System.out.println(obj.iter(1, 0));
        }
        {
            pid obj = new pid(-10, +10, +10);
            System.out.print(obj.iter(1, 0) + " ");
            obj.kpid(10, 0.1, 1).zero();
            System.out.println(obj.iter(1, 0));
        }
        pid obj = new pid();
        obj.mode(obj.mode());
        obj.kp(obj.kp());
        obj.ki(obj.ki());
        obj.kd(obj.kd());
        obj.summax(obj.summax());
        obj.outmax(obj.outmax());
        obj.outmin(obj.outmin());
        obj.out();
        obj.fdb();
        obj.err();
    }
}
