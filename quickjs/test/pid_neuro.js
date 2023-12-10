import * as a from "liba.so";

var ctx = new a.pid_neuro()
ctx.kpid(10, 1, 0.1, 1)
ctx.wpid(1, 0, 0)
console.log(ctx.off(10, 0))
ctx.zero()
console.log(ctx.inc(10, 0))
ctx.zero()
ctx.k = ctx.k
ctx.kp = ctx.kp
ctx.ki = ctx.ki
ctx.kd = ctx.kd
ctx.wp = ctx.wp
ctx.wi = ctx.wi
ctx.wd = ctx.wd
ctx.outmax = ctx.outmax
ctx.outmin = ctx.outmin
ctx.out
ctx.fdb
ctx.err
ctx.ec
