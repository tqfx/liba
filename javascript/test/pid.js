#!/usr/bin/env node
var Module = require("../liba.js")

var ctx = new Module.pid()
ctx.kpid(10, 0.1, 1).zero()
console.log(ctx.iter(1, 0))
ctx.delete()

var ctx = new Module.pid(-10, 10)
ctx.kpid(10, 0.1, 1).zero()
console.log(ctx.iter(1, 0))
ctx.delete()

var ctx = new Module.pid(-10, 10, 10)
ctx.kpid(10, 0.1, 1).zero()
console.log(ctx.iter(1, 0))
ctx.delete()
