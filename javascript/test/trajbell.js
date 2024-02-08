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
var ctx = new liba.trajbell()
ctx.gen(3, 2, 3, 0, 10, 0, 0)
console.log(ctx.t)
console.log(ctx.tv)
console.log(ctx.ta)
console.log(ctx.td)
console.log(ctx.taj)
console.log(ctx.tdj)
console.log(ctx.q0)
console.log(ctx.q1)
console.log(ctx.v0)
console.log(ctx.v1)
console.log(ctx.vm)
console.log(ctx.jm)
console.log(ctx.am)
console.log(ctx.dm)
console.log(ctx.pos(0.5), ctx.vel(0.5), ctx.acc(0.5), ctx.jer(0.5))
do_leak_check(ctx)
