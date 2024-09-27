import liba.regress_simple;

class _regress_simple {
    public static void main(String[] args) {
        double x[] = {0, 1, 2, 3, 4};
        double y[] = {1, 2, 3, 4, 5};
        regress_simple obj = new regress_simple(1, 0);
        obj.set_coef(obj.coef());
        obj.set_bias(obj.bias());
        obj.ols_(x, y, 2, 3);
        for (int i = 0; i < x.length; ++i) {
            System.out.format("%g,%g\n", obj.evar(y[i]), obj.eval(x[i]));
        }
        obj.zero();
        obj.olsx(x, y, 2);
        for (int i = 0; i < x.length; ++i) {
            System.out.format("%g,%g\n", obj.evar(y[i]), obj.eval(x[i]));
        }
        obj.zero();
        obj.olsy(x, y, 3);
        for (int i = 0; i < x.length; ++i) {
            System.out.format("%g,%g\n", obj.evar(y[i]), obj.eval(x[i]));
        }
        obj.zero();
        obj.ols(x, y);
        for (int i = 0; i < x.length; ++i) {
            System.out.format("%g,%g\n", obj.evar(y[i]), obj.eval(x[i]));
        }
        obj.zero();
    }
}
