import liba.a;
import liba.polytrack5;

public class test_polytrack5 {
    public static void main(String[] args) {
        a.init();
        double[] t = { 0, 1 };
        double[] q = { 0, 1 };
        double[] v = { 0, 1 };
        double[] a = { 0, 1 };
        double[] source = { 0, 0, 0, 0 };
        double[] target = { 1, 1, 1, 1 };
        polytrack5 obj = new polytrack5(0, 1, 0, 1, 0, 1, 0, 1);
        obj.init(t, q, v, a);
        obj.init(source, target);
        double[] out = obj.out(0.5);
        System.out.print(obj.pos(0.5) + "," + obj.vec(0.5) + "," + obj.acc(0.5));
        System.out.println(" " + out[0] + "," + out[1] + "," + out[2]);
    }
}
