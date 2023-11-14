#!/usr/bin/env node
var Module = require("../liba.js")

var ctx = new Module.pid_neuron().zero()
ctx.wpid(1, 0, 0).kpid(10, 1, 0.1, 1)
console.log(ctx.iter(10, 0))
ctx.delete()

var ctx = new Module.pid_neuron(-10, 10).zero()
ctx.wpid(1, 0, 0).kpid(10, 1, 0.1, 1)
console.log(ctx.iter(10, 0))
ctx.delete()
