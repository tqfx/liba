import * as a from "liba.so";
var num = [6.59492796e-05, 6.54019884e-05]
var den = [-1.97530991, 0.97530991]
var ctx = new a.tf(num, den)
ctx.iter(1)
console.log(ctx.num)
console.log(ctx.den)
console.log(ctx.input)
console.log(ctx.output)
ctx.num = [1]
ctx.den = [2]
console.log(ctx.num)
console.log(ctx.den)
console.log(ctx.input)
console.log(ctx.output)
ctx.zero()
