#!/usr/bin/env node
var Module = require("../liba.js")

var ctx = new Module.polytrack3(0, 1, 0, 1, 0, 1)
console.log(ctx.out(0.5))
console.log(ctx.pos(0.5))
console.log(ctx.vel(0.5))
console.log(ctx.acc(0.5))
ctx.delete()

var ctx = new Module.polytrack5(0, 1, 0, 1, 0, 1, 0, 1)
console.log(ctx.out(0.5))
console.log(ctx.pos(0.5))
console.log(ctx.vel(0.5))
console.log(ctx.acc(0.5))
ctx.delete()

var ctx = new Module.polytrack7(0, 1, 0, 1, 0, 1, 0, 1, 0, 1)
console.log(ctx.out(0.5))
console.log(ctx.pos(0.5))
console.log(ctx.vel(0.5))
console.log(ctx.acc(0.5))
console.log(ctx.jer(0.5))
ctx.delete()
