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

var num = [6.59492796e-05, 6.54019884e-05]
var den = [1.0, -1.97530991, 0.97530991]

var ctx = new liba.tf(num, den)
ctx.set_num(num).set_den(den).zero()
console.log(ctx.iter(1.0), ctx.iter(1.0))
assert(ctx.num)
assert(ctx.den)
assert(ctx.input)
assert(ctx.output)
ctx.num = ctx.num
ctx.den = ctx.den
do_leak_check(ctx)
