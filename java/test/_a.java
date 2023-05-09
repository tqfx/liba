import java.io.*;

class _a {
    public static void main(String[] args) throws FileNotFoundException {
        liba.init();
        if (args.length > 0) {
            System.setOut(new PrintStream(new FileOutputStream(args[0])));
        }
        System.out.println("version " + liba.version());
        System.out.println("major " + liba.version_major());
        System.out.println("minor " + liba.version_minor());
        System.out.println("patch " + liba.version_patch());
    }
}
