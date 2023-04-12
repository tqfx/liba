import liba.tf;

class _tf {
    public static void main(String[] args) {
        liba.init();
        double num[] = { 6.59492796e-05, 6.54019884e-05 };
        double den[] = { -1.97530991, 0.97530991 };
        tf obj = new tf(num, den);
        System.out.println(obj.proc(1));
        obj.zero();
    }
}
