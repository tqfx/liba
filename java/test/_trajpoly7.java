import java.util.Arrays;
import liba.trajpoly7;

class _trajpoly7 {
    public static void main(String[] args) {
        trajpoly7 obj = new trajpoly7(1, 0, 1, 0, 1, 0, 1, 0, 1);
        System.out.println(Arrays.toString(obj.p()));
        System.out.println(Arrays.toString(obj.v()));
        System.out.println(Arrays.toString(obj.a()));
        System.out.println(Arrays.toString(obj.j()));
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5) + "," + obj.jer(0.5));
    }
}
