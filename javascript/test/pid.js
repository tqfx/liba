#!/usr/bin/env node
var liba = require("../liba")

var ctx = new liba.pid()
ctx.kpid(10, 0.1, 1).zero()
console.log(ctx.iter(1, 0))
ctx.delete()

var ctx = new liba.pid(-10, 10)
ctx.kpid(10, 0.1, 1).zero()
console.log(ctx.iter(1, 0))
ctx.delete()

var ctx = new liba.pid(-10, 10, 10)
ctx.kpid(10, 0.1, 1).zero()
console.log(ctx.iter(1, 0))
ctx.delete()
