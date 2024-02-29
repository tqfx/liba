import * as a from "liba.so";
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
assert("a.mf.NUL == 0");
assert("a.mf.GAUSS == 1");
assert("a.mf.GAUSS2 == 2");
assert("a.mf.GBELL == 3");
assert("a.mf.SIG == 4");
assert("a.mf.DSIG == 5");
assert("a.mf.PSIG == 6");
assert("a.mf.TRAP == 7");
assert("a.mf.TRI == 8");
assert("a.mf.LINS == 9");
assert("a.mf.LINZ == 10");
assert("a.mf.S == 11");
assert("a.mf.Z == 12");
assert("a.mf.PI == 13");
for (var i = -1; i < 1; i += 0.1) {
    console.log(
        a.mf.gauss(i, 1, 0),
        a.mf.gauss2(i, 1, -1, 1, 1),
        a.mf.gbell(i, 2, 1, 0),
        a.mf.sig(i, 2, 0),
        a.mf.dsig(i, 5, -2, 5, 2),
        a.mf.psig(i, 5, -2, -5, 2),
        a.mf.trap(i, -2, -1, 1, 2),
        a.mf.tri(i, -1, 0, 1),
        a.mf.lins(i, -1, 1),
        a.mf.linz(i, -1, 1),
        a.mf.s(i, -1, 1),
        a.mf.z(i, -1, 1),
        a.mf.pi(i, -2, -1, 1, 2)
    );
}
