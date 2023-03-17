import liba.a;

public class test_a {
    public static void main(String[] args) {
        a.init();
        System.out.println("version " + a.version());
        System.out.println("major " + a.version_major());
        System.out.println("minor " + a.version_minor());
        System.out.println("patch " + a.version_patch());
    }
}
