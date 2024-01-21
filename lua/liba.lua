---@meta liba
local liba = {}

---@param str string
---@param ... string
---@return string
function liba.hash_bkdr(str, ...) end

---@param x integer
---@param ... integer
---@return integer ...
function liba.isqrt(x, ...) end

---@param x number
---@param ... number
---@return number ...
function liba.rsqrt(x, ...) end

---@class a.complex
---@field real number
---@field imag number
---@field rho number
---@field theta number
---@operator len: number
---@operator unm: a.complex
---@operator add(a.complex): a.complex
---@operator sub(a.complex): a.complex
---@operator mul(a.complex): a.complex
---@operator div(a.complex): a.complex
---@operator pow(a.complex): a.complex
local complex = {}
---@class liba.complex
---@overload fun(real?: a.complex|number|string, imag?: number): a.complex
liba.complex = {}

---@param real? a.complex|number|string
---@param imag? number
---@return a.complex
function liba.complex.new(real, imag) end

---@param real? a.complex|number|string
---@param imag? number
---@return a.complex
function complex.new(real, imag) end

---@param real? number
---@param imag? number
---@return a.complex
function liba.complex.rect(real, imag) end

---@param real? number
---@param imag? number
---@return a.complex
function complex.rect(real, imag) end

---@param rho? number
---@param theta? number
---@return a.complex
function liba.complex.polar(rho, theta) end

---@param rho? number
---@param theta? number
---@return a.complex
function complex.polar(rho, theta) end

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
function liba.complex.proj(z) end

---@return a.complex
function complex:proj() end

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

---@class a.hpf
---@field alpha number
---@field input number
---@field output number
---@overload fun(x: number): number
local hpf = {}
---@class liba.hpf
---@overload fun(alpha: number): a.hpf
---@overload fun(fc: number, ts: number): a.hpf
liba.hpf = {}

---@param fc number
---@param ts number
---@return a.hpf
---@overload fun(alpha: number): a.hpf
function liba.hpf.new(fc, ts) end

---@param fc number
---@param ts number
---@return a.hpf
---@overload fun(alpha: number): a.hpf
function hpf.new(fc, ts) end

---@param ctx a.hpf
---@param fc number
---@param ts number
---@return a.hpf
---@overload fun(ctx: a.hpf, alpha: number): a.hpf
function liba.hpf.gen(ctx, fc, ts) end

---@param fc number
---@param ts number
---@return a.hpf
---@overload fun(ctx: a.hpf, alpha: number): a.hpf
function hpf:gen(fc, ts) end

---@param ctx a.hpf
---@param x number
---@return number
function liba.hpf.iter(ctx, x) end

---@param x number
---@return number
function hpf:iter(x) end

---@param ctx a.hpf
---@return a.hpf
function liba.hpf.zero(ctx) end

---@return a.hpf
function hpf:zero() end

---@class a.lpf
---@field alpha number
---@field output number
---@overload fun(x: number): number
local lpf = {}
---@class liba.lpf
---@overload fun(alpha: number): a.lpf
---@overload fun(fc: number, ts: number): a.lpf
liba.lpf = {}

---@param fc number
---@param ts number
---@return a.lpf
---@overload fun(alpha: number): a.lpf
function liba.lpf.new(fc, ts) end

---@param fc number
---@param ts number
---@return a.lpf
---@overload fun(alpha: number): a.lpf
function lpf.new(fc, ts) end

---@param ctx a.lpf
---@param fc number
---@param ts number
---@return a.lpf
---@overload fun(ctx: a.lpf, alpha: number): a.lpf
function liba.lpf.gen(ctx, fc, ts) end

---@param fc number
---@param ts number
---@return a.lpf
---@overload fun(ctx: a.lpf, alpha: number): a.lpf
function lpf:gen(fc, ts) end

---@param ctx a.lpf
---@param x number
---@return number
function liba.lpf.iter(ctx, x) end

---@param x number
---@return number
function lpf:iter(x) end

---@param ctx a.lpf
---@return a.lpf
function liba.lpf.zero(ctx) end

---@return a.lpf
function lpf:zero() end

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
---@field kp number
---@field ki number
---@field kd number
---@field summax number
---@field summin number
---@field outmax number
---@field outmin number
---@field out number
---@field fdb number
---@field err number
local pid = {}
---@class liba.pid
---@overload fun(): a.pid
liba.pid = {}
liba.pid.RUN = 0
liba.pid.POS = 1
liba.pid.INC = 2

---@return a.pid
function liba.pid.new() end

---@return a.pid
function pid.new() end

---@param ctx a.pid
---@return a.pid
function liba.pid.init(ctx) end

---@return a.pid
function pid:init() end

---@param ctx a.pid
---@return a.pid
function liba.pid.zero(ctx) end

---@return a.pid
function pid:zero() end

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
function liba.pid.run(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid:run(set, fdb) end

---@param ctx a.pid
---@param set number
---@param fdb number
---@return number
function liba.pid.pos(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid:pos(set, fdb) end

---@param ctx a.pid
---@param set number
---@param fdb number
---@return number
function liba.pid.inc(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid:inc(set, fdb) end

---@class a.pid_fuzzy
---@field kp number
---@field ki number
---@field kd number
---@field summax number
---@field summin number
---@field outmax number
---@field outmin number
---@field out number
---@field fdb number
---@field err number
---@field order integer
---@field joint integer
local pid_fuzzy = {}
---@class liba.pid_fuzzy
---@overload fun(): a.pid_fuzzy
liba.pid_fuzzy = {}

---@return a.pid_fuzzy
function liba.pid_fuzzy.new() end

---@return a.pid_fuzzy
function pid_fuzzy.new() end

---@param ctx a.pid_fuzzy
---@return a.pid_fuzzy
function liba.pid_fuzzy.init(ctx) end

---@return a.pid_fuzzy
function pid_fuzzy:init() end

---@param ctx a.pid_fuzzy
---@return a.pid_fuzzy
function liba.pid_fuzzy.zero(ctx) end

---@return a.pid_fuzzy
function pid_fuzzy:zero() end

---@param ctx a.pid_fuzzy
---@param me table
---@param mec table
---@param mkp table
---@param mki table
---@param mkd table
---@return a.pid_fuzzy
function liba.pid_fuzzy.rule(ctx, me, mec, mkp, mki, mkd) end

---@param me table
---@param mec table
---@param mkp table
---@param mki table
---@param mkd table
---@return a.pid_fuzzy
function pid_fuzzy:rule(me, mec, mkp, mki, mkd) end

liba.pid_fuzzy.CAP = 1
liba.pid_fuzzy.CAP_ALGEBRA = 2
liba.pid_fuzzy.CAP_BOUNDED = 3
liba.pid_fuzzy.CUP = 4
liba.pid_fuzzy.CUP_ALGEBRA = 5
liba.pid_fuzzy.CUP_BOUNDED = 6
liba.pid_fuzzy.EQU = 0
---@param ctx a.pid_fuzzy
---@param op integer
---@return a.pid_fuzzy
function liba.pid_fuzzy.op(ctx, op) end

---@param op integer
---@return a.pid_fuzzy
function pid_fuzzy:op(op) end

---@param ctx a.pid_fuzzy
---@param joint integer
---@return a.pid_fuzzy
function liba.pid_fuzzy.set_joint(ctx, joint) end

---@param joint integer
---@return a.pid_fuzzy
function pid_fuzzy:set_joint(joint) end

---@param ctx a.pid_fuzzy
---@param kp number
---@param ki number
---@param kd number
---@return a.pid_fuzzy
function liba.pid_fuzzy.kpid(ctx, kp, ki, kd) end

---@param kp number
---@param ki number
---@param kd number
---@return a.pid_fuzzy
function pid_fuzzy:kpid(kp, ki, kd) end

---@param ctx a.pid_fuzzy
---@param set number
---@param fdb number
---@return number
function liba.pid_fuzzy.run(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid_fuzzy:run(set, fdb) end

---@param ctx a.pid_fuzzy
---@param set number
---@param fdb number
---@return number
function liba.pid_fuzzy.pos(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid_fuzzy:pos(set, fdb) end

---@param ctx a.pid_fuzzy
---@param set number
---@param fdb number
---@return number
function liba.pid_fuzzy.inc(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid_fuzzy:inc(set, fdb) end

---@class a.pid_neuro
---@field k number
---@field kp number
---@field ki number
---@field kd number
---@field wp number
---@field wi number
---@field wd number
---@field outmax number
---@field outmin number
---@field out number
---@field fdb number
---@field err number
---@field ec number
local pid_neuro = {}
---@class liba.pid_neuro
---@overload fun(): a.pid_neuro
liba.pid_neuro = {}

---@return a.pid_neuro
function liba.pid_neuro.new() end

---@return a.pid_neuro
function pid_neuro.new() end

---@param ctx a.pid_neuro
---@return a.pid_neuro
function liba.pid_neuro.init(ctx) end

---@return a.pid_neuro
function pid_neuro:init() end

---@param ctx a.pid_neuro
---@return a.pid_neuro
function liba.pid_neuro.zero(ctx) end

---@return a.pid_neuro
function pid_neuro:zero() end

---@param ctx a.pid_neuro
---@param k number
---@param kp number
---@param ki number
---@param kd number
---@return a.pid_neuro
function liba.pid_neuro.kpid(ctx, k, kp, ki, kd) end

---@param k number
---@param kp number
---@param ki number
---@param kd number
---@return a.pid_neuro
function pid_neuro:kpid(k, kp, ki, kd) end

---@param ctx a.pid_neuro
---@param wp number
---@param wi number
---@param wd number
---@return a.pid_neuro
function liba.pid_neuro.wpid(ctx, wp, wi, wd) end

---@param wp number
---@param wi number
---@param wd number
---@return a.pid_neuro
function pid_neuro:wpid(wp, wi, wd) end

---@param ctx a.pid_neuro
---@param set number
---@param fdb number
---@return number
function liba.pid_neuro.run(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid_neuro:run(set, fdb) end

---@param ctx a.pid_neuro
---@param set number
---@param fdb number
---@return number
function liba.pid_neuro.inc(ctx, set, fdb) end

---@param set number
---@param fdb number
---@return number
function pid_neuro:inc(set, fdb) end

---@class a.polytraj3
---@field q table
---@field v table
---@field a table
local polytraj3 = {}
---@class liba.polytraj3
---@overload fun(t0: number, t1: number, q0: number, q1: number, v0?: number, v1?: number): a.polytraj3
---@overload fun(source: table, target: table): a.polytraj3
liba.polytraj3 = {}

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@return a.polytraj3
---@overload fun(source: table, target: table): a.polytraj3
function liba.polytraj3.new(t0, t1, q0, q1, v0, v1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@return a.polytraj3
---@overload fun(source: table, target: table): a.polytraj3
function polytraj3.new(t0, t1, q0, q1, v0, v1) end

---@param ctx a.polytraj3
---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@return a.polytraj3
---@overload fun(ctx: a.polytraj3, source: table, target: table): a.polytraj3
function liba.polytraj3.gen(ctx, t0, t1, q0, q1, v0, v1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@return a.polytraj3
---@overload fun(source: table, target: table): a.polytraj3
function polytraj3:gen(t0, t1, q0, q1, v0, v1) end

---@param ctx a.polytraj3
---@param dt number
---@return number
function liba.polytraj3.pos(ctx, dt) end

---@param dt number
---@return number
function polytraj3:pos(dt) end

---@param ctx a.polytraj3
---@param dt number
---@return number
function liba.polytraj3.vel(ctx, dt) end

---@param dt number
---@return number
function polytraj3:vel(dt) end

---@param ctx a.polytraj3
---@param dt number
---@return number
function liba.polytraj3.acc(ctx, dt) end

---@param dt number
---@return number
function polytraj3:acc(dt) end

---@class a.polytraj5
---@field q table
---@field v table
---@field a table
local polytraj5 = {}
---@class liba.polytraj5
---@overload fun(t0: number, t1: number, q0: number, q1: number, v0?: number, v1?: number, a0?: number, a1?: number): a.polytraj5
---@overload fun(source: table, target: table): a.polytraj5
liba.polytraj5 = {}

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@return a.polytraj5
---@overload fun(source: table, target: table): a.polytraj5
function liba.polytraj5.new(t0, t1, q0, q1, v0, v1, a0, a1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@return a.polytraj5
---@overload fun(source: table, target: table): a.polytraj5
function polytraj5.new(t0, t1, q0, q1, v0, v1, a0, a1) end

---@param ctx a.polytraj5
---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@return a.polytraj5
---@overload fun(ctx: a.polytraj5, source: table, target: table): a.polytraj5
function liba.polytraj5.gen(ctx, t0, t1, q0, q1, v0, v1, a0, a1) end

---@param t0 number
---@param t1 number
---@param q0 number
---@param q1 number
---@param v0? number
---@param v1? number
---@param a0? number
---@param a1? number
---@return a.polytraj5
---@overload fun(source: table, target: table): a.polytraj5
function polytraj5:gen(t0, t1, q0, q1, v0, v1, a0, a1) end

---@param ctx a.polytraj5
---@param dt number
---@return number
function liba.polytraj5.pos(ctx, dt) end

---@param dt number
---@return number
function polytraj5:pos(dt) end

---@param ctx a.polytraj5
---@param dt number
---@return number
function liba.polytraj5.vel(ctx, dt) end

---@param dt number
---@return number
function polytraj5:vel(dt) end

---@param ctx a.polytraj5
---@param dt number
---@return number
function liba.polytraj5.acc(ctx, dt) end

---@param dt number
---@return number
function polytraj5:acc(dt) end

---@class a.polytraj7
---@field q table
---@field v table
---@field a table
---@field j table
local polytraj7 = {}
---@class liba.polytraj7
---@overload fun(t0: number, t1: number, q0: number, q1: number, v0?: number, v1?: number, a0?: number, a1?: number, j0?: number, j1?: number): a.polytraj7
---@overload fun(source: table, target: table): a.polytraj7
liba.polytraj7 = {}

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
---@return a.polytraj7
---@overload fun(source: table, target: table): a.polytraj7
function liba.polytraj7.new(t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) end

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
---@return a.polytraj7
---@overload fun(source: table, target: table): a.polytraj7
function polytraj7.new(t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) end

---@param ctx a.polytraj7
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
---@return a.polytraj7
---@overload fun(ctx: a.polytraj7, source: table, target: table): a.polytraj7
function liba.polytraj7.gen(ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) end

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
---@return a.polytraj7
---@overload fun(source: table, target: table): a.polytraj7
function polytraj7:gen(t0, t1, q0, q1, v0, v1, a0, a1, j0, j1) end

---@param ctx a.polytraj7
---@param dt number
---@return number
function liba.polytraj7.pos(ctx, dt) end

---@param dt number
---@return number
function polytraj7:pos(dt) end

---@param ctx a.polytraj7
---@param dt number
---@return number
function liba.polytraj7.vel(ctx, dt) end

---@param dt number
---@return number
function polytraj7:vel(dt) end

---@param ctx a.polytraj7
---@param dt number
---@return number
function liba.polytraj7.acc(ctx, dt) end

---@param dt number
---@return number
function polytraj7:acc(dt) end

---@param ctx a.polytraj7
---@param dt number
---@return number
function liba.polytraj7.jer(ctx, dt) end

---@param dt number
---@return number
function polytraj7:jer(dt) end

---@class a.tf
---@field num table
---@field den table
---@field input table
---@field output table
---@overload fun(x: number): number
local tf = {}
---@class liba.tf
---@overload fun(num: table, den: table): a.tf
liba.tf = {}

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

---@param x number
---@return number
function tf:iter(x) end

---@param ctx a.tf
---@return a.tf
function liba.tf.zero(ctx) end

---@return a.tf
function tf:zero() end

---@class a.version
---@field major integer
---@field minor integer
---@field third integer
---@field extra integer
---@overload fun(major?: integer, minor?: integer, third?: integer, extra?: integer): a.version
---@overload fun(ver: string): a.version
local version = {}
---@class liba.version
---@overload fun(major?: integer, minor?: integer, third?: integer, extra?: integer): a.version
---@overload fun(ver: string): a.version
liba.version = {}
liba.version.MAJOR = 0
liba.version.MINOR = 0
liba.version.PATCH = 0
liba.version.TWEAK = 0

---@param major? integer
---@param minor? integer
---@param patch? integer
---@return integer -3,-2,-1,0,1,2,3
function liba.version.check(major, minor, patch) end

---@param major? integer
---@param minor? integer
---@param third? integer
---@param extra? integer
---@return a.version
---@overload fun(ver: string): a.version
function liba.version.new(major, minor, third, extra) end

---@param major? integer
---@param minor? integer
---@param third? integer
---@param extra? integer
---@return a.version
---@overload fun(ver: string): a.version
function version.new(major, minor, third, extra) end

---@param ctx a.version
---@param major? integer
---@param minor? integer
---@param third? integer
---@param extra? integer
---@return a.version
---@overload fun(ctx: a.version, ver: string): a.version
function liba.version.init(ctx, major, minor, third, extra) end

---@param major? integer
---@param minor? integer
---@param third? integer
---@param extra? integer
---@return a.version
---@overload fun(ver: string): a.version
function version:init(major, minor, third, extra) end

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
