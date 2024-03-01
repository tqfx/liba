#!/usr/bin/env node
var liba = require("../liba");
function do_leak_check() {
    for (const arg of arguments) {
        arg.delete();
    }
    if (liba.do_leak_check) {
        liba.do_leak_check();
    }
}
console.log("version", liba.VERSION);
console.log("major", liba.version.MAJOR);
console.log("minor", liba.version.MINOR);
console.log("patch", liba.version.PATCH);
console.log("tweak", liba.version.TWEAK);
var v = new liba.version();
console.log(v.toString());
do_leak_check(v);
var v = new liba.version(1);
console.log(v.toString());
do_leak_check(v);
var v = new liba.version(1, 2);
console.log(v.toString());
do_leak_check(v);
var v = new liba.version(1, 2, 3);
console.log(v.major, v.minor, v.third, v.alpha, v.extra);
console.log(v.parse("3.2.1").toString());
console.log(liba.version.check(0, 0, 0));
var w = new liba.version(1, 2, 0, 0);
console.log(v.cmp(w));
v.major = v.minor = v.third = v.extra = 0;
v.alpha = v.alpha
do_leak_check(v, w);
