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
var ctx = new liba.pid();
ctx.set_kpid(10, 0.1, 1);
console.log(ctx.zero().run(1, 0));
console.log(ctx.zero().pos(1, 0));
console.log(ctx.zero().inc(1, 0));
assert("ctx.kp != undefined");
assert("ctx.ki != undefined");
assert("ctx.kd != undefined");
assert("ctx.summax != undefined");
assert("ctx.summin != undefined");
assert("ctx.outmax != undefined");
assert("ctx.outmin != undefined");
assert("ctx.out != undefined");
assert("ctx.fdb != undefined");
assert("ctx.err != undefined");
ctx.kp = 0;
ctx.ki = 0;
ctx.kd = 0;
ctx.summax = 0;
ctx.summin = 0;
ctx.outmax = 0;
ctx.outmin = 0;
do_leak_check(ctx);
