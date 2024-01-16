#define MAIN_(x) A_CAST_2(x, _rbf)
#include "test.h"
#include "a/tf.h"
#include "a/rbf.h"
#include "a/math.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    main_init(argc, argv, 1);

    a_tf tf;
    {
        static a_float num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
        static a_float den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
        static a_float input[A_LEN(num)];
        static a_float output[A_LEN(den)];
        a_tf_init(&tf, A_LEN(num), num, input, A_LEN(den), den, output);
    }
    a_rbf ctx;
    {
        static a_float input[2];
        static a_float center[10] = {-1, A_FLOAT_C(-0.5), 0, A_FLOAT_C(0.5), 1, -10, 5, 0, 5, 10};
        static a_float height[5] = {A_FLOAT_C(1.5), A_FLOAT_C(1.5), A_FLOAT_C(1.5), A_FLOAT_C(1.5), A_FLOAT_C(1.5)};
        static a_float hidden[5];
        static a_float weight[5];
        static a_float deltaw[5];
        static a_float output[1];
        ctx.input_p = input;
        ctx.input_n = 2;
        ctx.center_p = center;
        ctx.center_n = 10;
        ctx.height_p = height;
        ctx.height_n = 1;
        ctx.hidden_p = hidden;
        ctx.hidden_n = 5;
        ctx.output_p = output;
        ctx.output_n = 1;
        ctx.weight = weight;
        ctx.deltaw = deltaw;
        ctx.learn = A_FLOAT_C(0.5);
        ctx.alpha = A_FLOAT_C(0.05);
        a_rbf_zero(&ctx);
    }

    for (unsigned int i = 0; i < 1000; ++i)
    {
        ctx.input_p[0] = a_float_sin(A_FLOAT_C(0.002) * A_FLOAT_PI * a_float_c(i));
        ctx.input_p[1] = *tf.output;
        a_rbf_tune(&ctx, ctx.input_p);
        a_tf_iter(&tf, *a_rbf_iter(&ctx));
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
              A_FLOAT_C(0.002) * A_FLOAT_PI * a_float_c(i), *ctx.input_p, *ctx.output_p, *tf.output);
    }

    return 0;
}
