#!/usr/bin/env node
const liba = require("../liba");
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
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
assert("ctx.c0");
assert("ctx.c1");
assert("ctx.c2");
for (var i = 0; i < 1; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i));
}
do_leak_check(ctx);
