import liba.polytrack5;

class _polytrack5 {
    public static void main(String[] args) {
        polytrack5 obj = new polytrack5(0, 1, 0, 1, 0, 1, 0, 1);
        double[] out = obj.out(0.5);
        System.out.print(obj.pos(0.5) + "," + obj.vec(0.5) + "," + obj.acc(0.5));
        System.out.println(" " + out[0] + "," + out[1] + "," + out[2]);
    }
}
