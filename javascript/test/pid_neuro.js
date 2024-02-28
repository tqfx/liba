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
var ctx = new liba.pid_neuro()
ctx.wpid(1, 0, 0).kpid(10, 1, 0.1, 1)
console.log(ctx.zero().run(10, 0))
console.log(ctx.zero().inc(10, 0))
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
do_leak_check(ctx)
