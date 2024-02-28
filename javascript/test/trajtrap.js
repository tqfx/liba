#!/usr/bin/env node
var liba = require("../liba");
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
    }
}
function do_leak_check() {
    for (const arg of arguments) {
        arg.delete();
    }
    if (liba.do_leak_check) {
        liba.do_leak_check();
    }
}
var ctx = new liba.trajtrap();
ctx.gen(2, 2, -2, 0, 4, 0, 0);
assert(ctx.t != undefined);
assert(ctx.p0 != undefined);
assert(ctx.p1 != undefined);
assert(ctx.v0 != undefined);
assert(ctx.v1 != undefined);
assert(ctx.vc != undefined);
assert(ctx.ta != undefined);
assert(ctx.td != undefined);
assert(ctx.pa != undefined);
assert(ctx.pd != undefined);
assert(ctx.ac != undefined);
assert(ctx.de != undefined);
for (var i = 0; i < ctx.t; i += ctx.t / 10) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i));
}
do_leak_check(ctx);
