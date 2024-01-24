#!/usr/bin/env node
var liba = require("../liba")
function do_leak_check() {
    for (const arg of arguments) {
        arg.delete()
    }
    if (liba.do_leak_check) {
        liba.do_leak_check()
    }
}

var ctx = new liba.pid()
ctx.kpid(10, 0.1, 1)
console.log(ctx.zero().run(1, 0))
console.log(ctx.zero().pos(1, 0))
console.log(ctx.zero().inc(1, 0))
do_leak_check(ctx)

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
do_leak_check(ctx)
