import java.util.Arrays;
import liba.polytraj5;

class _polytraj5 {
    public static void main(String[] args) {
        polytraj5 obj = new polytraj5(0, 1, 0, 1, 0, 1, 0, 1);
        System.out.println(Arrays.toString(obj.q()));
        System.out.println(Arrays.toString(obj.v()));
        System.out.println(Arrays.toString(obj.a()));
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5));
    }
}
