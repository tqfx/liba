#!/usr/bin/env node
var liba = require("../liba");
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
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
var text = "0123456789";
var crc = new liba.crc8(0x07);
assert(crc.eval(text, 0) == 0x45);
assert(crc.eval(crc.pack(text, 0), 0) == 0);
do_leak_check(crc);
var crc = new liba.crc8(0x31, true);
assert(crc.eval(text, 0) == 0x75);
assert(crc.eval(crc.pack(text, 0), 0) == 0);
do_leak_check(crc);
var crc = new liba.crc16(0x1021);
assert(crc.eval(text, 0) == 0x9C58);
assert(crc.eval(crc.pack(text, 0), 0) == 0);
do_leak_check(crc);
var crc = new liba.crc16(0x8005, true);
assert(crc.eval(text, 0) == 0x443D);
assert(crc.eval(crc.pack(text, 0), 0) == 0);
do_leak_check(crc);
var crc = new liba.crc32(0x1EDC6F41);
assert(crc.eval(text, 0) == 0x512B456E);
assert(crc.eval(crc.pack(text, 0), 0) == 0);
do_leak_check(crc);
var crc = new liba.crc32(0x04C11DB7, true);
assert(crc.eval(text, 0) == 0x450EAFB0);
assert(crc.eval(crc.pack(text, 0), 0) == 0);
do_leak_check(crc);
if (liba.crc64) {
    var crc = new liba.crc64(0x000000000000001Bn);
    assert(crc.eval(text, 0n) == 0xE4FFBEA588AFC790n);
    assert(crc.eval(crc.pack(text, 0n), 0n) == 0n);
    do_leak_check(crc);
    var crc = new liba.crc64(0x42F0E1EBA9EA3693n, true);
    assert(crc.eval(text, 0n) == 0xDA60676A5CDE0008n);
    assert(crc.eval(crc.pack(text, 0n), 0n) == 0n);
    do_leak_check(crc);
}
