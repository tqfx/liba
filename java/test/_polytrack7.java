import liba.polytrack7;

class _polytrack7 {
    public static void main(String[] args) {
        polytrack7 obj = new polytrack7(0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
        double[] out = obj.out(0.5);
        System.out.print(obj.pos(0.5) + "," + obj.vel(0.5) + "," + obj.acc(0.5) + "," + obj.jer(0.5));
        System.out.println(" " + out[0] + "," + out[1] + "," + out[2] + "," + out[3]);
    }
}
