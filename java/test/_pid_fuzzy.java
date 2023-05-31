import liba.mf;
import liba.pid;
import liba.pid_fuzzy;

class _pid_fuzzy {
    public static void main(String[] args) {
        int NB = -3;
        int NM = -2;
        int NS = -1;
        int ZO = 0;
        int PS = +1;
        int PM = +2;
        int PB = +3;
        double[][] me = {
                { mf.TRI, NB, NB, NM },
                { mf.TRI, NB, NM, NS },
                { mf.TRI, NM, NS, ZO },
                { mf.TRI, NS, ZO, PS },
                { mf.TRI, ZO, PS, PM },
                { mf.TRI, PS, PM, PB },
                { mf.TRI, PM, PB, PB },
        };
        NB = -6;
        NM = -4;
        NS = -2;
        ZO = 0;
        PS = +2;
        PM = +4;
        PB = +6;
        double[][] mec = {
                { mf.TRI, NB, NB, NM },
                { mf.TRI, NB, NM, NS },
                { mf.TRI, NM, NS, ZO },
                { mf.TRI, NS, ZO, PS },
                { mf.TRI, ZO, PS, PM },
                { mf.TRI, PS, PM, PB },
                { mf.TRI, PM, PB, PB },
        };
        NB = -15;
        NM = -10;
        NS = -5;
        ZO = 0;
        PS = +5;
        PM = +10;
        PB = +15;
        double[][] mkp = {
                { NB, NB, NM, NM, NS, ZO, ZO },
                { NB, NB, NM, NS, NS, ZO, PS },
                { NM, NM, NM, NS, ZO, PS, PS },
                { NM, NM, NS, ZO, PS, PM, PM },
                { NS, NS, ZO, PS, PS, PM, PM },
                { NS, ZO, PS, PM, PM, PM, PB },
                { ZO, ZO, PM, PM, PM, PB, PB },
        };
        NB = -3;
        NM = -2;
        NS = -1;
        ZO = 0;
        PS = +1;
        PM = +2;
        PB = +3;
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
        pid_fuzzy obj = new pid_fuzzy(7, 1, me, mec, mkp, mki, mkd, -10, +10);
        System.out.print(obj.iter(1, 0) + " ");
        obj.off().inc().pos(10).buff(2);
        obj.kpid(10, 0.1, 1);
        obj.mode(pid.INC);
        obj.time(0.1).zero();
        System.out.println(obj.iter(1, 0));
    }
}
