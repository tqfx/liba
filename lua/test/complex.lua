#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test:r(a.complex)
x = a.complex(1, 2)
y = a.complex.new(2, 1)
test:r(getmetatable(x(0, 0)))
z = a.complex.polar(1, math.pi)
test:p(z, z:conj(), z.r, z.theta)
z.real, z.imag = math.pi, math.pi
test:p("- " .. tostring(x) .. " = " .. tostring(-x))
test:p(tostring(x) .. " + " .. tostring(y) .. " = " .. tostring(x + y))
test:p(tostring(x) .. " - " .. tostring(y) .. " = " .. tostring(x - y))
test:p(tostring(x) .. " * " .. tostring(y) .. " = " .. tostring(x * y))
test:p(tostring(x) .. " / " .. tostring(y) .. " = " .. tostring(x / y))
test:p("- " .. tostring(x) .. " = " .. tostring(x:unm()))
test:p(tostring(x) .. " + " .. tostring(y) .. " = " .. tostring(x:add(y)))
test:p(tostring(x) .. " - " .. tostring(y) .. " = " .. tostring(x:sub(y)))
test:p(tostring(x) .. " * " .. tostring(y) .. " = " .. tostring(x:mul(y)))
test:p(tostring(x) .. " / " .. tostring(y) .. " = " .. tostring(x:div(y)))
