#!/usr/bin/env node
var liba = require("../liba")

var ctx = new liba.polytrack3(0, 1, 0, 1, 0, 1)
console.log(ctx.out(0.5))
console.log(ctx.pos(0.5))
console.log(ctx.vel(0.5))
console.log(ctx.acc(0.5))
ctx.delete()

var ctx = new liba.polytrack5(0, 1, 0, 1, 0, 1, 0, 1)
console.log(ctx.out(0.5))
console.log(ctx.pos(0.5))
console.log(ctx.vel(0.5))
console.log(ctx.acc(0.5))
ctx.delete()

var ctx = new liba.polytrack7(0, 1, 0, 1, 0, 1, 0, 1, 0, 1)
console.log(ctx.out(0.5))
console.log(ctx.pos(0.5))
console.log(ctx.vel(0.5))
console.log(ctx.acc(0.5))
console.log(ctx.jer(0.5))
ctx.delete()
