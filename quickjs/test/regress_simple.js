import * as a from "liba.so";
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
var x = [0, 1, 2, 3, 4];
var y = [1, 2, 3, 4, 5];
var ctx = new a.regress_simple();
ctx.ols_(x, y, 2, 3);
console.log(ctx.evar(y[0]), ctx.eval(x[0]));
ctx.zero();
ctx.olsx(x, y, 2);
console.log(ctx.evar(y[0]), ctx.eval(x[0]));
ctx.zero();
ctx.olsy(x, y, 3);
console.log(ctx.evar(y[0]), ctx.eval(x[0]));
ctx.zero();
ctx.ols(x, y);
console.log(ctx.evar(y[0]), ctx.eval(x[0]));
ctx.zero();
assert("ctx.coef != undefined");
assert("ctx.bias != undefined");
ctx.coef = 1;
ctx.bias = 1;
