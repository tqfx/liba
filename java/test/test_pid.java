import liba.a;
import liba.pid;

public class test_pid {
    public static void main(String[] args) {
        a.init();
        pid obj = new pid(1, -10, +10);
        System.out.print(obj.proc(1, 0) + " ");
        obj.off().inc().pos(10);
        obj.kpid(10, 0.1, 1);
        obj.mode(pid.INC);
        obj.time(0.1).zero();
        System.out.println(obj.proc(1, 0));
    }
}
