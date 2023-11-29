import java.util.Arrays;
import liba.polytraj3;

class _polytraj3 {
    public static void main(String[] args) {
        polytraj3 obj = new polytraj3(0, 1, 0, 1, 0, 1);
        System.out.println(Arrays.toString(obj.q()));
        System.out.println(Arrays.toString(obj.v()));
        System.out.println(Arrays.toString(obj.a()));
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5));
    }
}
