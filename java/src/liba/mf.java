package liba;

/** membership function */
public final class mf {
    /** none */
    public static final int NUL = 0;
    /** gaussian membership function */
    public static final int GAUSS = 1;
    /** generalized bell-shaped membership function */
    public static final int GBELL = 2;
    /** sigmoidal membership function */
    public static final int SIG = 3;
    /** trapezoidal membership function */
    public static final int TRAP = 4;
    /** triangular membership function */
    public static final int TRI = 5;
    /** z-shaped membership function */
    public static final int Z = 6;

    /**
     * gaussian membership function
     *
     * @param x     any element
     * @param sigma sigma
     * @param c     c
     * @return membership
     */
    public static final native double gauss(double x, double sigma, double c);

    /**
     * generalized bell-shaped membership function
     *
     * @param x any element
     * @param a a
     * @param b b
     * @param c c
     * @return membership
     */
    public static final native double gbell(double x, double a, double b, double c);

    /**
     * sigmoidal membership function
     *
     * @param x any element
     * @param a a
     * @param c c
     * @return membership
     */
    public static final native double sig(double x, double a, double c);

    /**
     * trapezoidal membership function
     *
     * @param x any element
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
     * @param x any element
     * @param a a
     * @param b b
     * @param c c
     * @return membership
     */
    public static final native double tri(double x, double a, double b, double c);

    /**
     * z-shaped membership function
     *
     * @param x any element
     * @param a a
     * @param b b
     * @return membership
     */
    public static final native double z(double x, double a, double b);
}
