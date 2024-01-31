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
var ctx = new liba.polytraj7(1, 0, 1, 0, 1, 0, 1, 0, 1)
console.log(ctx.q)
console.log(ctx.v)
console.log(ctx.a)
console.log(ctx.j)
console.log(ctx.pos(0.5), ctx.vel(0.5), ctx.acc(0.5), ctx.jer(0.5))
do_leak_check(ctx)
