import * as a from "liba.so";

var NL = -3
var NM = -2
var NS = -1
var ZO = 0
var PS = +1
var PM = +2
var PL = +3
var me = [
    [a.mf.TRI, NL, NL, NM],
    [a.mf.TRI, NL, NM, NS],
    [a.mf.TRI, NM, NS, ZO],
    [a.mf.TRI, NS, ZO, PS],
    [a.mf.TRI, ZO, PS, PM],
    [a.mf.TRI, PS, PM, PL],
    [a.mf.TRI, PM, PL, PL],
]
var NL = -6
var NM = -4
var NS = -2
var ZO = 0
var PS = +2
var PM = +4
var PL = +6
var mec = [
    [a.mf.TRI, NL, NL, NM],
    [a.mf.TRI, NL, NM, NS],
    [a.mf.TRI, NM, NS, ZO],
    [a.mf.TRI, NS, ZO, PS],
    [a.mf.TRI, ZO, PS, PM],
    [a.mf.TRI, PS, PM, PL],
    [a.mf.TRI, PM, PL, PL],
]
var NL = -15
var NM = -10
var NS = -5
var ZO = 0
var PS = +5
var PM = +10
var PL = +15
var mkp = [
    [NL, NL, NM, NM, NS, ZO, ZO],
    [NL, NL, NM, NS, NS, ZO, PS],
    [NM, NM, NM, NS, ZO, PS, PS],
    [NM, NM, NS, ZO, PS, PM, PM],
    [NS, NS, ZO, PS, PS, PM, PM],
    [NS, ZO, PS, PM, PM, PM, PL],
    [ZO, ZO, PM, PM, PM, PL, PL],
]
var NL = -3
var NM = -2
var NS = -1
var ZO = 0
var PS = +1
var PM = +2
var PL = +3
var mki = [
    [PL, PL, PM, PM, PS, ZO, ZO],
    [PL, PL, PM, PS, PS, ZO, ZO],
    [PL, PM, PS, PS, ZO, NS, NS],
    [PM, PM, PS, ZO, NS, NM, NM],
    [PM, PS, ZO, NS, NS, NM, NL],
    [ZO, ZO, NS, NS, NM, NL, NL],
    [ZO, ZO, NS, NM, NM, NL, NL],
]
var mkd = [
    [NS, PS, PL, PL, PL, PM, NS],
    [NS, PS, PL, PM, PM, PS, ZO],
    [ZO, PS, PM, PM, PS, PS, ZO],
    [ZO, PS, PS, PS, PS, PS, ZO],
    [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
    [NL, NS, NS, NS, NS, NS, NL],
    [NL, NM, NM, NM, NS, NS, NL],
]

var ctx = new a.pid_fuzzy()
ctx.rule(me, mec, mkp, mki, mkd)
ctx.set_block(2)
ctx.kpid(10, 0.1, 1)
ctx.op(a.pid_fuzzy.EQU)
console.log(ctx.run(10, 0))
ctx.zero()
console.log(ctx.pos(10, 0))
ctx.zero()
console.log(ctx.inc(10, 0))
ctx.zero()
ctx.kp = ctx.kp
ctx.ki = ctx.ki
ctx.kd = ctx.kd
ctx.summax = ctx.summax
ctx.summin = ctx.summin
ctx.sum
ctx.outmax = ctx.outmax
ctx.outmin = ctx.outmin
ctx.out
ctx.fdb
ctx.err
ctx.order
ctx.block = ctx.block
