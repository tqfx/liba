#!/usr/bin/env node
const liba = require("../liba");
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
function do_leak_check() {
    for (const arg of arguments) {
        arg.delete();
    }
    if (liba.do_leak_check) {
        liba.do_leak_check();
    }
}
var NL = -3;
var NM = -2;
var NS = -1;
var ZO = 0;
var PS = +1;
var PM = +2;
var PL = +3;
var me = [
    [liba.mf.TRI, NL, NL, NM],
    [liba.mf.TRI, NL, NM, NS],
    [liba.mf.TRI, NM, NS, ZO],
    [liba.mf.TRI, NS, ZO, PS],
    [liba.mf.TRI, ZO, PS, PM],
    [liba.mf.TRI, PS, PM, PL],
    [liba.mf.TRI, PM, PL, PL],
];
var NL = -6;
var NM = -4;
var NS = -2;
var ZO = 0;
var PS = +2;
var PM = +4;
var PL = +6;
var mec = [
    [liba.mf.TRI, NL, NL, NM],
    [liba.mf.TRI, NL, NM, NS],
    [liba.mf.TRI, NM, NS, ZO],
    [liba.mf.TRI, NS, ZO, PS],
    [liba.mf.TRI, ZO, PS, PM],
    [liba.mf.TRI, PS, PM, PL],
    [liba.mf.TRI, PM, PL, PL],
];
var NL = -15;
var NM = -10;
var NS = -5;
var ZO = 0;
var PS = +5;
var PM = +10;
var PL = +15;
var mkp = [
    [NL, NL, NM, NM, NS, ZO, ZO],
    [NL, NL, NM, NS, NS, ZO, PS],
    [NM, NM, NM, NS, ZO, PS, PS],
    [NM, NM, NS, ZO, PS, PM, PM],
    [NS, NS, ZO, PS, PS, PM, PM],
    [NS, ZO, PS, PM, PM, PM, PL],
    [ZO, ZO, PM, PM, PM, PL, PL],
];
var NL = -3;
var NM = -2;
var NS = -1;
var ZO = 0;
var PS = +1;
var PM = +2;
var PL = +3;
var mki = [
    [PL, PL, PM, PM, PS, ZO, ZO],
    [PL, PL, PM, PS, PS, ZO, ZO],
    [PL, PM, PS, PS, ZO, NS, NS],
    [PM, PM, PS, ZO, NS, NM, NM],
    [PM, PS, ZO, NS, NS, NM, NL],
    [ZO, ZO, NS, NS, NM, NL, NL],
    [ZO, ZO, NS, NM, NM, NL, NL],
];
var mkd = [
    [NS, PS, PL, PL, PL, PM, NS],
    [NS, PS, PL, PM, PM, PS, ZO],
    [ZO, PS, PM, PM, PS, PS, ZO],
    [ZO, PS, PS, PS, PS, PS, ZO],
    [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
    [NL, NS, NS, NS, NS, NS, NL],
    [NL, NM, NM, NM, NS, NS, NL],
];
var ctx = new liba.pid_fuzzy();
ctx.set_rule(me, mec, mkp, mki, mkd).set_nfuzz(2);
ctx.set_kpid(10, 0.1, 1).set_opr(liba.pid_fuzzy.EQU);
console.log(ctx.zero().run(10, 0));
console.log(ctx.zero().pos(10, 0));
console.log(ctx.zero().inc(10, 0));
assert("ctx.kp != undefined");
assert("ctx.ki != undefined");
assert("ctx.kd != undefined");
assert("ctx.summax != undefined");
assert("ctx.summin != undefined");
assert("ctx.sum != undefined");
assert("ctx.outmax != undefined");
assert("ctx.outmin != undefined");
assert("ctx.out != undefined");
assert("ctx.fdb != undefined");
assert("ctx.err != undefined");
assert("ctx.nrule != undefined");
assert("ctx.nfuzz != undefined");
ctx.kp = 0;
ctx.ki = 0;
ctx.kd = 0;
ctx.summax = 0;
ctx.summin = 0;
ctx.outmax = 0;
ctx.outmin = 0;
ctx.nfuzz = 0;
do_leak_check(ctx);
