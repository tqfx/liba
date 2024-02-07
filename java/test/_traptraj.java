import liba.traptraj;

class _traptraj {
    public static void main(String[] args) {
        traptraj obj = new traptraj(2, 2, -2, 0, 4, 0, 0);
        System.out.println(obj.t());
        System.out.println(obj.q0());
        System.out.println(obj.q1());
        System.out.println(obj.v0());
        System.out.println(obj.v1());
        System.out.println(obj.vc());
        System.out.println(obj.ta());
        System.out.println(obj.td());
        System.out.println(obj.qa());
        System.out.println(obj.qd());
        System.out.println(obj.ac());
        System.out.println(obj.de());
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5));
    }
}
