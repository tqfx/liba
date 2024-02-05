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
assert(ctx.q1 != undefined)
assert(ctx.q2 != undefined)
assert(ctx.t1 != undefined)
assert(ctx.t2 != undefined)
assert(ctx.vs != undefined)
assert(ctx.vc != undefined)
assert(ctx.ve != undefined)
assert(ctx.q != undefined)
assert(ctx.t != undefined)
for (var i = 0; i < ctx.t; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i))
}
