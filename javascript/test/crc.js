#!/usr/bin/env node
var liba = require("../liba")
function assert(b, str) {
    if (!b) {
        throw Error("assertion failed: " + str);
    }
}
var text = "0123456789"

var crc = new liba.crc8(0x07)
assert(crc.eval(text, 0) == 0x45)
var crc = new liba.crc8(0x31, true)
assert(crc.eval(text, 0) == 0x75)

var crc = new liba.crc16(0x1021)
assert(crc.eval(text, 0) == 0x9C58)
var crc = new liba.crc16(0x8005, true)
assert(crc.eval(text, 0) == 0x443D)

var crc = new liba.crc32(0x1EDC6F41)
assert(crc.eval(text, 0) == 0x512B456E)
var crc = new liba.crc32(0x04C11DB7, true)
assert(crc.eval(text, 0) == 0x450EAFB0)
