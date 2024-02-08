import * as a from "liba.so";
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
    }
}
var ctx = new a.trajtrap()
assert(ctx.gen(2, 2, -2, 0, 4) != undefined)
assert(ctx.t != undefined)
assert(ctx.q0 != undefined)
assert(ctx.q1 != undefined)
assert(ctx.v0 != undefined)
assert(ctx.v1 != undefined)
assert(ctx.vc != undefined)
assert(ctx.ta != undefined)
assert(ctx.td != undefined)
assert(ctx.qa != undefined)
assert(ctx.qd != undefined)
assert(ctx.ac != undefined)
assert(ctx.de != undefined)
for (var i = 0; i < ctx.t; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i))
}
