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
var ctx = new liba.lpf(10, 0.01)
ctx.gen(10, 0.01).zero()
console.log(ctx.iter(1.0), ctx.iter(1.0))
console.log(ctx.alpha, ctx.output)
do_leak_check(ctx)
var ctx = new liba.lpf(0.1)
console.log(ctx.iter(1.0), ctx.iter(1.0))
console.log(ctx.alpha, ctx.output)
do_leak_check(ctx)
