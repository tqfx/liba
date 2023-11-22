#!/usr/bin/env node
var liba = require("../liba")

var ctx = new liba.pid()
ctx.kpid(10, 0.1, 1)
console.log(ctx.zero().off(1, 0))
console.log(ctx.zero().pos(1, 0))
console.log(ctx.zero().inc(1, 0))
ctx.delete()

var ctx = new liba.pid()
ctx.kp = ctx.kp
ctx.ki = ctx.ki
ctx.kd = ctx.kd
ctx.summax = ctx.summax
ctx.summin = ctx.summin
ctx.outmax = ctx.outmax
ctx.outmin = ctx.outmin
ctx.out
ctx.fdb
ctx.err
ctx.delete()
