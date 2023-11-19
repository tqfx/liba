#!/usr/bin/env node
var liba = require("../liba")
function assert(b, str) {
    if (b) {
        return;
    } else {
        throw Error("assertion failed: " + str);
    }
}
assert(liba.MF_NUL == 0)
assert(liba.MF_GAUSS == 1)
assert(liba.MF_GAUSS2 == 2)
assert(liba.MF_GBELL == 3)
assert(liba.MF_SIG == 4)
assert(liba.MF_DSIG == 5)
assert(liba.MF_PSIG == 6)
assert(liba.MF_TRAP == 7)
assert(liba.MF_TRI == 8)
assert(liba.MF_LINS == 9)
assert(liba.MF_LINZ == 10)
assert(liba.MF_S == 11)
assert(liba.MF_Z == 12)
assert(liba.MF_PI == 13)
for (var i = -1; i < 1; i += 0.1) {
    console.log(
        liba.mf_gauss(i, 1, 0),
        liba.mf_gauss2(i, 1, -1, 1, 1),
        liba.mf_gbell(i, 2, 1, 0),
        liba.mf_sig(i, 2, 0),
        liba.mf_dsig(i, 5, -2, 5, 2),
        liba.mf_psig(i, 5, -2, -5, 2),
        liba.mf_trap(i, -2, -1, 1, 2),
        liba.mf_tri(i, -1, 0, 1),
        liba.mf_lins(i, -1, 1),
        liba.mf_linz(i, -1, 1),
        liba.mf_s(i, -1, 1),
        liba.mf_z(i, -1, 1),
        liba.mf_pi(i, -2, -1, 1, 2)
    )
}
