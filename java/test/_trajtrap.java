import liba.trajtrap;

class _trajtrap {
    public static void main(String[] args) {
        trajtrap obj = new trajtrap();
        obj.gen(2, 2, -2, 0, 4, 0, 0);
        System.out.println(obj.t());
        System.out.println(obj.p0());
        System.out.println(obj.p1());
        System.out.println(obj.v0());
        System.out.println(obj.v1());
        System.out.println(obj.vc());
        System.out.println(obj.ta());
        System.out.println(obj.td());
        System.out.println(obj.pa());
        System.out.println(obj.pd());
        System.out.println(obj.ac());
        System.out.println(obj.de());
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5));
    }
}
