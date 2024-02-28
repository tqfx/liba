import * as a from "liba.so";
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
    }
}
var ctx = new a.pid();
ctx.kpid(10, 0.1, 1);
console.log(ctx.run(1, 0));
ctx.zero();
console.log(ctx.pos(1, 0));
ctx.zero();
console.log(ctx.inc(1, 0));
ctx.zero();
assert(ctx.kp != undefined);
assert(ctx.ki != undefined);
assert(ctx.kd != undefined);
assert(ctx.summax != undefined);
assert(ctx.summin != undefined);
assert(ctx.outmax != undefined);
assert(ctx.outmin != undefined);
assert(ctx.out != undefined);
assert(ctx.fdb != undefined);
assert(ctx.err != undefined);
ctx.kp = 0;
ctx.ki = 0;
ctx.kd = 0;
ctx.summax = 0;
ctx.summin = 0;
ctx.outmax = 0;
ctx.outmin = 0;
