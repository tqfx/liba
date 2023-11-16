package liba;

/** membership function */
public class mf {
    /** none */
    public static final int NUL;
    /** gaussian membership function */
    public static final int GAUSS;
    /** generalized bell-shaped membership function */
    public static final int GBELL;
    /** sigmoidal membership function */
    public static final int SIG;
    /** trapezoidal membership function */
    public static final int TRAP;
    /** triangular membership function */
    public static final int TRI;
    /** z-shaped membership function */
    public static final int Z;
    static {
        System.loadLibrary("a");
        NUL = 0;
        GAUSS = 1;
        GBELL = 2;
        SIG = 3;
        TRAP = 4;
        TRI = 5;
        Z = 6;
        INIT();
    }

    static final native void INIT();

    /**
     * gaussian membership function
     *
     * @param x     independent variable
     * @param sigma sigma
     * @param c     c
     * @return membership
     */
    public static final native double gauss(double x, double sigma, double c);

    /**
     * generalized bell-shaped membership function
     *
     * @param x independent variable
     * @param a a
     * @param b b
     * @param c c
     * @return membership
     */
    public static final native double gbell(double x, double a, double b, double c);

    /**
     * sigmoidal membership function
     *
     * @param x independent variable
     * @param a a
     * @param c c
     * @return membership
     */
    public static final native double sig(double x, double a, double c);

    /**
     * trapezoidal membership function
     *
     * @param x independent variable
     * @param a a
     * @param b b
     * @param c c
     * @param d d
     * @return membership
     */
    public static final native double trap(double x, double a, double b, double c, double d);

    /**
     * triangular membership function
     *
     * @param x independent variable
     * @param a a
     * @param b b
     * @param c c
     * @return membership
     */
    public static final native double tri(double x, double a, double b, double c);

    /**
     * z-shaped membership function
     *
     * @param x independent variable
     * @param a a
     * @param b b
     * @return membership
     */
    public static final native double z(double x, double a, double b);
}
