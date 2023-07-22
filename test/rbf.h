#ifndef TEST_RBF_H
#define TEST_RBF_H
#define MAIN_(s, argc, argv) A_CAST_2(rbf, s)(argc, argv)
#include "test.h"
#include "a/tf.h"
#include "a/rbf.h"
#include "a/math.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
#if defined(MAIN_ONCE)
    FILE *log = A_NULL;
    if (argc > 1)
    {
        log = freopen(argv[1], "wb", stdout);
    }
#else /* !MAIN_ONCE */
    (void)(argc);
    (void)(argv);
#endif /* MAIN_ONCE */

    a_tf_s tf;
    {
        static a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
        static a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
        static a_float_t input[a_array_n(num)];
        static a_float_t output[a_array_n(den)];
        a_tf_init(&tf, a_array_n(num), num, input, a_array_n(den), den, output);
    }
    a_rbf_s ctx;
    {
        static a_float_t input[2];
        static a_float_t center[10] = {-1, A_FLOAT_C(-0.5), 0, A_FLOAT_C(0.5), 1, -10, 5, 0, 5, 10};
        static a_float_t height[5] = {A_FLOAT_C(1.5), A_FLOAT_C(1.5), A_FLOAT_C(1.5), A_FLOAT_C(1.5), A_FLOAT_C(1.5)};
        static a_float_t hidden[5];
        static a_float_t weight[5];
        static a_float_t deltaw[5];
        static a_float_t output[1];
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
        ctx.input_p[0] = a_float_sin(A_FLOAT_C(0.002) * A_FLOAT_PI * a_float_c(, i));
        ctx.input_p[1] = *tf.output;
        a_rbf_tune(&ctx, ctx.input_p);
        a_tf_iter(&tf, *a_rbf_iter(&ctx));
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
               A_FLOAT_C(0.002) * A_FLOAT_PI * a_float_c(, i), *ctx.input_p, *ctx.output_p, *tf.output);
#endif /* MAIN_ONCE */
    }

#if defined(MAIN_ONCE)
    if (log)
    {
        if (fclose(log))
        {
            perror(A_FUNC);
        }
    }
#endif /* MAIN_ONCE */

    return 0;
}

#endif /* test/rbf.h */
