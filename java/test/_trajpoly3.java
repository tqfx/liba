import java.util.Arrays;
import liba.trajpoly3;

class _trajpoly3 {
    public static void main(String[] args) {
        trajpoly3 obj = new trajpoly3(1, 0, 1, 0, 1);
        System.out.println(Arrays.toString(obj.q()));
        System.out.println(Arrays.toString(obj.v()));
        System.out.println(Arrays.toString(obj.a()));
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5));
    }
}
