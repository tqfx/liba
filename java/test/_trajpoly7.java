import java.util.Arrays;
import liba.trajpoly7;

class _trajpoly7 {
    public static void main(String[] args) {
        trajpoly7 obj = new trajpoly7(1, 0, 1, 0, 1, 0, 1, 0, 1);
        System.out.println(Arrays.toString(obj.c0()));
        System.out.println(Arrays.toString(obj.c1()));
        System.out.println(Arrays.toString(obj.c2()));
        System.out.println(Arrays.toString(obj.c3()));
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5) + "," + obj.jer(0.5));
    }
}
