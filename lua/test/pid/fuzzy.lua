#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "../?.lua;" .. package.path
local test = require("test")
local a = require("liba")
local NL = -3
local NM = -2
local NS = -1
local ZO = 0
local PS = 1
local PM = 2
local PL = 3
local me = {
    -- LuaFormatter off
    { a.mf.TRI, NL, NL, NM },
    { a.mf.TRI, NL, NM, NS },
    { a.mf.TRI, NM, NS, ZO },
    { a.mf.TRI, NS, ZO, PS },
    { a.mf.TRI, ZO, PS, PM },
    { a.mf.TRI, PS, PM, PL },
    { a.mf.TRI, PM, PL, PL },
    -- LuaFormatter on
}
local NL = -6
local NM = -4
local NS = -3
local ZO = 0
local PS = 2
local PM = 4
local PL = 6
local mec = {
    -- LuaFormatter off
    { a.mf.TRI, NL, NL, NM },
    { a.mf.TRI, NL, NM, NS },
    { a.mf.TRI, NM, NS, ZO },
    { a.mf.TRI, NS, ZO, PS },
    { a.mf.TRI, ZO, PS, PM },
    { a.mf.TRI, PS, PM, PL },
    { a.mf.TRI, PM, PL, PL },
    -- LuaFormatter on
}
local NL = -15
local NM = -10
local NS = -5
local ZO = 0
local PS = 5
local PM = 10
local PL = 15
local mkp = {
    -- LuaFormatter off
    { NL, NL, NM, NM, NS, ZO, ZO },
    { NL, NL, NM, NS, NS, ZO, PS },
    { NM, NM, NM, NS, ZO, PS, PS },
    { NM, NM, NS, ZO, PS, PM, PM },
    { NS, NS, ZO, PS, PS, PM, PM },
    { NS, ZO, PS, PM, PM, PM, PL },
    { ZO, ZO, PM, PM, PM, PL, PL },
    -- LuaFormatter on
}
local NL = -3
local NM = -2
local NS = -1
local ZO = 0
local PS = 1
local PM = 2
local PL = 3
local mki = {
    -- LuaFormatter off
    { PL, PL, PM, PM, PS, ZO, ZO },
    { PL, PL, PM, PS, PS, ZO, ZO },
    { PL, PM, PS, PS, ZO, NS, NS },
    { PM, PM, PS, ZO, NS, NM, NM },
    { PM, PS, ZO, NS, NS, NM, NL },
    { ZO, ZO, NS, NS, NM, NL, NL },
    { ZO, ZO, NS, NM, NM, NL, NL },
    -- LuaFormatter on
}
local mkd = {
    -- LuaFormatter off
    { NS, PS, PL, PL, PL, PM, NS },
    { NS, PS, PL, PM, PM, PS, ZO },
    { ZO, PS, PM, PM, PS, PS, ZO },
    { ZO, PS, PS, PS, PS, PS, ZO },
    { ZO, ZO, ZO, ZO, ZO, ZO, ZO },
    { NL, NS, NS, NS, NS, NS, NL },
    { NL, NM, NM, NM, NS, NS, NL },
    -- LuaFormatter on
}
test:dir(getmetatable(a.pid.fuzzy))
assert(a.pid.fuzzy.new())
assert(a.pid.fuzzy.new(-10, 10))
assert(a.pid.fuzzy.new(-10, 10, 10))
assert(a.pid.fuzzy.new(10, 0.1, 1, -10, 10))
assert(a.pid.fuzzy.new(10, 0.1, 1, -10, 10, 10))
ctx = a.pid.fuzzy.new(-10, 10)
assert(type(a.pid.fuzzy.rule(ctx, me, mec, mkp, mki, mkd)) == "userdata")
assert(type(a.pid.fuzzy:rule(ctx, me, mec, mkp, mki, mkd)) == "userdata")
assert(type(a.pid.fuzzy.kpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid.fuzzy:kpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid.fuzzy.buff(ctx, 2)) == "userdata")
assert(type(a.pid.fuzzy:buff(ctx, 2)) == "userdata")
assert(type(a.pid.fuzzy.iter(ctx, 1, 0)) == "number")
assert(type(a.pid.fuzzy:iter(ctx, 1, 0)) == "number")
assert(type(a.pid.fuzzy.zero(ctx)) == "userdata")
assert(type(a.pid.fuzzy:zero(ctx)) == "userdata")
test:dir(getmetatable(ctx))
ctx = a.pid:fuzzy(-10, 10, 10)
ctx:rule(me, mec, mkp, mki, mkd)
ctx:kpid(3, 2, 1):buff(2)
assert(type(ctx(1, 0)) == "number")
assert(type(ctx.kp) == "number")
assert(type(ctx.ki) == "number")
assert(type(ctx.kd) == "number")
assert(type(ctx.summax) == "number")
assert(type(ctx.outmax) == "number")
assert(type(ctx.outmin) == "number")
assert(type(ctx.out) == "number")
assert(type(ctx.fdb) == "number")
assert(type(ctx.err) == "number")
assert(type(ctx.col) == "number")
assert(type(ctx.buf) == "number")
assert(ctx.mode == a.pid.POS)
ctx.mode = a.pid.OFF
ctx.buf = ctx.col
ctx.summax = 5
ctx.dt = 0.1
ctx.kp = 3
ctx.ki = 2
ctx.kd = 1
