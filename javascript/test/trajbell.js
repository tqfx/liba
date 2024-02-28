#!/usr/bin/env node
var liba = require("../liba")
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
    }
}
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
assert(ctx.t != undefined)
assert(ctx.tv != undefined)
assert(ctx.ta != undefined)
assert(ctx.td != undefined)
assert(ctx.taj != undefined)
assert(ctx.tdj != undefined)
assert(ctx.p0 != undefined)
assert(ctx.p1 != undefined)
assert(ctx.v0 != undefined)
assert(ctx.v1 != undefined)
assert(ctx.vm != undefined)
assert(ctx.jm != undefined)
assert(ctx.am != undefined)
assert(ctx.dm != undefined)
console.log(ctx.pos(0.5), ctx.vel(0.5), ctx.acc(0.5), ctx.jer(0.5))
do_leak_check(ctx)
