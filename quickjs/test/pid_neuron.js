import * as a from "liba.so";

var ctx = new a.pid_neuron()
ctx.kpid(10, 1, 0.1, 1)
ctx.wpid(1, 0, 0)
console.log(ctx.iter(10, 0))
ctx.zero()

var ctx = new a.pid_neuron(-10, 10)
ctx.kpid(10, 1, 0.1, 1)
ctx.wpid(1, 0, 0)
console.log(ctx.iter(10, 0))
ctx.zero()

var ctx = new a.pid_neuron()
ctx.mode = ctx.mode
ctx.k = ctx.k
ctx.kp = ctx.kp
ctx.ki = ctx.ki
ctx.kd = ctx.kd
ctx.wp = ctx.wp
ctx.wi = ctx.wi
ctx.wd = ctx.wd
ctx.summax = ctx.summax
ctx.outmax = ctx.outmax
ctx.outmin = ctx.outmin
ctx.out
ctx.fdb
ctx.err
ctx.ec
