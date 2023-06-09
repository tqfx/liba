#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
local NB = -3
local NM = -2
local NS = -1
local ZO = 0
local PS = 1
local PM = 2
local PB = 3
local me = {
  -- LuaFormatter off
  { a.mf.TRI, NB, NB, NM },
  { a.mf.TRI, NB, NM, NS },
  { a.mf.TRI, NM, NS, ZO },
  { a.mf.TRI, NS, ZO, PS },
  { a.mf.TRI, ZO, PS, PM },
  { a.mf.TRI, PS, PM, PB },
  { a.mf.TRI, PM, PB, PB },
  -- LuaFormatter on
}
local NB = -6
local NM = -4
local NS = -3
local ZO = 0
local PS = 2
local PM = 4
local PB = 6
local mec = {
  -- LuaFormatter off
  { a.mf.TRI, NB, NB, NM },
  { a.mf.TRI, NB, NM, NS },
  { a.mf.TRI, NM, NS, ZO },
  { a.mf.TRI, NS, ZO, PS },
  { a.mf.TRI, ZO, PS, PM },
  { a.mf.TRI, PS, PM, PB },
  { a.mf.TRI, PM, PB, PB },
  -- LuaFormatter on
}
local NB = -15
local NM = -10
local NS = -5
local ZO = 0
local PS = 5
local PM = 10
local PB = 15
local mkp = {
  -- LuaFormatter off
  { NB, NB, NM, NM, NS, ZO, ZO },
  { NB, NB, NM, NS, NS, ZO, PS },
  { NM, NM, NM, NS, ZO, PS, PS },
  { NM, NM, NS, ZO, PS, PM, PM },
  { NS, NS, ZO, PS, PS, PM, PM },
  { NS, ZO, PS, PM, PM, PM, PB },
  { ZO, ZO, PM, PM, PM, PB, PB },
  -- LuaFormatter on
}
local NB = -3
local NM = -2
local NS = -1
local ZO = 0
local PS = 1
local PM = 2
local PB = 3
local mki = {
  -- LuaFormatter off
  { PB, PB, PM, PM, PS, ZO, ZO },
  { PB, PB, PM, PS, PS, ZO, ZO },
  { PB, PM, PS, PS, ZO, NS, NS },
  { PM, PM, PS, ZO, NS, NM, NM },
  { PM, PS, ZO, NS, NS, NM, NB },
  { ZO, ZO, NS, NS, NM, NB, NB },
  { ZO, ZO, NS, NM, NM, NB, NB },
  -- LuaFormatter on
}
local mkd = {
  -- LuaFormatter off
  { NS, PS, PB, PB, PB, PM, NS },
  { NS, PS, PB, PM, PM, PS, ZO },
  { ZO, PS, PM, PM, PS, PS, ZO },
  { ZO, PS, PS, PS, PS, PS, ZO },
  { ZO, ZO, ZO, ZO, ZO, ZO, ZO },
  { NB, NS, NS, NS, NS, NS, NB },
  { NB, NM, NM, NM, NS, NS, NB },
  -- LuaFormatter on
}
test:r(getmetatable(a.pid_fuzzy))
ctx = a.pid_fuzzy.new(2, 1, me, mec, mkp, mki, mkd, -10, 10)
assert(type(a.pid_fuzzy.base(ctx, me, mec, mkp, mki, mkd)) == "userdata")
assert(type(a.pid_fuzzy:base(ctx, me, mec, mkp, mki, mkd)) == "userdata")
assert(type(a.pid_fuzzy.kpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid_fuzzy:kpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid_fuzzy.iter(ctx, 1, 0)) == "number")
assert(type(a.pid_fuzzy:iter(ctx, 1, 0)) == "number")
assert(type(a.pid_fuzzy.zero(ctx)) == "userdata")
assert(type(a.pid_fuzzy:zero(ctx)) == "userdata")
assert(type(a.pid_fuzzy.pos(ctx, 10)) == "userdata")
assert(type(a.pid_fuzzy:pos(ctx, 10)) == "userdata")
assert(type(a.pid_fuzzy.inc(ctx)) == "userdata")
assert(type(a.pid_fuzzy:inc(ctx)) == "userdata")
assert(type(a.pid_fuzzy.off(ctx)) == "userdata")
assert(type(a.pid_fuzzy:off(ctx)) == "userdata")
test:r(getmetatable(ctx))
ctx = a:pid_fuzzy(2, 1, me, mec, mkp, mki, mkd, -10, 10)
ctx:kpid(3, 2, 1):off():inc():pos(10)
assert(type(ctx(1, 0)) == "number")
assert(type(ctx.outmin) == "number")
assert(type(ctx.outmax) == "number")
assert(type(ctx.summax) == "number")
assert(type(ctx.dt) == "number")
assert(type(ctx.kp) == "number")
assert(type(ctx.ki) == "number")
assert(type(ctx.kd) == "number")
assert(type(ctx.col) == "number")
assert(type(ctx.buf) == "number")
assert(type(ctx.out) == "number")
assert(type(ctx.fdb) == "number")
assert(type(ctx.err) == "number")
assert(ctx.mode == a.pid.POS)
ctx.mode = a.pid.OFF
ctx.buf = ctx.col
ctx.summax = 5
ctx.dt = 0.1
ctx.kp = 3
ctx.ki = 2
ctx.kd = 1
