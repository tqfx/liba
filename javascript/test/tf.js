#!/usr/bin/env node
var Module = require("../liba.js")

var ctx = new Module.tf([6.59492796e-05, 6.54019884e-05], [1.0, -1.97530991, 0.97530991])
console.log(ctx.iter(1.0), ctx.iter(1.0))
console.log(ctx.num(), ctx.input())
console.log(ctx.den(), ctx.output())
