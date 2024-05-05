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
var ctx = new liba.pid_neuro();
ctx.wpid(1, 0, 0).kpid(10, 1, 0.1, 1);
console.log(ctx.zero().run(10, 0));
console.log(ctx.zero().inc(10, 0));
assert("ctx.k != undefined");
assert("ctx.kp != undefined");
assert("ctx.ki != undefined");
assert("ctx.kd != undefined");
assert("ctx.wp != undefined");
assert("ctx.wi != undefined");
assert("ctx.wd != undefined");
assert("ctx.outmax != undefined");
assert("ctx.outmin != undefined");
assert("ctx.out != undefined");
assert("ctx.fdb != undefined");
assert("ctx.err != undefined");
assert("ctx.ec != undefined");
ctx.k = 0;
ctx.kp = 0;
ctx.ki = 0;
ctx.kd = 0;
ctx.wp = 0;
ctx.wi = 0;
ctx.wd = 0;
ctx.outmax = 0;
ctx.outmin = 0;
do_leak_check(ctx);
