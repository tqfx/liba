import liba.mf;
import liba.pid_fuzzy;

class _pid_fuzzy {
    public static void main(String[] args) {
        int NL = -3;
        int NM = -2;
        int NS = -1;
        int ZO = 0;
        int PS = +1;
        int PM = +2;
        int PL = +3;
        double[][] me = {
                { mf.TRI, NL, NL, NM },
                { mf.TRI, NL, NM, NS },
                { mf.TRI, NM, NS, ZO },
                { mf.TRI, NS, ZO, PS },
                { mf.TRI, ZO, PS, PM },
                { mf.TRI, PS, PM, PL },
                { mf.TRI, PM, PL, PL },
        };
        NL = -6;
        NM = -4;
        NS = -2;
        ZO = 0;
        PS = +2;
        PM = +4;
        PL = +6;
        double[][] mec = {
                { mf.TRI, NL, NL, NM },
                { mf.TRI, NL, NM, NS },
                { mf.TRI, NM, NS, ZO },
                { mf.TRI, NS, ZO, PS },
                { mf.TRI, ZO, PS, PM },
                { mf.TRI, PS, PM, PL },
                { mf.TRI, PM, PL, PL },
        };
        NL = -15;
        NM = -10;
        NS = -5;
        ZO = 0;
        PS = +5;
        PM = +10;
        PL = +15;
        double[][] mkp = {
                { NL, NL, NM, NM, NS, ZO, ZO },
                { NL, NL, NM, NS, NS, ZO, PS },
                { NM, NM, NM, NS, ZO, PS, PS },
                { NM, NM, NS, ZO, PS, PM, PM },
                { NS, NS, ZO, PS, PS, PM, PM },
                { NS, ZO, PS, PM, PM, PM, PL },
                { ZO, ZO, PM, PM, PM, PL, PL },
        };
        NL = -3;
        NM = -2;
        NS = -1;
        ZO = 0;
        PS = +1;
        PM = +2;
        PL = +3;
        double[][] mki = {
                { PL, PL, PM, PM, PS, ZO, ZO },
                { PL, PL, PM, PS, PS, ZO, ZO },
                { PL, PM, PS, PS, ZO, NS, NS },
                { PM, PM, PS, ZO, NS, NM, NM },
                { PM, PS, ZO, NS, NS, NM, NL },
                { ZO, ZO, NS, NS, NM, NL, NL },
                { ZO, ZO, NS, NM, NM, NL, NL },
        };
        double[][] mkd = {
                { NS, PS, PL, PL, PL, PM, NS },
                { NS, PS, PL, PM, PM, PS, ZO },
                { ZO, PS, PM, PM, PS, PS, ZO },
                { ZO, PS, PS, PS, PS, PS, ZO },
                { ZO, ZO, ZO, ZO, ZO, ZO, ZO },
                { NL, NS, NS, NS, NS, NS, NL },
                { NL, NM, NM, NM, NS, NS, NL },
        };
        pid_fuzzy obj = new pid_fuzzy();
        obj.rule(me, mec, mkp, mki, mkd).block(2);
        obj.kpid(10, 0.1, 1);
        System.out.print(obj.zero().pos(1, 0) + " ");
        System.out.print(obj.zero().inc(1, 0) + " ");
        System.out.println(obj.run(1, 0));
        obj.kp(obj.kp());
        obj.ki(obj.ki());
        obj.kd(obj.kd());
        obj.summax(obj.summax());
        obj.summin(obj.summin());
        obj.sum();
        obj.outmax(obj.outmax());
        obj.outmin(obj.outmin());
        obj.out();
        obj.fdb();
        obj.err();
        obj.order();
        obj.block(obj.block());
    }
}
