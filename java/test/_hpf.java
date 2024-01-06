import liba.hpf;

class _hpf {
    public static void main(String[] args) {
        hpf obj = new hpf(10, 0.1);
        obj.gen(10, 0.01).zero();
        System.out.println(obj.iter(1));
        System.out.println(obj.alpha());
        System.out.println(obj.output());
        System.out.println(obj.input());
    }
}
