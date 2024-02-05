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
var ctx = new liba.traptraj(10, 2, 2, -2)
console.log(ctx.ac)
console.log(ctx.de)
console.log(ctx.q1)
console.log(ctx.q2)
console.log(ctx.t1)
console.log(ctx.t2)
console.log(ctx.vs)
console.log(ctx.vc)
console.log(ctx.ve)
console.log(ctx.q)
console.log(ctx.t)
console.log(ctx.pos(0.5), ctx.vel(0.5), ctx.acc(0.5))
do_leak_check(ctx)
