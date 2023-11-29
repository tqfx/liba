import java.util.Arrays;
import liba.polytraj7;

class _polytraj7 {
    public static void main(String[] args) {
        polytraj7 obj = new polytraj7(0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
        System.out.println(Arrays.toString(obj.q()));
        System.out.println(Arrays.toString(obj.v()));
        System.out.println(Arrays.toString(obj.a()));
        System.out.println(Arrays.toString(obj.j()));
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5) + "," + obj.jer(0.5));
    }
}
