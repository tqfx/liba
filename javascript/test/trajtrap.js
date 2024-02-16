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
var ctx = new liba.trajtrap()
ctx.gen(2, 2, -2, 0, 4, 0, 0)
console.log(ctx.t)
console.log(ctx.p0)
console.log(ctx.p1)
console.log(ctx.v0)
console.log(ctx.v1)
console.log(ctx.vc)
console.log(ctx.ta)
console.log(ctx.td)
console.log(ctx.pa)
console.log(ctx.pd)
console.log(ctx.ac)
console.log(ctx.de)
console.log(ctx.pos(0.5), ctx.vel(0.5), ctx.acc(0.5))
do_leak_check(ctx)
