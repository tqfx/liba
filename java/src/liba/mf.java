package liba;

/** membership function */
public class mf {
    /** none */
    public static final int NUL;
    /** gaussian membership function */
    public static final int GAUSS;
    /** gaussian combination membership function */
    public static final int GAUSS2;
    /** generalized bell-shaped membership function */
    public static final int GBELL;
    /** sigmoidal membership function */
    public static final int SIG;
    /** difference between two sigmoidal membership functions */
    public static final int DSIG;
    /** product of two sigmoidal membership functions */
    public static final int PSIG;
    /** trapezoidal membership function */
    public static final int TRAP;
    /** triangular membership function */
    public static final int TRI;
    /** linear s-shaped saturation membership function */
    public static final int LINS;
    /** linear z-shaped saturation membership function */
    public static final int LINZ;
    /** s-shaped membership function */
    public static final int S;
    /** z-shaped membership function */
    public static final int Z;
    /** pi-shaped membership function */
    public static final int PI;
    static {
        System.loadLibrary("a");
        NUL = 0;
        GAUSS = 1;
        GAUSS2 = 2;
        GBELL = 3;
        SIG = 4;
        DSIG = 5;
        PSIG = 6;
        TRAP = 7;
        TRI = 8;
        LINS = 9;
        LINZ = 10;
        S = 11;
        Z = 12;
        PI = 13;
        INIT();
    }

    static final native void INIT();

    /**
     * gaussian membership function
     *
     * @param x     input value for which to compute membership value.
     * @param sigma is the standard deviation.
     * @param c     is the mean.
     * @return membership value.
     */
    public static final native double gauss(double x, double sigma, double c);

    /**
     * gaussian combination membership function
     *
     * @param x      input value for which to compute membership value.
     * @param sigma1 is the standard deviation of the left gaussian function.
     * @param c1     is the mean of the left gaussian function.
     * @param sigma2 is the standard deviation of the right gaussian function.
     * @param c2     is the mean of the right gaussian function.
     * @return membership value.
     */
    public static final native double gauss2(double x, double sigma1, double c1, double sigma2, double c2);

    /**
     * generalized bell-shaped membership function
     *
     * @param x input value for which to compute membership value.
     * @param a defines the width of the membership function, where a larger value
     *          creates a wider membership function.
     * @param b defines the shape of the curve on either side of the central
     *          plateau, where a larger value creates a more steep transition.
     * @param c defines the center of the membership function.
     * @return membership value.
     */
    public static final native double gbell(double x, double a, double b, double c);

    /**
     * sigmoidal membership function
     *
     * @param x input value for which to compute membership value.
     * @param a defines the width of the transition area.
     * @param c defines the center of the transition area.
     * @return membership value.
     */
    public static final native double sig(double x, double a, double c);

    /**
     * difference between two sigmoidal membership functions
     *
     * @param x  input value for which to compute membership value.
     * @param a1 defines the width of the first transition area.
     * @param c1 defines the center of the first transition area.
     * @param a2 defines the width of the second transition area.
     * @param c2 defines the center of the second transition area.
     * @return membership value.
     */
    public static final native double dsig(double x, double a1, double c1, double a2, double c2);

    /**
     * product of two sigmoidal membership functions
     *
     * @param x  input value for which to compute membership value.
     * @param a1 defines the width of the first transition area.
     * @param c1 defines the center of the first transition area.
     * @param a2 defines the width of the second transition area.
     * @param c2 defines the center of the second transition area.
     * @return membership value.
     */
    public static final native double psig(double x, double a1, double c1, double a2, double c2);

    /**
     * trapezoidal membership function
     *
     * @param x input value for which to compute membership value.
     * @param a defines its left foot.
     * @param b defines its left shoulder.
     * @param c defines its right shoulder.
     * @param d defines its right foot.
     * @return membership value.
     */
    public static final native double trap(double x, double a, double b, double c, double d);

    /**
     * triangular membership function
     *
     * @param x input value for which to compute membership value.
     * @param a defines its left foot.
     * @param b defines its peak.
     * @param c defines its right foot.
     * @return membership value.
     */
    public static final native double tri(double x, double a, double b, double c);

    /**
     * linear s-shaped saturation membership function
     *
     * @param x input value for which to compute membership value.
     * @param a defines its foot.
     * @param b defines its shoulder.
     * @return membership value.
     */
    public static final native double lins(double x, double a, double b);

    /**
     * linear z-shaped saturation membership function
     *
     * @param x input value for which to compute membership value.
     * @param a defines its shoulder.
     * @param b defines its foot.
     * @return membership value.
     */
    public static final native double linz(double x, double a, double b);

    /**
     * s-shaped membership function
     *
     * @param x input value for which to compute membership value.
     * @param a defines its foot.
     * @param b defines its shoulder.
     * @return membership value.
     */
    public static final native double s(double x, double a, double b);

    /**
     * z-shaped membership function
     *
     * @param x input value for which to compute membership value.
     * @param a defines its shoulder.
     * @param b defines its foot.
     * @return membership value.
     */
    public static final native double z(double x, double a, double b);

    /**
     * pi-shaped membership function
     *
     * @param x input value for which to compute membership value.
     * @param a defines its left foot.
     * @param b defines its left shoulder.
     * @param c defines its right shoulder.
     * @param d defines its right foot.
     * @return membership value.
     */
    public static final native double pi(double x, double a, double b, double c, double d);
}
