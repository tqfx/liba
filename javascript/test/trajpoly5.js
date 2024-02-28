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
var ctx = new liba.trajpoly5(1, 0, 1, 0, 1, 0, 1);
assert(ctx.p);
assert(ctx.v);
assert(ctx.a);
for (var i = 0; i < 1; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i));
}
do_leak_check(ctx);
