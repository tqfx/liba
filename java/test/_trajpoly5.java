import java.util.Arrays;
import liba.trajpoly5;

class _trajpoly5 {
    public static void main(String[] args) {
        trajpoly5 obj = new trajpoly5(1, 0, 1, 0, 1, 0, 1);
        System.out.println(Arrays.toString(obj.c0()));
        System.out.println(Arrays.toString(obj.c1()));
        System.out.println(Arrays.toString(obj.c2()));
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5));
    }
}
