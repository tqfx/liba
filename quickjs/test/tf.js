import * as a from "liba.so";
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
    }
}
var num = [6.59492796e-05, 6.54019884e-05]
var den = [-1.97530991, 0.97530991]
var ctx = new a.tf(num, den)
ctx.iter(1)
assert(ctx.num)
assert(ctx.den)
assert(ctx.input)
assert(ctx.output)
ctx.num = [1]
ctx.den = [2]
assert(ctx.num)
assert(ctx.den)
assert(ctx.input)
assert(ctx.output)
ctx.zero()
