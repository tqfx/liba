import * as a from "liba.so";
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
var ctx = new a.lpf(10, 0.01);
ctx.gen(10, 0.01);
ctx.iter(1);
assert("ctx.alpha != undefined");
assert("ctx.output != undefined");
var ctx = new a.lpf(0.1);
ctx.gen(0.1);
ctx.iter(1);
assert("ctx.alpha != undefined");
assert("ctx.output != undefined");
ctx.zero();
