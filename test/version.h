#ifndef TEST_VERSION_H
#define TEST_VERSION_H
#define MAIN_(s, argc, argv) A_CASE_2(version, s)(argc, argv)
#include "test.h"
#include "a/version.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
#if defined(__cplusplus)
    printf("version %s+%" PRIu64 "\n", a::VERSION, a::VERSION_TWEAK);
    printf("major %u\n", a::version_major());
    printf("minor %u\n", a::version_minor());
    printf("patch %u\n", a::version_patch());
    printf("tweak %" PRIu64 "\n", a::VERSION_TWEAK);
#else /* !__cplusplus */
    printf("version %s+%" PRIu64 "\n", a_version(), A_VERSION_TWEAK);
    printf("major %u\n", a_version_major());
    printf("minor %u\n", a_version_minor());
    printf("patch %u\n", a_version_patch());
    printf("tweak %" PRIu64 "\n", A_VERSION_TWEAK);
#endif /* __cplusplus */
#if defined(__cplusplus)
    a::version v000 = a::version(0, 0);
    a::version v010 = a::version(0, 1);
    TEST_BUG(v000 == v000);
    TEST_BUG(v000 != v010);
    TEST_BUG(v000 < v010);
    TEST_BUG(!(v000 < v000));
    TEST_BUG(v010 > v000);
    TEST_BUG(!(v000 > v000));
    TEST_BUG(v000 <= v010);
    TEST_BUG(!(v010 <= v000));
    TEST_BUG(v010 >= v010);
    TEST_BUG(!(v000 >= v010));
#else /* !__cplusplus */
    a_version_s v000 = A_VERSION_C(0, 0, 0);
    a_version_s v100 = A_VERSION_C(1, 0, 0);
    a_version_s v010 = A_VERSION_C(0, 1, 0);
    a_version_s v001 = A_VERSION_C(0, 0, 1);
    TEST_BUG(a_version_eq(&v000, &v000));
    TEST_BUG(a_version_ne(&v000, &v010));
    TEST_BUG(a_version_lt(&v000, &v010));
    TEST_BUG(!a_version_lt(&v000, &v000));
    TEST_BUG(a_version_gt(&v010, &v000));
    TEST_BUG(!a_version_gt(&v000, &v000));
    TEST_BUG(a_version_le(&v000, &v010));
    TEST_BUG(!a_version_le(&v010, &v000));
    TEST_BUG(a_version_ge(&v010, &v000));
    TEST_BUG(!a_version_ge(&v000, &v010));
    TEST_BUG(a_version_cmp(&v000, &v100) < 0);
    TEST_BUG(a_version_cmp(&v000, &v010) < 0);
    TEST_BUG(a_version_cmp(&v000, &v001) < 0);
    TEST_BUG(a_version_cmp(&v100, &v000) > 0);
    TEST_BUG(a_version_cmp(&v010, &v000) > 0);
    TEST_BUG(a_version_cmp(&v001, &v000) > 0);
    TEST_BUG(a_version_cmp(&v000, &v000) == 0);
#endif /* __cplusplus */
    TEST_BUG(a_version_check() == 0);
    return 0;
}

#endif /* test/version.h */
