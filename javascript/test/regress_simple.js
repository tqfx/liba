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
var ctx = new liba.regress_simple();
ctx.ols_(x, y, 2, 3);
console.log(ctx.evar(y[0]), ctx.eval(x[0]), ctx.coef, ctx.bias);
ctx.zero();
ctx.olsx(x, y, 2);
console.log(ctx.evar(y[0]), ctx.eval(x[0]), ctx.coef, ctx.bias);
ctx.zero();
ctx.olsy(x, y, 3);
console.log(ctx.evar(y[0]), ctx.eval(x[0]), ctx.coef, ctx.bias);
ctx.zero();
ctx.ols(x, y);
console.log(ctx.evar(y[0]), ctx.eval(x[0]), ctx.coef, ctx.bias);
ctx.zero();
assert("ctx.coef != undefined");
assert("ctx.bias != undefined");
ctx.coef = ctx.coef;
ctx.bias = ctx.bias;
do_leak_check(ctx);
