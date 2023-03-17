#ifndef TEST_REAL_H
#define TEST_REAL_H
#define MAIN_(s, argc, argv) real##s(argc, argv)
#include "test.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    {
        a_f64_t min = A_F64_MIN;
        a_f64_t max = A_F64_MAX;
        a_f64_t inf = A_F64_INF;
        a_f64_t nan = A_F64_NAN;
#if defined(MAIN_ONCE)
        printf("64 min = %-12g max = %g\n", min, max);
        printf("64 inf = %-12g nan = %g\n", inf, nan);
#else /* !MAIN_ONCE */
        (void)(min);
        (void)(max);
        (void)(inf);
        (void)(nan);
#endif /* MAIN_ONCE */
    }
    {
        a_f32_t min = A_F32_MIN;
        a_f32_t max = A_F32_MAX;
        a_f32_t inf = A_F32_INF;
        a_f32_t nan = A_F32_NAN;
#if defined(MAIN_ONCE)
        printf("32 min = %-12g max = %g\n", min, max);
        printf("32 inf = %-12g nan = %g\n", inf, nan);
#else /* !MAIN_ONCE */
        (void)(min);
        (void)(max);
        (void)(inf);
        (void)(nan);
#endif /* MAIN_ONCE */
    }
    {
        a_real_t min = A_REAL_MIN;
        a_real_t max = A_REAL_MAX;
        a_real_t inf = A_REAL_INF;
        a_real_t nan = A_REAL_NAN;
#if defined(MAIN_ONCE)
        printf("min = " A_REAL_PRI("-12", "g ") "max = " A_REAL_PRI("", "g\n"), min, max);
        printf("inf = " A_REAL_PRI("-12", "g ") "nan = " A_REAL_PRI("", "g\n"), inf, nan);
#else /* !MAIN_ONCE */
        (void)(min);
        (void)(max);
        (void)(inf);
        (void)(nan);
#endif /* MAIN_ONCE */
    }
    return 0;
}

#endif /* real.h */
