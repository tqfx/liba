import * as a from "liba.so";
function assert(b, str) {
    if (b) {
        return;
    } else {
        throw Error("assertion failed: " + str);
    }
}
assert(a.mf.NUL == 0)
assert(a.mf.GAUSS == 1)
assert(a.mf.GBELL == 2)
assert(a.mf.SIG == 3)
assert(a.mf.TRAP == 4)
assert(a.mf.TRI == 5)
assert(a.mf.Z == 6)
for (var i = -1; i < 1; i += 0.1) {
    console.log(
        a.mf.gauss(i, 1, 0),
        a.mf.gbell(i, 2, 1, 0),
        a.mf.sig(i, 2, 0),
        a.mf.trap(i, -2, -1, 1, 2),
        a.mf.tri(i, -1, 0, 1),
        a.mf.z(i, -1, 1)
    )
}
