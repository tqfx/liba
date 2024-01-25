import * as a from "liba.so";
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
    }
}
var text = "0123456789"
var ctx = new a.crc8(0x07)
assert(ctx.eval(text) == 0x45)
assert(ctx.eval(ctx.pack(text)) == 0)
var ctx = new a.crc8(0x31, true)
assert(ctx.eval(text) == 0x75)
assert(ctx.eval(ctx.pack(text)) == 0)
var ctx = new a.crc16(0x1021)
assert(ctx.eval(text) == 0x9C58)
assert(ctx.eval(ctx.pack(text)) == 0)
var ctx = new a.crc16(0x8005, true)
assert(ctx.eval(text) == 0x443D)
assert(ctx.eval(ctx.pack(text)) == 0)
var ctx = new a.crc32(0x1EDC6F41)
assert(ctx.eval(text) == 0x512B456E)
assert(ctx.eval(ctx.pack(text)) == 0)
var ctx = new a.crc32(0x04C11DB7, true)
assert(ctx.eval(text) == 0x450EAFB0)
assert(ctx.eval(ctx.pack(text)) == 0)
var ctx = new a.crc64(0x000000000000001Bn)
assert(ctx.eval(text) == 0xE4FFBEA588AFC790n)
assert(ctx.eval(ctx.pack(text)) == 0)
var ctx = new a.crc64(0x42F0E1EBA9EA3693n, true)
assert(ctx.eval(text) == 0xDA60676A5CDE0008n)
assert(ctx.eval(ctx.pack(text)) == 0)
