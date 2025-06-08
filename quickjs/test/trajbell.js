import * as a from "liba.so";
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
var ctx = new a.trajbell();
assert("ctx.gen(3, 2, 3, 0, 10) != undefined");
assert("ctx.t != undefined");
assert("ctx.tv != undefined");
assert("ctx.ta != undefined");
assert("ctx.td != undefined");
assert("ctx.taj != undefined");
assert("ctx.tdj != undefined");
assert("ctx.p0 != undefined");
assert("ctx.p1 != undefined");
assert("ctx.v0 != undefined");
assert("ctx.v1 != undefined");
assert("ctx.vm != undefined");
assert("ctx.jm != undefined");
assert("ctx.am != undefined");
assert("ctx.dm != undefined");
for (var i = 0; i < ctx.t; i += ctx.t / 10) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i), ctx.jer(i));
}
