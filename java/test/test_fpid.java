import liba.a;
import liba.mf;
import liba.pid;
import liba.fpid;

public class test_fpid {
    public static void main(String[] args) {
        a.init();
        final int NB = -3;
        final int NM = -2;
        final int NS = -1;
        final int ZO = 0;
        final int PS = +1;
        final int PM = +2;
        final int PB = +3;
        double[][] mmp = {
                { mf.TRI, NB, NB, NM },
                { mf.TRI, NB, NM, NS },
                { mf.TRI, NM, NS, ZO },
                { mf.TRI, NS, ZO, PS },
                { mf.TRI, ZO, PS, PM },
                { mf.TRI, PS, PM, PB },
                { mf.TRI, PM, PB, PB },
                { mf.NUL },
        };
        double[][] mkp = {
                { NB, NB, NM, NM, NS, ZO, ZO },
                { NB, NB, NM, NS, NS, ZO, PS },
                { NM, NM, NM, NS, ZO, PS, PS },
                { NM, NM, NS, ZO, PS, PM, PM },
                { NS, NS, ZO, PS, PS, PM, PM },
                { NS, ZO, PS, PM, PM, PM, PB },
                { ZO, ZO, PM, PM, PM, PB, PB },
        };
        double[][] mki = {
                { PB, PB, PM, PM, PS, ZO, ZO },
                { PB, PB, PM, PS, PS, ZO, ZO },
                { PB, PM, PS, PS, ZO, NS, NS },
                { PM, PM, PS, ZO, NS, NM, NM },
                { PM, PS, ZO, NS, NS, NM, NB },
                { ZO, ZO, NS, NS, NM, NB, NB },
                { ZO, ZO, NS, NM, NM, NB, NB },
        };
        double[][] mkd = {
                { NS, PS, PB, PB, PB, PM, NS },
                { NS, PS, PB, PM, PM, PS, ZO },
                { ZO, PS, PM, PM, PS, PS, ZO },
                { ZO, PS, PS, PS, PS, PS, ZO },
                { ZO, ZO, ZO, ZO, ZO, ZO, ZO },
                { NB, NS, NS, NS, NS, NS, NB },
                { NB, NM, NM, NM, NS, NS, NB },
        };
        fpid obj = new fpid(0, 1, mmp, mkp, mki, mkd, -3, 3, -10, +10);
        System.out.print(obj.proc(1, 0) + " ");
        obj.off().inc().pos(10).buff(2);
        obj.kpid(10, 0.1, 1);
        obj.mode(pid.INC);
        obj.time(0.1).zero();
        System.out.println(obj.proc(1, 0));
    }
}
