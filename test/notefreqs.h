#ifndef TEST_NOTEFREQS_H
#define TEST_NOTEFREQS_H
#define MAIN_(s, argc, argv) A_CAST_2(notefreqs, s)(argc, argv)
#include "test.h"
#define A_NOTEFREQ_T a_float_t
#define A_NOTEFREQ_C(X) A_FLOAT_C(X)
#define A_NOTEFREQ_FREQ ((8000000 >> 1) / 100)
#include "a/notefreqs.h"

static a_float_t const song[][2] = {
    /* clang-format off */
    {A_NOTEFREQ_FREQ_C0,  A_NOTEFREQ_C0},  {A_NOTEFREQ_FREQ_C_0, A_NOTEFREQ_C_0}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_D0,  A_NOTEFREQ_D0},  {A_NOTEFREQ_FREQ_D_0, A_NOTEFREQ_D_0}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_E0,  A_NOTEFREQ_E0},  {A_NOTEFREQ_FREQ_F0,  A_NOTEFREQ_F0}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_F_0, A_NOTEFREQ_F_0}, {A_NOTEFREQ_FREQ_G0,  A_NOTEFREQ_G0}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_G_0, A_NOTEFREQ_G_0}, {A_NOTEFREQ_FREQ_A0,  A_NOTEFREQ_A0}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_A_0, A_NOTEFREQ_A_0}, {A_NOTEFREQ_FREQ_B0,  A_NOTEFREQ_B0}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_C1,  A_NOTEFREQ_C1},  {A_NOTEFREQ_FREQ_C_1, A_NOTEFREQ_C_1}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_D1,  A_NOTEFREQ_D1},  {A_NOTEFREQ_FREQ_D_1, A_NOTEFREQ_D_1}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_E1,  A_NOTEFREQ_E1},  {A_NOTEFREQ_FREQ_F1,  A_NOTEFREQ_F1}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_F_1, A_NOTEFREQ_F_1}, {A_NOTEFREQ_FREQ_G1,  A_NOTEFREQ_G1}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_G_1, A_NOTEFREQ_G_1}, {A_NOTEFREQ_FREQ_A1,  A_NOTEFREQ_A1}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_A_1, A_NOTEFREQ_A_1}, {A_NOTEFREQ_FREQ_B1,  A_NOTEFREQ_B1}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_C2,  A_NOTEFREQ_C2},  {A_NOTEFREQ_FREQ_C_2, A_NOTEFREQ_C_2}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_D2,  A_NOTEFREQ_D2},  {A_NOTEFREQ_FREQ_D_2, A_NOTEFREQ_D_2}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_E2,  A_NOTEFREQ_E2},  {A_NOTEFREQ_FREQ_F2,  A_NOTEFREQ_F2}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_F_2, A_NOTEFREQ_F_2}, {A_NOTEFREQ_FREQ_G2,  A_NOTEFREQ_G2}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_G_2, A_NOTEFREQ_G_2}, {A_NOTEFREQ_FREQ_A2,  A_NOTEFREQ_A2}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_A_2, A_NOTEFREQ_A_2}, {A_NOTEFREQ_FREQ_B2,  A_NOTEFREQ_B2}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_C3,  A_NOTEFREQ_C3},  {A_NOTEFREQ_FREQ_C_3, A_NOTEFREQ_C_3}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_D3,  A_NOTEFREQ_D3},  {A_NOTEFREQ_FREQ_D_3, A_NOTEFREQ_D_3}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_E3,  A_NOTEFREQ_E3},  {A_NOTEFREQ_FREQ_F3,  A_NOTEFREQ_F3}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_F_3, A_NOTEFREQ_F_3}, {A_NOTEFREQ_FREQ_G3,  A_NOTEFREQ_G3}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_G_3, A_NOTEFREQ_G_3}, {A_NOTEFREQ_FREQ_A3,  A_NOTEFREQ_A3}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_A_3, A_NOTEFREQ_A_3}, {A_NOTEFREQ_FREQ_B3,  A_NOTEFREQ_B3}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_C4,  A_NOTEFREQ_C4},  {A_NOTEFREQ_FREQ_C_4, A_NOTEFREQ_C_4}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_D4,  A_NOTEFREQ_D4},  {A_NOTEFREQ_FREQ_D_4, A_NOTEFREQ_D_4}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_E4,  A_NOTEFREQ_E4},  {A_NOTEFREQ_FREQ_F4,  A_NOTEFREQ_F4}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_F_4, A_NOTEFREQ_F_4}, {A_NOTEFREQ_FREQ_G4,  A_NOTEFREQ_G4}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_G_4, A_NOTEFREQ_G_4}, {A_NOTEFREQ_FREQ_A4,  A_NOTEFREQ_A4}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_A_4, A_NOTEFREQ_A_4}, {A_NOTEFREQ_FREQ_B4,  A_NOTEFREQ_B4}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_C5,  A_NOTEFREQ_C5},  {A_NOTEFREQ_FREQ_C_5, A_NOTEFREQ_C_5}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_D5,  A_NOTEFREQ_D5},  {A_NOTEFREQ_FREQ_D_5, A_NOTEFREQ_D_5}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_E5,  A_NOTEFREQ_E5},  {A_NOTEFREQ_FREQ_F5,  A_NOTEFREQ_F5}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_F_5, A_NOTEFREQ_F_5}, {A_NOTEFREQ_FREQ_G5,  A_NOTEFREQ_G5}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_G_5, A_NOTEFREQ_G_5}, {A_NOTEFREQ_FREQ_A5,  A_NOTEFREQ_A5}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_A_5, A_NOTEFREQ_A_5}, {A_NOTEFREQ_FREQ_B5,  A_NOTEFREQ_B5}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_C6,  A_NOTEFREQ_C6},  {A_NOTEFREQ_FREQ_C_6, A_NOTEFREQ_C_6}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_D6,  A_NOTEFREQ_D6},  {A_NOTEFREQ_FREQ_D_6, A_NOTEFREQ_D_6}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_E6,  A_NOTEFREQ_E6},  {A_NOTEFREQ_FREQ_F6,  A_NOTEFREQ_F6}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_F_6, A_NOTEFREQ_F_6}, {A_NOTEFREQ_FREQ_G6,  A_NOTEFREQ_G6}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_G_6, A_NOTEFREQ_G_6}, {A_NOTEFREQ_FREQ_A6,  A_NOTEFREQ_A6}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_A_6, A_NOTEFREQ_A_6}, {A_NOTEFREQ_FREQ_B6,  A_NOTEFREQ_B6}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_C7,  A_NOTEFREQ_C7},  {A_NOTEFREQ_FREQ_C_7, A_NOTEFREQ_C_7}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_D7,  A_NOTEFREQ_D7},  {A_NOTEFREQ_FREQ_D_7, A_NOTEFREQ_D_7}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_E7,  A_NOTEFREQ_E7},  {A_NOTEFREQ_FREQ_F7,  A_NOTEFREQ_F7}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_F_7, A_NOTEFREQ_F_7}, {A_NOTEFREQ_FREQ_G7,  A_NOTEFREQ_G7}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_G_7, A_NOTEFREQ_G_7}, {A_NOTEFREQ_FREQ_A7,  A_NOTEFREQ_A7}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_A_7, A_NOTEFREQ_A_7}, {A_NOTEFREQ_FREQ_B7,  A_NOTEFREQ_B7}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_C8,  A_NOTEFREQ_C8},  {A_NOTEFREQ_FREQ_C_8, A_NOTEFREQ_C_8}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_D8,  A_NOTEFREQ_D8},  {A_NOTEFREQ_FREQ_D_8, A_NOTEFREQ_D_8}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_E8,  A_NOTEFREQ_E8},  {A_NOTEFREQ_FREQ_F8,  A_NOTEFREQ_F8}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_F_8, A_NOTEFREQ_F_8}, {A_NOTEFREQ_FREQ_G8,  A_NOTEFREQ_G8}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_G_8, A_NOTEFREQ_G_8}, {A_NOTEFREQ_FREQ_A8,  A_NOTEFREQ_A8}, // NOLINT(bugprone-integer-division)
    {A_NOTEFREQ_FREQ_A_8, A_NOTEFREQ_A_8}, {A_NOTEFREQ_FREQ_B8,  A_NOTEFREQ_B8}, // NOLINT(bugprone-integer-division)
    /* clang-format on */
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

    for (unsigned int i = 0; i != A_LEN(song); ++i)
    {
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("", "g\t") A_FLOAT_PRI("", "g\t") A_FLOAT_PRI("", "g\n"), song[i][0], song[i][1], 1 / song[i][1]);
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

#endif /* test/notefreqs.h */
