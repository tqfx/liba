#define MAIN_(x) A_CAST_2(x, _version)
#include "test.h"
#include "a/version.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    for (int i = 0; i < argc; ++i)
    {
        a_version_s ctx;
        a_version_parse(&ctx, argv[i]);
        debug("parse \"%s\" -> %u.%u.%u\n", argv[i], ctx.major, ctx.minor, ctx.patch);
    }
    printf("%s\n", A_FUNC);
#if defined(__cplusplus)
    printf("version %s+%" PRIu32 "\n", a::VERSION, a::version::TWEAK);
    printf("major %u\n", a::version::MAJOR);
    printf("minor %u\n", a::version::MINOR);
    printf("patch %u\n", a::version::PATCH);
    printf("tweak %" PRIu32 "\n", a::version::TWEAK);
#else /* !__cplusplus */
    printf("version %s+%" PRIu32 "\n", a_version, a_version_tweak);
    printf("major %u\n", a_version_major);
    printf("minor %u\n", a_version_minor);
    printf("patch %u\n", a_version_patch);
    printf("tweak %" PRIu32 "\n", a_version_tweak);
#endif /* __cplusplus */
#if defined(__cplusplus)
    a::version v000 = a::version();
    a::version v100 = a::version(1);
    a::version v010 = a::version(".1");
    a::version v001 = a::version(0, 0, 1);

    TEST_BUG(v000 == v000);
    TEST_BUG(v000 != v001);

    TEST_BUG(v000 < v001);
    TEST_BUG(v001 < v010);
    TEST_BUG(v010 < v100);

    TEST_BUG(v001 > v000);
    TEST_BUG(v010 > v001);
    TEST_BUG(v100 > v010);

    TEST_BUG(v000 <= v001);
    TEST_BUG(v001 <= v001);
    TEST_BUG(v001 <= v010);
    TEST_BUG(v010 <= v010);
    TEST_BUG(v010 <= v100);
    TEST_BUG(v100 <= v100);

    TEST_BUG(v001 >= v000);
    TEST_BUG(v001 >= v001);
    TEST_BUG(v010 >= v001);
    TEST_BUG(v010 >= v010);
    TEST_BUG(v100 >= v010);
    TEST_BUG(v100 >= v100);
#else /* !__cplusplus */
    a_version_s v000 = A_VERSION_C(0, 0, 0);
    a_version_s v100 = A_VERSION_C(1, 0, 0);
    a_version_s v010 = A_VERSION_C(0, 1, 0);
    a_version_s v001 = A_VERSION_C(0, 0, 1);

    TEST_BUG(a_version_eq(&v000, &v000));
    TEST_BUG(a_version_ne(&v000, &v001));

    TEST_BUG(a_version_lt(&v000, &v001));
    TEST_BUG(a_version_lt(&v001, &v010));
    TEST_BUG(a_version_lt(&v010, &v100));

    TEST_BUG(a_version_gt(&v001, &v000));
    TEST_BUG(a_version_gt(&v010, &v001));
    TEST_BUG(a_version_gt(&v100, &v010));

    TEST_BUG(a_version_le(&v000, &v001));
    TEST_BUG(a_version_le(&v001, &v001));
    TEST_BUG(a_version_le(&v001, &v010));
    TEST_BUG(a_version_le(&v010, &v010));
    TEST_BUG(a_version_le(&v010, &v100));
    TEST_BUG(a_version_le(&v100, &v100));

    TEST_BUG(a_version_ge(&v001, &v000));
    TEST_BUG(a_version_ge(&v001, &v001));
    TEST_BUG(a_version_ge(&v010, &v001));
    TEST_BUG(a_version_ge(&v010, &v010));
    TEST_BUG(a_version_ge(&v100, &v010));
    TEST_BUG(a_version_ge(&v100, &v100));

    TEST_BUG(a_version_cmp(&v010, &v100) < 0);
    TEST_BUG(a_version_cmp(&v001, &v010) < 0);
    TEST_BUG(a_version_cmp(&v000, &v001) < 0);
    TEST_BUG(a_version_cmp(&v100, &v010) > 0);
    TEST_BUG(a_version_cmp(&v010, &v001) > 0);
    TEST_BUG(a_version_cmp(&v001, &v000) > 0);
    TEST_BUG(a_version_cmp(&v000, &v000) == 0);
#endif /* __cplusplus */
    TEST_BUG(a_version_check() == 0);
    return 0;
}
