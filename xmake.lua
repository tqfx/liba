---@diagnostic disable
-- set project name
set_project("liba")

-- set xmake minimum version
set_xmakever("2.5.0")

-- set project version
set_version("0.1.12", { build = "%Y%m%d" })

-- option: liba-cxx
option("liba-cxx")
set_default(true)
set_showmenu(true)
set_category("liba")
set_description("Enable/Disable C++")
option_end()

-- option: warning
option("warning")
set_default(false)
set_showmenu(true)
set_description("Enable/Disable warnings")
option_end()

if has_config("warning") then
    -- set warning everything
    set_warnings("everything")
    -- disable some compiler errors
    if is_plat("windows") then
        add_cxflags("/wd4464", "/wd4514", "/wd4710", "/wd4711", "/wd4820", "/wd5039", "/wd5045")
    end
    add_cflags("-Wno-declaration-after-statement")
    add_cxxflags("-Wno-c++98-compat-pedantic")
    add_cxflags("-Wno-unsafe-buffer-usage")
end

-- add build modes
add_rules("mode.check", "mode.debug", "mode.release")
if is_mode("check") and not is_plat("mingw") then
    local flags = {
        "-fsanitize=address,leak",
        "-fsanitize=address,undefined",
        "-fsanitize-recover=all",
        "-fno-omit-frame-pointer",
    }
    add_cxflags(flags)
    add_ldflags(flags)
end

-- option: float
option("liba-float")
set_default("8")
set_showmenu(true)
set_category("liba")
set_values("4", "8", "16")
set_description("floating-point number bytes")
option_end()

-- option: rpath
option("liba-rpath")
set_showmenu(true)
set_category("liba")
set_description("dynamic library search path")
option_end()

if xmake.version():ge("2.8.5") then
    includes("@builtin/check")
else
    includes("check_csnippets.lua")
    includes("check_cincludes.lua")
    includes("check_cfuncs.lua")
end

configvar_check_sizeof = configvar_check_sizeof
    or function(define_name, type_name)
        configvar_check_csnippets(
            define_name,
            'printf("%u", sizeof(' .. type_name .. "));return 0;",
            { output = true, number = true }
        )
    end

target("a")
-- make as a collection of objects
set_kind("object")
-- detect c code functions
configvar_check_sizeof("A_SIZE_POINTER", "void *")
configvar_check_csnippets(
    "A_BYTE_ORDER",
    'int x = 1; puts(*(char *)&x ? "1234" : "4321");',
    { output = true, number = true }
)
float = get_config("liba-float")
function check_math(funcs, opt)
    for i, func in pairs(funcs) do
        local have = "A_HAVE_" .. string.upper(func)
        if float == "16" then
            func = func .. "l"
        end
        if float == "4" then
            func = func .. "f"
        end
        configvar_check_cfuncs(have, func, opt)
    end
end
local funcs = { "expm1", "log1p", "hypot", "atan2" }
check_math(funcs, { includes = "math.h" })
-- stylua: ignore
local funcs = { "csqrt",
    "cpow", "cexp", "clog",
    "csin", "ccos", "ctan",
    "csinh", "ccosh", "ctanh",
    "casin", "cacos", "catan",
    "casinh", "cacosh", "catanh",
}
check_math(funcs, { includes = "complex.h" })
-- set the auto-generated a.xmake.h
a_have_h = path.relative(os.projectdir() .. "/$(buildir)/a.xmake.h", "include/a")
add_defines('A_HAVE_H="' .. a_have_h .. '"', { public = true })
set_configvar("XMAKE_VERSION", tostring(xmake.version()))
set_configvar("A_SIZE_FLOAT", float, { quote = false })
add_configfiles("include/a.xmake.h.in")
-- add include directories
add_includedirs("include", { public = true })
-- set export library symbols
add_defines("A_EXPORTS")
-- add the common source files
if has_config("liba-cxx") then
    add_files(os.files("src/**.c*"))
else
    add_files("src/**.c")
end
-- add the platform options
rpath = get_config("liba-rpath")
if rpath then
    add_linkdirs(rpath, { public = true })
    add_rpathdirs(rpath, { public = true })
end
if not is_plat("windows", "mingw") then
    add_syslinks("m", { public = true })
    add_cxflags("-fPIC")
end
target_end()

target("alib")
set_basename("a")
-- make as a static library
set_kind("static")
-- add the header files for installing
add_headerfiles("$(buildir)/a.xmake.h", { prefixdir = "a" })
if has_config("liba-cxx") then
    add_headerfiles("include/(a/**.h*)")
else
    add_headerfiles("include/(a/**.h)")
end
on_load(function(target)
    target:set("links", target:targetfile(), { interface = true })
end)
after_install(function(target)
    if target:installdir() then
        local cur = "#if defined(A_HAVE_H)"
        local new = '#include "a.xmake.h"\n' .. cur
        local includedir = path.join(target:installdir(), "include")
        io.replace(path.join(includedir, "a", "a.h"), cur, new, { plain = true })
    end
end)
-- add the dependent target
add_deps("a")
target_end()

target("liba")
-- make as a shared library
set_kind("shared")
-- add the platform options
if not is_plat("windows") then
    set_prefixname("lib")
    set_basename("a")
end
on_load(function(target)
    local liba = target:targetfile()
    if target:is_plat("windows") then
        liba = liba:gsub(".dll", ".lib")
    elseif target:is_plat("mingw") then
        liba = liba .. ".a"
    end
    target:set("links", liba, { interface = true })
end)
add_defines("A_IMPORTS", { interface = true })
-- add the dependent target
add_deps("a")
target_end()

-- option: liba-rust
option("liba-rust")
set_default(false)
set_showmenu(true)
set_category("liba")
set_description("Enable/Disable Rust")
option_end()

if has_config("liba-rust") then
    target("ars")
    set_kind("static")
    set_basename("liba")
    add_files("src/lib.rs")
    if get_config("liba-float") == "4" then
        add_rcflags('--cfg=feature="float"')
    end
    add_deps("a")
    target_end()
end

-- include module sources
if not table.empty(os.files("*/xmake.lua")) then
    includes("*/xmake.lua")
end
