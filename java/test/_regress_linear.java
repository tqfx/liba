import java.util.Arrays;
import liba.regress_linear;

class _regress_linear {
    public static void main(String[] args) {
        double x[] = { 0, 1, 2, 3, 4 };
        double y[] = { 1, 2, 3, 4, 5 };
        double r[] = { 0, 0, 0, 0, 0 };
        double coef[] = { 0 };
        regress_linear obj = new regress_linear(coef, 0);
        obj.set_coef(obj.coef());
        obj.set_bias(obj.bias());
        obj.gd(coef, 0, 0);

        obj.zero();
        for (int i = 0; i < 100; ++i) {
            obj.sgd(x, y, 0.1);
        }
        for (int i = 0; i < r.length; i++) {
            double[] val = { x[i] };
            r[i] = obj.eval(val);
        }
        System.out.println(Arrays.toString(r));
        System.out.println(Arrays.toString(obj.err(x, y)));

        obj.zero();
        for (int i = 0; i < 100; ++i) {
            obj.bgd(x, y, 0.1);
        }
        for (int i = 0; i < r.length; i++) {
            double[] val = { x[i] };
            r[i] = obj.eval(val);
        }
        System.out.println(Arrays.toString(r));
        System.out.println(Arrays.toString(obj.err(x, y)));

        obj.zero();
        obj.mgd(x, y, 0.001, 0.2, 0.1, 100, 100, 10);
        for (int i = 0; i < r.length; i++) {
            double[] val = { x[i] };
            r[i] = obj.eval(val);
        }
        System.out.println(Arrays.toString(r));
        System.out.println(Arrays.toString(obj.err(x, y)));
    }
}
