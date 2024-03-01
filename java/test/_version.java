import liba.version;

class _version {
    public static void main(String[] args) {
        System.out.println(version.check(0, 0, 0));
        System.out.println("major " + version.MAJOR);
        System.out.println("minor " + version.MINOR);
        System.out.println("patch " + version.PATCH);
        System.out.println("tweak " + version.TWEAK);
        version v000 = new version();
        version v100 = new version(1);
        version v010 = new version(0, 1);
        version v001 = new version(0, 0, 1);
        System.out.println(v000);
        System.out.println(v100);
        System.out.println(v010);
        System.out.println(v001);
        if (!v000.lt(v001)) {
            throw new RuntimeException("v000.lt(v001)");
        }
        if (!v001.gt(v000)) {
            throw new RuntimeException("v001.gt(v000)");
        }
        if (!v100.le(v100)) {
            throw new RuntimeException("v100.le(v100)");
        }
        if (!v100.ge(v100)) {
            throw new RuntimeException("v100.ge(v100)");
        }
        if (!v010.eq(v010)) {
            throw new RuntimeException("v010.eq(v010)");
        }
        if (!v010.ne(v001)) {
            throw new RuntimeException("v010.ne(v001)");
        }
        if (v100.cmp(v001.parse("0.0.1")) != 3) {
            throw new RuntimeException("v100.cmp(v001) == 3");
        }
        v000.major(1).minor(2).third(3).extra(4);
        if (v000.major() != 1) {
            throw new RuntimeException("v000.major() != 1");
        }
        if (v000.minor() != 2) {
            throw new RuntimeException("v000.minor() != 2");
        }
        if (v000.third() != 3) {
            throw new RuntimeException("v000.third() != 3");
        }
        if (v000.extra() != 4) {
            throw new RuntimeException("v000.extra() != 4");
        }
        v000.alpha(v000.alpha());
        System.out.println(v000);
    }
}
