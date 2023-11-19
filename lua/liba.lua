---@meta liba
local liba = {}

---@param str string
---@param ... string
---@return integer
function liba.hash_bkdr(str, ...) end

---@param x number
---@param ... number
---@return number ...
function liba.rsqrt(x, ...) end

---@class a.complex
---@field __name string
---@field __index table
---@field real number
---@field imag number
---@field r number
---@field theta number
---@operator unm(a.complex): a.complex
---@operator add(a.complex): a.complex
---@operator sub(a.complex): a.complex
---@operator mul(a.complex): a.complex
---@operator div(a.complex): a.complex
---@operator pow(a.complex): a.complex
---@operator len(a.complex): number
---@overload fun(real: number, imag: number): a.complex
local complex = setmetatable({}, {
    __call = liba.complex.new
})
liba.complex = setmetatable({}, {
    __call = liba.complex.new
})

---@param real number
---@param imag number
---@return a.complex
function liba.complex.new(real, imag) end

---@param r number
---@param theta number
---@return a.complex
function liba.complex.polar(r, theta) end

---@param r number
---@param theta number
---@return a.complex
function complex:polar(r, theta) end

---@param z a.complex|number|string
---@return number
function liba.complex.logabs(z) end

---@return number
function complex:logabs() end

---@param z a.complex|number|string
---@return number
function liba.complex.abs2(z) end

---@return number
function complex:abs2() end

---@param z a.complex|number|string
---@return number
function liba.complex.abs(z) end

---@return number
function complex:abs() end

---@param z a.complex|number|string
---@return number
function liba.complex.arg(z) end

---@return number
function complex:arg() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.conj(z) end

---@return a.complex
function complex:conj() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.unm(z) end

---@return a.complex
function complex:unm() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.inv(z) end

---@return a.complex
function complex:inv() end

---@param x a.complex|number|string
---@param y a.complex|number|string
---@return a.complex
function liba.complex.add(x, y) end

---@param z a.complex|number|string
---@return a.complex
function complex:add(z) end

---@param x a.complex|number|string
---@param y a.complex|number|string
---@return a.complex
function liba.complex.sub(x, y) end

---@param z a.complex|number|string
---@return a.complex
function complex:sub(z) end

---@param x a.complex|number|string
---@param y a.complex|number|string
---@return a.complex
function liba.complex.mul(x, y) end

---@param z a.complex|number|string
---@return a.complex
function complex:mul(z) end

---@param x a.complex|number|string
---@param y a.complex|number|string
---@return a.complex
function liba.complex.div(x, y) end

---@param z a.complex|number|string
---@return a.complex
function complex:div(z) end

---@param z a.complex|number|string
---@param a a.complex|number|string
---@return a.complex
function liba.complex.pow(z, a) end

---@param a a.complex|number|string
---@return a.complex
function complex:pow(a) end

---@param z a.complex|number|string
---@param b a.complex|number|string
---@return a.complex
function liba.complex.logb(z, b) end

---@param b a.complex
---@return a.complex
function complex:logb(b) end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.exp(z) end

---@return a.complex
function complex:exp() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.log(z) end

---@return a.complex
function complex:log() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.sqrt(z) end

---@return a.complex
function complex:sqrt() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.log2(z) end

---@return a.complex
function complex:log2() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.log10(z) end

---@return a.complex
function complex:log10() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.sin(z) end

---@return a.complex
function complex:sin() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.cos(z) end

---@return a.complex
function complex:cos() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.tan(z) end

---@return a.complex
function complex:tan() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.sec(z) end

---@return a.complex
function complex:sec() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.csc(z) end

---@return a.complex
function complex:csc() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.cot(z) end

---@return a.complex
function complex:cot() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.asin(z) end

---@return a.complex
function complex:asin() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.acos(z) end

---@return a.complex
function complex:acos() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.atan(z) end

---@return a.complex
function complex:atan() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.asec(z) end

---@return a.complex
function complex:asec() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.acsc(z) end

---@return a.complex
function complex:acsc() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.acot(z) end

---@return a.complex
function complex:acot() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.sinh(z) end

---@return a.complex
function complex:sinh() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.cosh(z) end

---@return a.complex
function complex:cosh() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.tanh(z) end

---@return a.complex
function complex:tanh() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.sech(z) end

---@return a.complex
function complex:sech() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.csch(z) end

---@return a.complex
function complex:csch() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.coth(z) end

---@return a.complex
function complex:coth() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.asinh(z) end

---@return a.complex
function complex:asinh() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.acosh(z) end

---@return a.complex
function complex:acosh() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.atanh(z) end

---@return a.complex
function complex:atanh() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.asech(z) end

---@return a.complex
function complex:asech() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.acsch(z) end

---@return a.complex
function complex:acsch() end

---@param z a.complex|number|string
---@return a.complex
function liba.complex.acoth(z) end

---@return a.complex
function complex:acoth() end

liba.mf = {}

liba.mf.NUL = 0
---@param e integer
---@param x number
---@param ... number
function liba.mf.mf(e, x, ...) end

liba.mf.GAUSS = 1
---@param x number
---@param sigma number
---@param c number
---@return number
function liba.mf.gauss(x, sigma, c) end

liba.mf.GAUSS2 = 2
---@param x number
---@param sigma1 number
---@param c1 number
---@param sigma2 number
---@param c2 number
---@return number
function liba.mf.gauss2(x, sigma1, c1, sigma2, c2) end

liba.mf.GBELL = 3
---@param x number
---@param a number
---@param b number
---@param c number
---@return number
function liba.mf.gbell(x, a, b, c) end

liba.mf.SIG = 4
---@param x number
---@param a number
---@param c number
---@return number
function liba.mf.sig(x, a, c) end

liba.mf.DSIG = 5
---@param x number
---@param a1 number
---@param c1 number
---@param a2 number
---@param c2 number
---@return number
function liba.mf.dsig(x, a1, c1, a2, c2) end

liba.mf.PSIG = 6
---@param x number
---@param a1 number
---@param c1 number
---@param a2 number
---@param c2 number
---@return number
function liba.mf.psig(x, a1, c1, a2, c2) end

liba.mf.TRAP = 7
---@param x number
---@param a number
---@param b number
---@param c number
---@param d number
---@return number
function liba.mf.trap(x, a, b, c, d) end

liba.mf.TRI = 8
---@param x number
---@param a number
---@param b number
---@param c number
---@return number
function liba.mf.tri(x, a, b, c) end

liba.mf.LINS = 9
---@param x number
---@param a number
---@param b number
---@return number
function liba.mf.lins(x, a, b) end

liba.mf.LINZ = 10
---@param x number
---@param a number
---@param b number
---@return number
function liba.mf.linz(x, a, b) end

liba.mf.S = 11
---@param x number
---@param a number
---@param b number
---@return number
function liba.mf.s(x, a, b) end

liba.mf.Z = 12
---@param x number
---@param a number
---@param b number
---@return number
function liba.mf.z(x, a, b) end

liba.mf.PI = 13
---@param x number
---@param a number
---@param b number
---@param c number
---@param d number
---@return number
function liba.mf.pi(x, a, b, c, d) end

---@class a.pid
---@field __name string
---@field __index table
---@field kp number
---@field ki number
---@field kd number
---@field summax number
---@field outmax number
---@field outmin number
---@field out number
---@field fdb number
---@field err number
---@field mode integer
---@overload fun(set: number, fdb: number): number
local pid = setmetatable({}, {
    __call = liba.pid.iter
})
liba.pid = setmetatable({}, {
    __call = liba.pid.new
})
liba.pid.OFF = 0
liba.pid.POS = 1
liba.pid.INC = 2

---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid
---@overload fun(): a.pid
---@overload fun(min: number, max: number, sum?: number): a.pid
function liba.pid.new(kp, ki, kd, min, max, sum) end

---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid
---@overload fun(): a.pid
---@overload fun(min: number, max: number, sum?: number): a.pid
function pid.new(kp, ki, kd, min, max, sum) end

---@param ctx a.pid
---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid
---@overload fun(ctx: a.pid): a.pid
---@overload fun(ctx: a.pid, min: number, max: number, sum?: number): a.pid
function liba.pid.init(ctx, kp, ki, kd, min, max, sum) end

---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid
---@overload fun(): a.pid
---@overload fun(min: number, max: number, sum?: number): a.pid
function pid:init(kp, ki, kd, min, max, sum) end

---@param ctx a.pid
---@param kp number
---@param ki number
---@param kd number
---@return a.pid
function liba.pid.kpid(ctx, kp, ki, kd) end

---@param kp number
---@param ki number
---@param kd number
---@return a.pid
function pid:kpid(kp, ki, kd) end

---@param ctx a.pid
---@param set number
---@param fdb number
---@return number
function liba.pid.iter(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid:iter(set, fdb) end

---@param ctx a.pid
---@return a.pid
function liba.pid.zero(ctx) end

---@return a.pid
function pid:zero() end

---@class a.pid.fuzzy
---@field __name string
---@field __index table
---@field kp number
---@field ki number
---@field kd number
---@field summax number
---@field outmax number
---@field outmin number
---@field out number
---@field fdb number
---@field err number
---@field mode integer
---@field order integer
---@overload fun(set: number, fdb: number): number
pid.fuzzy = setmetatable({}, {
    __call = liba.pid.fuzzy.iter
})
liba.pid.fuzzy = setmetatable({}, {
    __call = liba.pid.fuzzy.new
})

---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid.fuzzy
---@overload fun(): a.pid.fuzzy
---@overload fun(min: number, max: number, sum?: number): a.pid.fuzzy
function liba.pid.fuzzy.new(kp, ki, kd, min, max, sum) end

---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid.fuzzy
---@overload fun(): a.pid.fuzzy
---@overload fun(min: number, max: number, sum?: number): a.pid.fuzzy
function pid.fuzzy.new(kp, ki, kd, min, max, sum) end

---@param ctx a.pid.fuzzy
---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid.fuzzy
---@overload fun(ctx: a.pid.fuzzy): a.pid.fuzzy
---@overload fun(ctx: a.pid.fuzzy, min: number, max: number, sum?: number): a.pid.fuzzy
function liba.pid.fuzzy.init(ctx, kp, ki, kd, min, max, sum) end

---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid.fuzzy
---@overload fun(): a.pid.fuzzy
---@overload fun(min: number, max: number, sum?: number): a.pid.fuzzy
function pid.fuzzy:init(kp, ki, kd, min, max, sum) end

---@param ctx a.pid.fuzzy
---@param me table
---@param mec table
---@param mkp table
---@param mki table
---@param mkd table
---@return a.pid.fuzzy
function liba.pid.fuzzy.rule(ctx, me, mec, mkp, mki, mkd) end

---@param me table
---@param mec table
---@param mkp table
---@param mki table
---@param mkd table
---@return a.pid.fuzzy
function pid.fuzzy:rule(me, mec, mkp, mki, mkd) end

liba.pid.fuzzy.CAP = 1
liba.pid.fuzzy.CAP_ALGEBRA = 2
liba.pid.fuzzy.CAP_BOUNDED = 3
liba.pid.fuzzy.CUP = 4
liba.pid.fuzzy.CUP_ALGEBRA = 5
liba.pid.fuzzy.CUP_BOUNDED = 6
liba.pid.fuzzy.EQU = 0
---@param ctx a.pid.fuzzy
---@param op integer
---@return a.pid.fuzzy
function liba.pid.fuzzy.op(ctx, op) end

---@param op integer
---@return a.pid.fuzzy
function pid.fuzzy:op(op) end

---@param ctx a.pid.fuzzy
---@param joint integer
---@return a.pid.fuzzy
function liba.pid.fuzzy.joint(ctx, joint) end

---@param joint integer
---@return a.pid.fuzzy
function pid.fuzzy:joint(joint) end

---@param ctx a.pid.fuzzy
---@param kp number
---@param ki number
---@param kd number
---@return a.pid.fuzzy
function liba.pid.fuzzy.kpid(ctx, kp, ki, kd) end

---@param kp number
---@param ki number
---@param kd number
---@return a.pid.fuzzy
function pid.fuzzy:kpid(kp, ki, kd) end

---@param ctx a.pid.fuzzy
---@param set number
---@param fdb number
---@return number
function liba.pid.fuzzy.iter(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid.fuzzy:iter(set, fdb) end

---@param ctx a.pid.fuzzy
---@return a.pid.fuzzy
function liba.pid.fuzzy.zero(ctx) end

---@return a.pid.fuzzy
function pid.fuzzy:zero() end

---@class a.pid.neuron
---@field __name string
---@field __index table
---@field k number
---@field kp number
---@field ki number
---@field kd number
---@field wp number
---@field wi number
---@field wd number
---@field summax number
---@field outmax number
---@field outmin number
---@field out number
---@field fdb number
---@field err number
---@field ec number
---@field mode integer
---@overload fun(set: number, fdb: number): number
pid.neuron = setmetatable({}, {
    __call = liba.pid.neuron.iter
})
liba.pid.neuron = setmetatable({}, {
    __call = liba.pid.neuron.new
})

---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid.neuron
---@overload fun(): a.pid.neuron
---@overload fun(min: number, max: number, sum?: number): a.pid.neuron
function liba.pid.neuron.new(kp, ki, kd, min, max, sum) end

---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid.neuron
---@overload fun(): a.pid.neuron
---@overload fun(min: number, max: number, sum?: number): a.pid.neuron
function pid.neuron.new(kp, ki, kd, min, max, sum) end

---@param ctx a.pid.neuron
---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid.neuron
---@overload fun(ctx: a.pid.neuron): a.pid.neuron
---@overload fun(ctx: a.pid.neuron, min: number, max: number, sum?: number): a.pid.neuron
function liba.pid.neuron.init(ctx, kp, ki, kd, min, max, sum) end

---@param kp number
---@param ki number
---@param kd number
---@param min number
---@param max number
---@param sum? number
---@return a.pid.neuron
---@overload fun(): a.pid.neuron
---@overload fun(min: number, max: number, sum?: number): a.pid.neuron
function pid.neuron:init(kp, ki, kd, min, max, sum) end

---@param ctx a.pid.neuron
---@param k number
---@param kp number
---@param ki number
---@param kd number
---@return a.pid.neuron
function liba.pid.neuron.kpid(ctx, k, kp, ki, kd) end

---@param k number
---@param kp number
---@param ki number
---@param kd number
---@return a.pid.neuron
function pid.neuron:kpid(k, kp, ki, kd) end

---@param ctx a.pid.neuron
---@param wp number
---@param wi number
---@param wd number
---@return a.pid.neuron
function liba.pid.neuron.wpid(ctx, wp, wi, wd) end

---@param wp number
---@param wi number
---@param wd number
---@return a.pid.neuron
function pid.neuron:wpid(wp, wi, wd) end

---@param ctx a.pid.neuron
---@param set number
---@param fdb number
---@return number
function liba.pid.neuron.iter(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid.neuron:iter(set, fdb) end

---@param ctx a.pid.neuron
---@return a.pid.neuron
function liba.pid.neuron.zero(ctx) end

---@return a.pid.neuron
function pid.neuron:zero() end

---@class a.polytrack3
---@field __name string
---@field __index table
---@field k table
---@overload fun(dt: number): table
local polytrack3 = setmetatable({}, {
    __call = liba.polytrack3.out
})
liba.polytrack3 = setmetatable({}, {
    __call = liba.polytrack3.new
})

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@return a.polytrack3
---@overload fun(source: table, target: table): a.polytrack3
function liba.polytrack3.new(t0, t1, q0, q1, v0, v1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@return a.polytrack3
---@overload fun(source: table, target: table): a.polytrack3
function polytrack3.new(t0, t1, q0, q1, v0, v1) end

---@param ctx a.polytrack3
---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@return a.polytrack3
---@overload fun(ctx: a.polytrack3, source: table, target: table): a.polytrack3
function liba.polytrack3.gen(ctx, t0, t1, q0, q1, v0, v1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@return a.polytrack3
---@overload fun(source: table, target: table): a.polytrack3
function polytrack3:gen(t0, t1, q0, q1, v0, v1) end

---@param ctx a.polytrack3
---@param dt number
---@return table
function liba.polytrack3.out(ctx, dt) end

---@param dt number
---@return table
function polytrack3:out(dt) end

---@param ctx a.polytrack3
---@param dt number
---@return number
function liba.polytrack3.pos(ctx, dt) end

---@param dt number
---@return number
function polytrack3:pos(dt) end

---@param ctx a.polytrack3
---@param dt number
---@return number
function liba.polytrack3.vel(ctx, dt) end

---@param dt number
---@return number
function polytrack3:vel(dt) end

---@param ctx a.polytrack3
---@param dt number
---@return number
function liba.polytrack3.acc(ctx, dt) end

---@param dt number
---@return number
function polytrack3:acc(dt) end

---@class a.polytrack5
---@field __name string
---@field __index table
---@field k table
---@overload fun(dt: number): table
local polytrack5 = setmetatable({}, {
    __call = liba.polytrack5.out
})
liba.polytrack5 = setmetatable({}, {
    __call = liba.polytrack5.new
})

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@return a.polytrack5
---@overload fun(source: table, target: table): a.polytrack5
function liba.polytrack5.new(t0, t1, q0, q1, v0, v1, a0, a1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@return a.polytrack5
---@overload fun(source: table, target: table): a.polytrack5
function polytrack5.new(t0, t1, q0, q1, v0, v1, a0, a1) end

---@param ctx a.polytrack5
---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@return a.polytrack5
---@overload fun(ctx: a.polytrack5, source: table, target: table): a.polytrack5
function liba.polytrack5.gen(ctx, t0, t1, q0, q1, v0, v1, a0, a1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@return a.polytrack5
---@overload fun(source: table, target: table): a.polytrack5
function polytrack5:gen(t0, t1, q0, q1, v0, v1, a0, a1) end

---@param ctx a.polytrack5
---@param dt number
---@return table
function liba.polytrack5.out(ctx, dt) end

---@param dt number
---@return table
function polytrack5:out(dt) end

---@param ctx a.polytrack5
---@param dt number
---@return number
function liba.polytrack5.pos(ctx, dt) end

---@param dt number
---@return number
function polytrack5:pos(dt) end

---@param ctx a.polytrack5
---@param dt number
---@return number
function liba.polytrack5.vel(ctx, dt) end

---@param dt number
---@return number
function polytrack5:vel(dt) end

---@param ctx a.polytrack5
---@param dt number
---@return number
function liba.polytrack5.acc(ctx, dt) end

---@param dt number
---@return number
function polytrack5:acc(dt) end

---@class a.polytrack7
---@field __name string
---@field __index table
---@field k table
---@overload fun(dt: number): table
local polytrack7 = setmetatable({}, {
    __call = liba.polytrack7.out
})
liba.polytrack7 = setmetatable({}, {
    __call = liba.polytrack7.new
})

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@param j0? number
---@param j1? number
---@return a.polytrack7
---@overload fun(source: table, target: table): a.polytrack7
function liba.polytrack7.new(t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@param j0? number
---@param j1? number
---@return a.polytrack7
---@overload fun(source: table, target: table): a.polytrack7
function polytrack7.new(t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) end

---@param ctx a.polytrack7
---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@param j0? number
---@param j1? number
---@return a.polytrack7
---@overload fun(ctx: a.polytrack7, source: table, target: table): a.polytrack7
function liba.polytrack7.gen(ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@param j0? number
---@param j1? number
---@return a.polytrack7
---@overload fun(source: table, target: table): a.polytrack7
function polytrack7:gen(t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) end

---@param ctx a.polytrack7
---@param dt number
---@return table
function liba.polytrack7.out(ctx, dt) end

---@param dt number
---@return table
function polytrack7:out(dt) end

---@param ctx a.polytrack7
---@param dt number
---@return number
function liba.polytrack7.pos(ctx, dt) end

---@param dt number
---@return number
function polytrack7:pos(dt) end

---@param ctx a.polytrack7
---@param dt number
---@return number
function liba.polytrack7.vel(ctx, dt) end

---@param dt number
---@return number
function polytrack7:vel(dt) end

---@param ctx a.polytrack7
---@param dt number
---@return number
function liba.polytrack7.acc(ctx, dt) end

---@param dt number
---@return number
function polytrack7:acc(dt) end

---@param ctx a.polytrack7
---@param dt number
---@return number
function liba.polytrack7.jer(ctx, dt) end

---@param dt number
---@return number
function polytrack7:jer(dt) end

---@class a.tf
---@field __name string
---@field __index table
---@field num table
---@field den table
---@field input table
---@field output table
---@overload fun(x: number): number
local tf = setmetatable({}, {
    __call = liba.tf.iter
})
liba.tf = setmetatable({}, {
    __call = liba.tf.new
})

---@param num table
---@param den table
---@return a.tf
function liba.tf.new(num, den) end

---@param num table
---@param den table
---@return a.tf
function tf.new(num, den) end

---@param ctx a.tf
function liba.tf.die(ctx) end

function tf:die() end

---@param ctx a.tf
---@param num table
---@param den table
---@return a.tf
function liba.tf.init(ctx, num, den) end

---@param num table
---@param den table
---@return a.tf
function tf:init(num, den) end

---@param ctx a.tf
---@param x number
---@return number
function liba.tf.iter(ctx, x) end

---@param dt number
---@return number
function tf:iter(dt) end

---@param ctx a.tf
---@return a.tf
function liba.tf.zero(ctx) end

---@return a.tf
function tf:zero() end

---@class a.version
---@field __name string
---@field __index table
---@field major integer
---@field patch integer
---@field tweak integer
---@overload fun(major?: integer, minor?: integer, patch?: integer): a.version
---@overload fun(ver: string): a.version
local version = setmetatable({}, {
    __call = liba.version.init
})
liba.version = setmetatable({}, {
    __call = liba.version.new
})
liba.version.major = 0
liba.version.minor = 0
liba.version.patch = 0
liba.version.tweak = 0

---@param major? integer
---@param minor? integer
---@param patch? integer
---@return integer -3,-2,-1,0,1,2,3
function liba.version.check(major, minor, patch) end

---@param major? integer
---@param minor? integer
---@param patch? integer
---@return a.version
---@overload fun(ver: string): a.version
function liba.version.new(major, minor, patch) end

---@param major? integer
---@param minor? integer
---@param patch? integer
---@return a.version
---@overload fun(ver: string): a.version
function version.new(major, minor, patch) end

---@param ctx a.version
---@param major? integer
---@param minor? integer
---@param patch? integer
---@return a.version
---@overload fun(ctx: a.version, ver: string): a.version
function liba.version.init(ctx, major, minor, patch) end

---@param major? integer
---@param minor? integer
---@param patch? integer
---@return a.version
---@overload fun(ver: string): a.version
function version:init(major, minor, patch) end

---@param ctx a.version
---@param ver string
---@return a.version
function liba.version.parse(ctx, ver) end

---@param ver string
---@return a.version
function version:parse(ver) end

---@param lhs a.version
---@param rhs a.version
---@return integer -3,-2,-1,0,1,2,3
function liba.version.cmp(lhs, rhs) end

---@param rhs a.version
---@return integer -3,-2,-1,0,1,2,3
function version:cmp(rhs) end

---@param lhs a.version
---@param rhs a.version
---@return boolean
function liba.version.lt(lhs, rhs) end

---@param rhs a.version
---@return boolean
function version:lt(rhs) end

---@param lhs a.version
---@param rhs a.version
---@return boolean
function liba.version.gt(lhs, rhs) end

---@param rhs a.version
---@return boolean
function version:gt(rhs) end

---@param lhs a.version
---@param rhs a.version
---@return boolean
function liba.version.le(lhs, rhs) end

---@param rhs a.version
---@return boolean
function version:le(rhs) end

---@param lhs a.version
---@param rhs a.version
---@return boolean
function liba.version.ge(lhs, rhs) end

---@param rhs a.version
---@return boolean
function version:ge(rhs) end

---@param lhs a.version
---@param rhs a.version
---@return boolean
function liba.version.eq(lhs, rhs) end

---@param rhs a.version
---@return boolean
function version:eq(rhs) end

---@param lhs a.version
---@param rhs a.version
---@return boolean
function liba.version.ne(lhs, rhs) end

---@param rhs a.version
---@return boolean
function version:ne(rhs) end

liba.VERSION = "0.0.0"

return liba
