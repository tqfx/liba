package liba;

import java.nio.ByteBuffer;

/** linear regression */
public class regress_linear {
    ByteBuffer ctx;
    ByteBuffer coef;
    static {
        System.loadLibrary("a");
        clinit();
    }

    static final native void clinit();

    final native void init(double[] coef, double bias);

    /**
     * construct a new {@link regress_linear} object
     *
     * @param coef regression coefficient
     * @param bias intercept
     */
    public regress_linear(double[] coef, double bias) {
        init(coef, bias);
    }

    /**
     * get regression coefficient for linear regression
     *
     * @return regression coefficient
     */
    public final native double[] coef();

    /**
     * set regression coefficient for linear regression
     *
     * @param coef regression coefficient
     * @return {@link regress_linear}
     */
    public final native regress_linear set_coef(double[] coef);

    /**
     * get intercept for linear regression
     *
     * @return intercept
     */
    public final native double bias();

    /**
     * set intercept for linear regression
     *
     * @param bias intercept
     * @return {@link regress_linear}
     */
    public final native regress_linear set_bias(double bias);

    /**
     * compute predicted value for linear regression
     *
     * @param val independent variable
     * @return predicted value
     */
    public final native double eval(double[] val);

    /**
     * compute residuals for linear regression
     *
     * @param x predictor data, specified as a numeric matrix
     * @param y response data, specified as a numeric vector
     * @return residuals, specified as a numeric vector
     */
    public final native double[] err(double[] x, double[] y);

    /**
     * gradient descent for linear regression
     *
     * @param input predictor data, specified as a numeric vector
     * @param error residual, specified as a numeric scalar
     * @param alpha learning rate for gradient descent
     * @return {@link regress_linear}
     */
    public final native regress_linear gd(double[] input, double error, double alpha);

    /**
     * stochastic gradient descent for linear regression
     *
     * @param x predictor data, specified as a numeric matrix
     * @param y response data, specified as a numeric vector
     * @param alpha learning rate for gradient descent
     * @return {@link regress_linear}
     */
    public final native regress_linear sgd(double[] x, double[] y, double alpha);

    /**
     * batch gradient descent for linear regression
     *
     * @param x predictor data, specified as a numeric matrix
     * @param y response data, specified as a numeric vector
     * @param alpha learning rate for gradient descent
     * @return {@link regress_linear}
     */
    public final native regress_linear bgd(double[] x, double[] y, double alpha);

    /**
     * mini-batch gradient descent for linear regression
     *
     * @param x predictor data, specified as a numeric matrix
     * @param y response data, specified as a numeric vector
     * @param delta threshold for gradient descent value
     * @param lrmax maximum learning rate of iterations
     * @param lrmin minimum learning rate of iterations
     * @param lrtim total number of learning rate steps
     * @param epoch maximum number of epochs
     * @param batch batch size of data
     * @return change in loss function
     */
    public final native double mgd(double[] x, double[] y, double delta, double lrmax, double lrmin, int lrtim,
            int epoch, int batch);

    /**
     * zeroing for linear regression
     *
     * @return {@link regress_linear}
     */
    public final native regress_linear zero();
}
