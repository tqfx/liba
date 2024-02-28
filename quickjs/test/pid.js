import * as a from "liba.so";

var ctx = new a.pid()
ctx.kpid(10, 0.1, 1)
console.log(ctx.run(1, 0))
ctx.zero()
console.log(ctx.pos(1, 0))
ctx.zero()
console.log(ctx.inc(1, 0))
ctx.zero()
ctx.kp = ctx.kp
ctx.ki = ctx.ki
ctx.kd = ctx.kd
ctx.summax = ctx.summax
ctx.summin = ctx.summin
ctx.sum
ctx.outmax = ctx.outmax
ctx.outmin = ctx.outmin
ctx.out
ctx.fdb
ctx.err
