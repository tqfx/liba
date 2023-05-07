#!/usr/bin/env node
var Module = require("../liba.js")
var NB = -3
var NM = -2
var NS = -1
var ZO = 0
var PS = +1
var PM = +2
var PB = +3
var me = [
    [Module.MF_TRI, NB, NB, NM],
    [Module.MF_TRI, NB, NM, NS],
    [Module.MF_TRI, NM, NS, ZO],
    [Module.MF_TRI, NS, ZO, PS],
    [Module.MF_TRI, ZO, PS, PM],
    [Module.MF_TRI, PS, PM, PB],
    [Module.MF_TRI, PM, PB, PB],
    [Module.MF_NUL, ZO, ZO, ZO],
]
var NB = -6
var NM = -4
var NS = -2
var ZO = 0
var PS = +2
var PM = +4
var PB = +6
var mec = [
    [Module.MF_TRI, NB, NB, NM],
    [Module.MF_TRI, NB, NM, NS],
    [Module.MF_TRI, NM, NS, ZO],
    [Module.MF_TRI, NS, ZO, PS],
    [Module.MF_TRI, ZO, PS, PM],
    [Module.MF_TRI, PS, PM, PB],
    [Module.MF_TRI, PM, PB, PB],
    [Module.MF_NUL, ZO, ZO, ZO],
]
var NB = -15
var NM = -10
var NS = -5
var ZO = 0
var PS = +5
var PM = +10
var PB = +15
var mkp = [
    [NB, NB, NM, NM, NS, ZO, ZO],
    [NB, NB, NM, NS, NS, ZO, PS],
    [NM, NM, NM, NS, ZO, PS, PS],
    [NM, NM, NS, ZO, PS, PM, PM],
    [NS, NS, ZO, PS, PS, PM, PM],
    [NS, ZO, PS, PM, PM, PM, PB],
    [ZO, ZO, PM, PM, PM, PB, PB],
]
var NB = -3
var NM = -2
var NS = -1
var ZO = 0
var PS = +1
var PM = +2
var PB = +3
var mki = [
    [PB, PB, PM, PM, PS, ZO, ZO],
    [PB, PB, PM, PS, PS, ZO, ZO],
    [PB, PM, PS, PS, ZO, NS, NS],
    [PM, PM, PS, ZO, NS, NM, NM],
    [PM, PS, ZO, NS, NS, NM, NB],
    [ZO, ZO, NS, NS, NM, NB, NB],
    [ZO, ZO, NS, NM, NM, NB, NB],
]
var mkd = [
    [NS, PS, PB, PB, PB, PM, NS],
    [NS, PS, PB, PM, PM, PS, ZO],
    [ZO, PS, PM, PM, PS, PS, ZO],
    [ZO, PS, PS, PS, PS, PS, ZO],
    [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
    [NB, NS, NS, NS, NS, NS, NB],
    [NB, NM, NM, NM, NS, NS, NB],
]

var ctx = new Module.fpid(2, 1, me, mec, mkp, mki, mkd, -10, 10)
ctx.kpid(10, 0.1, 1)
console.log(ctx.iter(10, 0))
ctx.delete()

var ctx = new Module.fpid(2, 1, me, mec, mkp, mki, mkd, -10, 10, 10)
ctx.kpid(10, 0.1, 1)
console.log(ctx.iter(10, 0))
ctx.delete()
