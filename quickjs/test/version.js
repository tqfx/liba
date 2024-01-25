import * as a from "liba.so";
var v000 = new a.version()
var v100 = new a.version(1)
var v010 = new a.version(0, 1)
var v001 = new a.version(0, 0, 1)
function assert(expr, info) {
    if (!expr) {
        throw Error("assertion failed: " + info);
    }
}
assert(v000.lt(v010))
assert(v001.gt(v000))
assert(v000.le(v000))
assert(v000.ge(v000))
assert(v000.eq(v000))
assert(v000.ne(v100))
assert(v100.major)
assert(v010.minor)
assert(v001.third)
assert(v000.extra == 0)
console.log(a.version.MAJOR)
console.log(a.version.MINOR)
console.log(a.version.PATCH)
console.log(a.version.check())
