#!/usr/bin/env node
var liba = require("../liba")

var ctx = new liba.pid_neuron().zero()
ctx.wpid(1, 0, 0).kpid(10, 1, 0.1, 1)
console.log(ctx.iter(10, 0))
ctx.delete()

var ctx = new liba.pid_neuron(-10, 10).zero()
ctx.wpid(1, 0, 0).kpid(10, 1, 0.1, 1)
console.log(ctx.iter(10, 0))
ctx.delete()
