#!/usr/bin/env node
var liba = require("../liba")
var ctx = new liba.polytraj5(0, 1, 0, 1, 0, 1, 0, 1)
console.log(ctx.q)
console.log(ctx.v)
console.log(ctx.a)
console.log(ctx.pos(0.5), ctx.vel(0.5), ctx.acc(0.5))
ctx.delete()
