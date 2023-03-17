#!/usr/bin/env node
var Module = require("./liba.js")

var ctx = new Module.pid(1, -10, 10)
ctx.kpid(10, 0.1, 1)
console.log(ctx.proc(1, 0))
ctx.delete()

var ctx = new Module.pid(1, -10, 10, 10)
ctx.kpid(10, 0.1, 1)
console.log(ctx.proc(1, 0))
ctx.delete()

var ctx = new Module.pid(1, 10, 0.1, 1, -10, 10)
console.log(ctx.proc(1, 0))
ctx.delete()

var ctx = new Module.pid(1, 10, 0.1, 1, -10, 10, 10)
console.log(ctx.proc(1, 0))
ctx.delete()
