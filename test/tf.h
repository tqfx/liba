#define MAIN(x) tf##x
#include "test.h"
#include "a/tf.h"

static a_real u[] = {
    A_REAL_C(2000.0),
    A_REAL_C(-652.99418),
    A_REAL_C(-344.66975),
    A_REAL_C(-168.84826),
    A_REAL_C(-133.5101),
    A_REAL_C(-109.5296),
    A_REAL_C(-86.454203),
    A_REAL_C(-67.783481),
    A_REAL_C(-53.22429),
    A_REAL_C(-41.808457),
    A_REAL_C(-32.835939),
    A_REAL_C(-25.786913),
    A_REAL_C(-20.2509),
    A_REAL_C(-15.903432),
    A_REAL_C(-12.489385),
    A_REAL_C(-9.8083792),
    A_REAL_C(-7.703033),
    A_REAL_C(-6.0497455),
    A_REAL_C(-4.7514505),
    A_REAL_C(-3.731923),
    A_REAL_C(-2.9313047),
    A_REAL_C(-2.3025903),
    A_REAL_C(-1.8088678),
    A_REAL_C(-1.4211508),
    A_REAL_C(-1.1166775),
    A_REAL_C(-0.87757332),
    A_REAL_C(-0.68980192),
    A_REAL_C(-0.54234094),
    A_REAL_C(-0.42653479),
    A_REAL_C(-0.33558647),
    A_REAL_C(-0.26415848),
    A_REAL_C(-0.2080594),
    A_REAL_C(-0.16399783),
    A_REAL_C(-0.12938911),
    A_REAL_C(-0.10220358),
    A_REAL_C(-0.080847398),
    A_REAL_C(-0.064068962),
    A_REAL_C(-0.050885415),
    A_REAL_C(-0.040524947),
    A_REAL_C(-0.032381475),
    A_REAL_C(-0.025979056),
    A_REAL_C(-0.020943941),
    A_REAL_C(-0.016982637),
    A_REAL_C(-0.013864667),
    A_REAL_C(-0.011409044),
    A_REAL_C(-0.0094736412),
    A_REAL_C(-0.00794685),
    A_REAL_C(-0.0067410251),
    A_REAL_C(-0.0057873396),
    A_REAL_C(-0.0050317445),
    A_REAL_C(-0.0044317954),
    A_REAL_C(-0.0039541603),
    A_REAL_C(-0.0035726634),
    A_REAL_C(-0.0032667484),
    A_REAL_C(-0.0030202717),
    A_REAL_C(-0.002820555),
    A_REAL_C(-0.0026576412),
    A_REAL_C(-0.0025237103),
    A_REAL_C(-0.00241262),
    A_REAL_C(-0.0023195462),
    A_REAL_C(-0.0022406992),
    A_REAL_C(-0.0021731023),
    A_REAL_C(-0.0021144168),
    A_REAL_C(-0.002062805),
    A_REAL_C(-0.0020168229),
    A_REAL_C(-0.0019753356),
    A_REAL_C(-0.0019374509),
    A_REAL_C(-0.0019024669),
    A_REAL_C(-0.0018698319),
    A_REAL_C(-0.0018391113),
    A_REAL_C(-0.0018099631),
    A_REAL_C(-0.0017821178),
    A_REAL_C(-0.0017553627),
    A_REAL_C(-0.00172953),
    A_REAL_C(-0.001704487),
    A_REAL_C(-0.0016801285),
    A_REAL_C(-0.0016563712),
    A_REAL_C(-0.0016331487),
    A_REAL_C(-0.0016104081),
    A_REAL_C(-0.0015881069),
    A_REAL_C(-0.0015662109),
    A_REAL_C(-0.0015446926),
    A_REAL_C(-0.0015235294),
    A_REAL_C(-0.0015027029),
    A_REAL_C(-0.0014821978),
    A_REAL_C(-0.0014620014),
    A_REAL_C(-0.0014421028),
    A_REAL_C(-0.0014224928),
    A_REAL_C(-0.0014031634),
    A_REAL_C(-0.0013841076),
    A_REAL_C(-0.0013653192),
    A_REAL_C(-0.0013467927),
    A_REAL_C(-0.0013285228),
    A_REAL_C(-0.001310505),
    A_REAL_C(-0.0012927348),
    A_REAL_C(-0.0012752081),
    A_REAL_C(-0.001257921),
    A_REAL_C(-0.0012408699),
    A_REAL_C(-0.0012240512),
    A_REAL_C(-0.0012074614),
};

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    a_tf ctx;
    a_real num[] = {A_REAL_C(6.59492796e-05), A_REAL_C(6.54019884e-05)};
    a_real den[] = {A_REAL_C(-1.97530991), A_REAL_C(0.97530991)};
    a_real input[A_LEN(num)];
    a_real output[A_LEN(den)];
    unsigned int i;

    main_init(argc, argv, 1);
    a_tf_init(&ctx, A_LEN(num), num, input, A_LEN(den), den, output);

    for (i = 0; i < A_LEN(u); ++i)
    {
        a_tf_iter(&ctx, u[i]);
        debug("%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f\n",
              A_REAL_C(0.001) * a_real_c(i), A_REAL_C(1.0), *ctx.output);
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_tf>::value);
#endif /* __cplusplus */

    return 0;
}
