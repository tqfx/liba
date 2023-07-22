#ifndef TEST_TF_H
#define TEST_TF_H
#define MAIN_(s, argc, argv) A_CAST_2(tf, s)(argc, argv)
#include "test.h"
#include "a/tf.h"

static a_float_t u[] = {
    A_FLOAT_C(2000.0),
    A_FLOAT_C(-652.99418),
    A_FLOAT_C(-344.66975),
    A_FLOAT_C(-168.84826),
    A_FLOAT_C(-133.5101),
    A_FLOAT_C(-109.5296),
    A_FLOAT_C(-86.454203),
    A_FLOAT_C(-67.783481),
    A_FLOAT_C(-53.22429),
    A_FLOAT_C(-41.808457),
    A_FLOAT_C(-32.835939),
    A_FLOAT_C(-25.786913),
    A_FLOAT_C(-20.2509),
    A_FLOAT_C(-15.903432),
    A_FLOAT_C(-12.489385),
    A_FLOAT_C(-9.8083792),
    A_FLOAT_C(-7.703033),
    A_FLOAT_C(-6.0497455),
    A_FLOAT_C(-4.7514505),
    A_FLOAT_C(-3.731923),
    A_FLOAT_C(-2.9313047),
    A_FLOAT_C(-2.3025903),
    A_FLOAT_C(-1.8088678),
    A_FLOAT_C(-1.4211508),
    A_FLOAT_C(-1.1166775),
    A_FLOAT_C(-0.87757332),
    A_FLOAT_C(-0.68980192),
    A_FLOAT_C(-0.54234094),
    A_FLOAT_C(-0.42653479),
    A_FLOAT_C(-0.33558647),
    A_FLOAT_C(-0.26415848),
    A_FLOAT_C(-0.2080594),
    A_FLOAT_C(-0.16399783),
    A_FLOAT_C(-0.12938911),
    A_FLOAT_C(-0.10220358),
    A_FLOAT_C(-0.080847398),
    A_FLOAT_C(-0.064068962),
    A_FLOAT_C(-0.050885415),
    A_FLOAT_C(-0.040524947),
    A_FLOAT_C(-0.032381475),
    A_FLOAT_C(-0.025979056),
    A_FLOAT_C(-0.020943941),
    A_FLOAT_C(-0.016982637),
    A_FLOAT_C(-0.013864667),
    A_FLOAT_C(-0.011409044),
    A_FLOAT_C(-0.0094736412),
    A_FLOAT_C(-0.00794685),
    A_FLOAT_C(-0.0067410251),
    A_FLOAT_C(-0.0057873396),
    A_FLOAT_C(-0.0050317445),
    A_FLOAT_C(-0.0044317954),
    A_FLOAT_C(-0.0039541603),
    A_FLOAT_C(-0.0035726634),
    A_FLOAT_C(-0.0032667484),
    A_FLOAT_C(-0.0030202717),
    A_FLOAT_C(-0.002820555),
    A_FLOAT_C(-0.0026576412),
    A_FLOAT_C(-0.0025237103),
    A_FLOAT_C(-0.00241262),
    A_FLOAT_C(-0.0023195462),
    A_FLOAT_C(-0.0022406992),
    A_FLOAT_C(-0.0021731023),
    A_FLOAT_C(-0.0021144168),
    A_FLOAT_C(-0.002062805),
    A_FLOAT_C(-0.0020168229),
    A_FLOAT_C(-0.0019753356),
    A_FLOAT_C(-0.0019374509),
    A_FLOAT_C(-0.0019024669),
    A_FLOAT_C(-0.0018698319),
    A_FLOAT_C(-0.0018391113),
    A_FLOAT_C(-0.0018099631),
    A_FLOAT_C(-0.0017821178),
    A_FLOAT_C(-0.0017553627),
    A_FLOAT_C(-0.00172953),
    A_FLOAT_C(-0.001704487),
    A_FLOAT_C(-0.0016801285),
    A_FLOAT_C(-0.0016563712),
    A_FLOAT_C(-0.0016331487),
    A_FLOAT_C(-0.0016104081),
    A_FLOAT_C(-0.0015881069),
    A_FLOAT_C(-0.0015662109),
    A_FLOAT_C(-0.0015446926),
    A_FLOAT_C(-0.0015235294),
    A_FLOAT_C(-0.0015027029),
    A_FLOAT_C(-0.0014821978),
    A_FLOAT_C(-0.0014620014),
    A_FLOAT_C(-0.0014421028),
    A_FLOAT_C(-0.0014224928),
    A_FLOAT_C(-0.0014031634),
    A_FLOAT_C(-0.0013841076),
    A_FLOAT_C(-0.0013653192),
    A_FLOAT_C(-0.0013467927),
    A_FLOAT_C(-0.0013285228),
    A_FLOAT_C(-0.001310505),
    A_FLOAT_C(-0.0012927348),
    A_FLOAT_C(-0.0012752081),
    A_FLOAT_C(-0.001257921),
    A_FLOAT_C(-0.0012408699),
    A_FLOAT_C(-0.0012240512),
    A_FLOAT_C(-0.0012074614),
};

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
    a_float_t input[a_array_n(num)];
    a_float_t output[a_array_n(den)];
    a_tf_init(&ctx, a_array_n(num), num, input, a_array_n(den), den, output);

    for (unsigned int i = 0; i < a_array_n(u); ++i)
    {
        a_tf_iter(&ctx, u[i]);
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
               A_FLOAT_C(0.001) * a_float_c(, i), A_FLOAT_C(1.0), *ctx.output);
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

#endif /* test/tf.h */
