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
var ctx = new liba.trajtrap(2, 2, -2, 0, 4, 0, 0)
do_leak_check(ctx)
var ctx = new liba.trajtrap(2, 2, -2, 0, 4)
console.log(ctx.t)
console.log(ctx.q0)
console.log(ctx.q1)
console.log(ctx.v0)
console.log(ctx.v1)
console.log(ctx.vc)
console.log(ctx.ta)
console.log(ctx.td)
console.log(ctx.qa)
console.log(ctx.qd)
console.log(ctx.ac)
console.log(ctx.de)
console.log(ctx.pos(0.5), ctx.vel(0.5), ctx.acc(0.5))
do_leak_check(ctx)
