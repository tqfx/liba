#include "a.h"

typedef struct a_rbf_s
{
    a_float_t *input_p;
    a_float_t *center_p;
    a_float_t *hidden_p;
    a_float_t *weight_p;
    a_float_t *output_p;
} a_rbf;
