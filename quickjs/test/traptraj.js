import * as a from "liba.so";
var ctx = new a.traptraj(10, 2, 0, 0, 2, 2)
ctx.gen(10, 2, 0, 0, 2, -2)
console.log(ctx.ac)
console.log(ctx.de)
console.log(ctx.ta)
console.log(ctx.qa)
console.log(ctx.tc)
console.log(ctx.qc)
console.log(ctx.td)
console.log(ctx.qd)
console.log(ctx.vs)
console.log(ctx.vc)
console.log(ctx.ve)
for (var i = 0; i < ctx.ta + ctx.tc + ctx.td; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i))
}
