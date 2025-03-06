package liba;

import java.nio.ByteBuffer;

/** simple linear regression */
public class regress_simple {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        clinit();
    }

    static final native void clinit();

    final native void init(double coef, double bias);

    /**
     * construct a new {@link regress_simple} object
     *
     * @param coef regression coefficient
     * @param bias intercept
     */
    public regress_simple(double coef, double bias) {
        init(coef, bias);
    }

    /**
     * get regression coefficient for simple linear regression
     *
     * @return regression coefficient
     */
    public final native double coef();

    /**
     * set regression coefficient for simple linear regression
     *
     * @param coef regression coefficient
     * @return {@link regress_simple}
     */
    public final native regress_simple set_coef(double coef);

    /**
     * get intercept for simple linear regression
     *
     * @return intercept
     */
    public final native double bias();

    /**
     * set intercept for simple linear regression
     *
     * @param bias intercept
     * @return {@link regress_simple}
     */
    public final native regress_simple set_bias(double bias);

    /**
     * compute predicted value for simple linear regression
     *
     * @param val independent variable
     * @return predicted value
     */
    public final native double eval(double val);

    /**
     * compute predicted value for simple linear regression
     *
     * @param val dependent variable
     * @return predicted value
     */
    public final native double evar(double val);

    /**
     * compute predicted value for simple linear regression
     *
     * @param x predictor data, specified as a numeric vector
     * @param y response data, specified as a numeric vector
     * @param x_mean mean of predictor data
     * @param y_mean mean of response data
     * @return {@link regress_simple}
     */
    public final native regress_simple ols_(double[] x, double[] y, double x_mean, double y_mean);

    /**
     * compute predicted value for simple linear regression
     *
     * @param x predictor data, specified as a numeric vector
     * @param y response data, specified as a numeric vector
     * @param x_mean mean of predictor data
     * @return {@link regress_simple}
     */
    public final native regress_simple olsx(double[] x, double[] y, double x_mean);

    /**
     * compute predicted value for simple linear regression
     *
     * @param x predictor data, specified as a numeric vector
     * @param y response data, specified as a numeric vector
     * @param y_mean mean of response data
     * @return {@link regress_simple}
     */
    public final native regress_simple olsy(double[] x, double[] y, double y_mean);

    /**
     * compute predicted value for simple linear regression
     *
     * @param x predictor data, specified as a numeric vector
     * @param y response data, specified as a numeric vector
     * @return {@link regress_simple}
     */
    public final native regress_simple ols(double[] x, double[] y);

    /**
     * zeroing for simple linear regression
     *
     * @return {@link regress_simple}
     */
    public final native regress_simple zero();
}
