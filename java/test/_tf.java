import java.util.Arrays;
import liba.tf;

class _tf {
    public static void main(String[] args) {
        double num0[] = { 0 };
        double den0[] = { 0 };
        double num[] = { 6.59492796e-05, 6.54019884e-05 };
        double den[] = { -1.97530991, 0.97530991 };
        tf obj = new tf(num0, den0);
        obj.num(num).den(den).zero();
        System.out.println(obj.iter(1));
        System.out.println(obj.iter(1));
        System.out.println(Arrays.toString(obj.num()));
        System.out.println(Arrays.toString(obj.den()));
        System.out.println(Arrays.toString(obj.input()));
        System.out.println(Arrays.toString(obj.output()));
    }
}
