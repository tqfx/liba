import java.util.Arrays;
import liba.polytraj7;

class _polytraj7 {
    public static void main(String[] args) {
        polytraj7 obj = new polytraj7(0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
        double[] out = obj.out(0.5);
        System.out.println(Arrays.toString(obj.k()));
        System.out.println(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5) + "," + obj.jer(0.5));
        System.out.println(out[0] + "," + out[1] + "," + out[2] + "," + out[3]);
    }
}
