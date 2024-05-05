#!/usr/bin/env node
const liba = require("../liba");
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
assert("liba.mf.NUL == 0");
assert("liba.mf.GAUSS == 1");
assert("liba.mf.GAUSS2 == 2");
assert("liba.mf.GBELL == 3");
assert("liba.mf.SIG == 4");
assert("liba.mf.DSIG == 5");
assert("liba.mf.PSIG == 6");
assert("liba.mf.TRAP == 7");
assert("liba.mf.TRI == 8");
assert("liba.mf.LINS == 9");
assert("liba.mf.LINZ == 10");
assert("liba.mf.S == 11");
assert("liba.mf.Z == 12");
assert("liba.mf.PI == 13");
for (var i = -1; i < 1; i += 0.1) {
    console.log(
        liba.mf.gauss(i, 1, 0),
        liba.mf.gauss2(i, 1, -1, 1, 1),
        liba.mf.gbell(i, 2, 1, 0),
        liba.mf.sig(i, 2, 0),
        liba.mf.dsig(i, 5, -2, 5, 2),
        liba.mf.psig(i, 5, -2, -5, 2),
        liba.mf.trap(i, -2, -1, 1, 2),
        liba.mf.tri(i, -1, 0, 1),
        liba.mf.lins(i, -1, 1),
        liba.mf.linz(i, -1, 1),
        liba.mf.s(i, -1, 1),
        liba.mf.z(i, -1, 1),
        liba.mf.pi(i, -2, -1, 1, 2)
    );
}
