import * as a from "liba.so";

var ctx = new a.pid()
ctx.kpid(10, 0.1, 1)
console.log(ctx.iter(1, 0))
ctx.zero()

var ctx = new a.pid(-10, 10)
ctx.kpid(10, 0.1, 1)
console.log(ctx.iter(1, 0))
ctx.zero()

var ctx = new a.pid(-10, 10, 10)
ctx.kpid(10, 0.1, 1)
console.log(ctx.iter(1, 0))
ctx.zero()

var ctx = new a.pid()
ctx.mode = ctx.mode
ctx.kp = ctx.kp
ctx.ki = ctx.ki
ctx.kd = ctx.kd
ctx.summax = ctx.summax
ctx.outmax = ctx.outmax
ctx.outmin = ctx.outmin
ctx.out
ctx.fdb
ctx.err
