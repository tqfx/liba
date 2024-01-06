import liba.lpf;

class _lpf {
    public static void main(String[] args) {
        lpf obj = new lpf(10, 0.1);
        obj.gen(10, 0.01).zero();
        System.out.println(obj.iter(1));
        System.out.println(obj.alpha());
        System.out.println(obj.output());
    }
}
