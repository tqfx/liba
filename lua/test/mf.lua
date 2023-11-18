#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.mf))

a.mf.gauss(0, 0, 0)
a.mf.gbell(0, 0, 0, 0)
a.mf.sig(0, 0, 0)
a.mf.trap(0, 0, 0, 0, 0)
a.mf.tri(0, 0, 0, 0)
a.mf.z(0, 0, 0)

---@diagnostic disable: param-type-mismatch, redundant-parameter
a.mf:gauss(0, 0, 0)
a.mf:gbell(0, 0, 0, 0)
a.mf:sig(0, 0, 0)
a.mf:trap(0, 0, 0, 0, 0)
a.mf:tri(0, 0, 0, 0)
a.mf:z(0, 0, 0)
---@diagnostic enable: param-type-mismatch, redundant-parameter

a.mf(a.mf.GAUSS, 0, 0, 0)
a.mf(a.mf.GBELL, 0, 0, 0, 0)
a.mf(a.mf.SIG, 0, 0, 0)
a.mf(a.mf.TRAP, 0, 0, 0, 0, 0)
a.mf(a.mf.TRI, 0, 0, 0, 0)
a.mf(a.mf.Z, 0, 0, 0)

a:mf(a.mf.GAUSS, 0, 0, 0)
a:mf(a.mf.GBELL, 0, 0, 0, 0)
a:mf(a.mf.SIG, 0, 0, 0)
a.mf(a.mf.TRAP, 0, 0, 0, 0, 0)
a:mf(a.mf.TRI, 0, 0, 0, 0)
a:mf(a.mf.Z, 0, 0, 0)
