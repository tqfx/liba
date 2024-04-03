#define MAIN(x) version##x
#include "test.h"
#include "a/version.h"

int main(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
#if defined(__cplusplus)
    a::version v000 = A_VERSION_0();
    a::version v100 = A_VERSION_1(1);
    a::version v010 = A_VERSION_2(0, 1);
    a::version v001 = A_VERSION_3(0, 0, 1);
    v010.parse(".1");

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
    a_version v000 = A_VERSION_0();
    a_version v100 = A_VERSION_1(1);
    a_version v010 = A_VERSION_2(0, 1);
    a_version v001 = A_VERSION_3(0, 0, 1);

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
#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_ASSERT_BUILD(std::is_pod<a_version>::value);
#endif /* __cplusplus */
    for (int i = 0; i < argc; ++i)
    {
        char str[48];
        a_version ctx = A_VERSION_0();
        a_version_parse(&ctx, argv[i]);
        a_version_tostr(&ctx, str, sizeof(str));
        debug("parse \"%s\" -> %s\n", argv[i], str);
    }
    printf("%s\n", A_FUNC);
    debug("version %u.%u.%u+%" PRIu32 "\n", a_version_major, a_version_minor, a_version_patch, a_version_tweak);
    TEST_BUG(a_version_check() == 0);
    return 0;
}
