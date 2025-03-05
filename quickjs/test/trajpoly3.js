import * as a from "liba.so";
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
var ctx = new a.trajpoly3(1, 0, 1);
ctx.gen(10, 0, 10, 0, 0);
assert("ctx.c0");
assert("ctx.c1");
assert("ctx.c2");
for (var i = 0; i < 10; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i));
}
