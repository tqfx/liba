import * as a from "liba.so";
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
var ctx = new a.trajpoly5(1, 0, 1);
ctx.gen(10, 0, 10, 0, 0);
assert("ctx.p");
assert("ctx.v");
assert("ctx.a");
for (var i = 0; i < 10; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i));
}
