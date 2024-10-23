import * as a from "liba.so";
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
var x = [0, 1, 2, 3, 4];
var y = [1, 2, 3, 4, 5];
var ctx = new a.regress_linear([0]);
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
ctx.coef = [1, 2];
ctx.bias = 0;
