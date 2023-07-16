#ifndef TEST_TF_H
#define TEST_TF_H
#define MAIN_(s, argc, argv) A_CASE_2(tf, s)(argc, argv)
#include "test.h"
#include "a/tf.h"

static a_float_t u[] = {2000, -652.99418, -344.66975, -168.84826, -133.5101, -109.5296, -86.454203, -67.783481, -53.22429, -41.808457, -32.835939, -25.786913, -20.2509, -15.903432, -12.489385, -9.8083792, -7.703033, -6.0497455, -4.7514505, -3.731923, -2.9313047, -2.3025903, -1.8088678, -1.4211508, -1.1166775, -0.87757332, -0.68980192, -0.54234094, -0.42653479, -0.33558647, -0.26415848, -0.2080594, -0.16399783, -0.12938911, -0.10220358, -0.080847398, -0.064068962, -0.050885415, -0.040524947, -0.032381475, -0.025979056, -0.020943941, -0.016982637, -0.013864667, -0.011409044, -0.0094736412, -0.00794685, -0.0067410251, -0.0057873396, -0.0050317445, -0.0044317954, -0.0039541603, -0.0035726634, -0.0032667484, -0.0030202717, -0.002820555, -0.0026576412, -0.0025237103, -0.00241262, -0.0023195462, -0.0022406992, -0.0021731023, -0.0021144168, -0.002062805, -0.0020168229, -0.0019753356, -0.0019374509, -0.0019024669, -0.0018698319, -0.0018391113, -0.0018099631, -0.0017821178, -0.0017553627, -0.00172953, -0.001704487, -0.0016801285, -0.0016563712, -0.0016331487, -0.0016104081, -0.0015881069, -0.0015662109, -0.0015446926, -0.0015235294, -0.0015027029, -0.0014821978, -0.0014620014, -0.0014421028, -0.0014224928, -0.0014031634, -0.0013841076, -0.0013653192, -0.0013467927, -0.0013285228, -0.001310505, -0.0012927348, -0.0012752081, -0.001257921, -0.0012408699, -0.0012240512, -0.0012074614};

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

    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};

    a_tf_s ctx;
    a_float_t input[a_count_of(num)];
    a_float_t output[a_count_of(den)];
    a_tf_init(&ctx, a_count_of(num), num, input, a_count_of(den), den, output);

    for (unsigned int i = 0; i < a_count_of(u); ++i)
    {
        a_tf_iter(&ctx, u[i]);
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
               A_FLOAT_C(0.001) * i, A_FLOAT_C(1.0), *ctx.output);
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

#endif /* tf.h */
