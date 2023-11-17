#!/usr/bin/env node
var liba = require("../liba")

var ctx = new liba.pid()
ctx.kpid(10, 0.1, 1).zero()
console.log(ctx.iter(1, 0))
ctx.delete()

var ctx = new liba.pid(-10, 10)
ctx.kpid(10, 0.1, 1).zero()
console.log(ctx.iter(1, 0))
ctx.delete()

var ctx = new liba.pid(-10, 10, 10)
ctx.kpid(10, 0.1, 1).zero()
console.log(ctx.iter(1, 0))
ctx.delete()

var ctx = new liba.pid()
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
ctx.delete()
