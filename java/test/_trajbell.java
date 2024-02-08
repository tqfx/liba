import liba.trajbell;

class _trajbell {
    public static void main(String[] args) {
        trajbell obj = new trajbell();
        obj.gen(3, 2, 3, 0, 10, 0, 0);
        System.out.println(obj.t());
        System.out.println(obj.tv());
        System.out.println(obj.ta());
        System.out.println(obj.td());
        System.out.println(obj.taj());
        System.out.println(obj.tdj());
        System.out.println(obj.q0());
        System.out.println(obj.q1());
        System.out.println(obj.v0());
        System.out.println(obj.v1());
        System.out.println(obj.vm());
        System.out.println(obj.jm());
        System.out.println(obj.am());
        System.out.println(obj.dm());
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5) + "," + obj.jer(0.5));
    }
}
