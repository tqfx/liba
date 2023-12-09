#!/usr/bin/env node
var liba = require("../liba")
var ctx = new liba.pid_neuron()
ctx.wpid(1, 0, 0).kpid(10, 1, 0.1, 1)
console.log(ctx.zero().off(10, 0))
console.log(ctx.zero().inc(10, 0))
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
ctx.delete()
