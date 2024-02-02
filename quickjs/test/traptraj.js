import * as a from "liba.so";
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
    }
}
var ctx = new a.traptraj(10, 2, 2, -2)
assert(ctx.gen(10, 2, 2, -2) != undefined)
assert(ctx.ac != undefined)
assert(ctx.de != undefined)
assert(ctx.ta != undefined)
assert(ctx.qa != undefined)
assert(ctx.tc != undefined)
assert(ctx.qc != undefined)
assert(ctx.td != undefined)
assert(ctx.qd != undefined)
assert(ctx.vs != undefined)
assert(ctx.vc != undefined)
assert(ctx.ve != undefined)
for (var i = 0; i < ctx.ta + ctx.tc + ctx.td; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i))
}
