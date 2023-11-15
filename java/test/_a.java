import java.io.*;

class _a {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length > 0) {
            System.setOut(new PrintStream(new FileOutputStream(args[0])));
        }
        System.out.println(liba.version_check(0, 0, 0));
        System.out.println("version " + liba.VERSION);
        System.out.println("major " + liba.VERSION_MAJOR);
        System.out.println("minor " + liba.VERSION_MINOR);
        System.out.println("patch " + liba.VERSION_PATCH);
        System.out.println("tweak " + liba.VERSION_TWEAK);
    }
}
