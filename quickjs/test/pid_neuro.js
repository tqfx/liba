import * as a from "liba.so";
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
    }
}
var ctx = new a.pid_neuro();
ctx.kpid(10, 1, 0.1, 1);
ctx.wpid(1, 0, 0);
console.log(ctx.run(10, 0));
ctx.zero();
console.log(ctx.inc(10, 0));
ctx.zero();
assert(ctx.k != undefined);
assert(ctx.kp != undefined);
assert(ctx.ki != undefined);
assert(ctx.kd != undefined);
assert(ctx.wp != undefined);
assert(ctx.wi != undefined);
assert(ctx.wd != undefined);
assert(ctx.outmax != undefined);
assert(ctx.outmin != undefined);
assert(ctx.out != undefined);
assert(ctx.fdb != undefined);
assert(ctx.err != undefined);
assert(ctx.ec != undefined);
ctx.k = 0;
ctx.kp = 0;
ctx.ki = 0;
ctx.kd = 0;
ctx.wp = 0;
ctx.wi = 0;
ctx.wd = 0;
ctx.outmax = 0;
ctx.outmin = 0;
