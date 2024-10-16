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
var x = [0, 1, 2, 3, 4];
var y = [1, 2, 3, 4, 5];
var ctx = new liba.regress_linear([0]);
ctx.zero();
for (let i = 0; i < 100; ++i) {
    ctx.sgd(x, y, 0.1);
}
console.log(ctx.coef, ctx.bias, ctx.err(x, y));
ctx.zero();
for (let i = 0; i < 100; ++i) {
    ctx.bgd(x, y, 0.1);
}
console.log(ctx.coef, ctx.bias, ctx.err(x, y));
ctx.zero();
ctx.mgd(x, y, 1e-3, 0.2, 0.1, 10, 100, 10);
console.log(ctx.coef, ctx.bias, ctx.err(x, y));
assert("ctx.coef != undefined");
assert("ctx.bias != undefined");
ctx.coef = ctx.coef;
ctx.bias = ctx.bias;
do_leak_check(ctx);
