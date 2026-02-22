#define LIBA_RAND_C
#include "a/rand.h"

void a_rand_lcg48_init(a_rand_lcg48 *ctx, a_i64 x)
{
    ctx->a = A_U64_C(0x5DEECE66D);
    ctx->c = A_U16_C(0xB);
    ctx->x[0] = A_U16_C(0x330E);
    ctx->x[1] = (a_u16)(x);
    ctx->x[2] = (a_u16)(x >> 16);
}

void a_rand_lcg48_seed(a_rand_lcg48 *ctx, a_u16 const x[3])
{
    ctx->a = A_U64_C(0x5DEECE66D);
    ctx->c = A_U16_C(0xB);
    if (x)
    {
        ctx->x[0] = x[0];
        ctx->x[1] = x[1];
        ctx->x[2] = x[2];
    }
    else
    {
        ctx->x[0] = A_U16_C(0x330E);
        ctx->x[1] = A_U16_C(0xABCD);
        ctx->x[2] = A_U16_C(0x1234);
    }
}

a_u64 a_rand_lcg48_iter(a_rand_lcg48 *ctx, a_u16 x[3])
{
    a_u64 r = ((a_u64)x[2] << 32) | ((a_u32)x[1] << 16) | x[0];
    r *= ctx->a;
    r += ctx->c;
    x[0] = (a_u16)(r);
    x[1] = (a_u16)(r >> 16);
    x[2] = (a_u16)(r >> 32);
    return r;
}

a_i32 a_rand_lcg48i_(a_rand_lcg48 *ctx, a_u16 x[3])
{
    a_rand_lcg48_iter(ctx, x);
    return (a_i32)((a_u32)x[2] << 16) | x[1];
}

a_u32 a_rand_lcg48u_(a_rand_lcg48 *ctx, a_u16 x[3])
{
    a_rand_lcg48_iter(ctx, x);
    return ((a_u32)x[2] << 15) | (x[1] >> 1);
}

a_f64 a_rand_lcg48f_(a_rand_lcg48 *ctx, a_u16 x[3])
{
    a_u64 r = a_rand_lcg48_iter(ctx, x);
    return (a_f64)(r & 0xFFFFFFFFFFFFU) * (1.0 / 0x1000000000000);
}

void a_rand_lcg48_shuf(a_rand_lcg48 *ctx, void *ptr, a_size num, a_size siz)
{
    a_byte *p = (a_byte *)ptr;
    a_size n = num;
    while (n > 1)
    {
        a_size i = (a_size)(a_rand_lcg48f(ctx) * (a_f64)n--);
        a_swap(p + i * siz, p + n * siz, siz);
    }
}
