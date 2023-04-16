-- set project name
set_project("liba")

-- set xmake minimum version
set_xmakever("2.5.0")

-- set project version
set_version("0.1.1", {build = "%Y%m%d%H%M"})

-- option: with-cxx
option("with-cxx")
    set_default(true)
    set_showmenu(true)
    set_description("Enable/Disable c++")
option_end()

-- option: warning
option("warning")
    set_default(false)
    set_showmenu(true)
    set_description("Enable/Disable warning")
option_end()

if has_config("warning") then
    -- set warning everything
    set_warnings("everything")
    -- disable some compiler errors
    if is_plat("windows") then
        add_cxflags("/wd4514", "/wd4710", "/wd4711", "/wd4820", "/wd5039", "/wd5045")
    end
    add_cflags("-Wno-declaration-after-statement")
    add_cxflags("-Wno-gnu-line-marker")
    add_cxxflags("-Wno-c++98-compat-pedantic")
end

-- add build modes
add_rules("mode.check", "mode.debug", "mode.release")
if is_mode("check") and not is_plat("mingw") then
    local flags = {
        "-fsanitize=address,undefined",
        "-fsanitize-recover=address",
        "-fno-omit-frame-pointer",
        "-fsanitize=leak",
    }
    add_cxflags(flags)
    add_ldflags(flags)
end

-- option: real
option("real")
    set_default("8")
    set_showmenu(true)
    set_values("4", "8", "16")
    set_description("real number bytes")
option_end()

-- option: rpath
option("rpath")
    set_showmenu(true)
    set_description("dynamic library search path")
option_end()

target("a.objs")
    -- make as a collection of objects
    set_kind("object")
    -- detect c code functions
    real = get_config("real")
    includes("check_csnippets.lua")
    local source = 'int x = 1; puts(*(char *)&x ? "1234" : "4321");'
    configvar_check_csnippets("A_BYTE_ORDER", source, {output = true, number = true})
    local source = 'printf("%u", (unsigned int)sizeof(size_t));'
    configvar_check_csnippets("A_SIZE_VPTR", source, {output = true, number = true})
    includes("check_cincludes.lua")
    configvar_check_cincludes("A_HAVE_COMPLEX_H", "complex.h")
    configvar_check_cincludes("A_HAVE_STDINT_H", "stdint.h")
    function check_math(funcs, opt)
        includes("check_cfuncs.lua")
        for i, func in pairs(funcs) do
            local have = "A_HAVE_" .. string.upper(func)
            if real == "16" then func = func .. 'l' end
            if real == "4" then func = func .. 'f' end
            configvar_check_cfuncs(have, func, opt)
        end
    end
    local funcs = {"hypot", "log1p", "atan2"}
    check_math(funcs, {includes = "math.h"})
    local funcs = {
        "csqrt",
        "cpow", "cexp", "clog",
        "csin", "ccos", "ctan",
        "csinh", "ccosh", "ctanh",
        "casin", "cacos", "catan",
        "casinh", "cacosh", "catanh",
    }
    check_math(funcs, {includes = "complex.h"})
    -- set the auto-generated a.xmake.h
    a_have_h = path.relative(os.projectdir().."/$(buildir)/a.xmake.h", "include")
    add_defines("A_HAVE_H=\""..a_have_h.."\"", {public = true})
    set_configvar("XMAKE_VERSION", tostring(xmake.version()))
    set_configvar("A_SIZE_REAL", real, {quote = false})
    add_configfiles("include/a.xmake.h.in")
    -- add include directories
    add_includedirs("include", {public = true})
    -- set export library symbols
    add_defines("A_EXPORTS")
    -- add the common source files
    if not table.empty(os.files("src/**.cpp")) and has_config("with-cxx") then
        add_files("src/**.cpp")
    end
    add_files("src/**.c")
    -- add the platform options
    rpath = get_config("rpath")
    if rpath then
        add_rpathdirs(rpath, {public = true})
        add_linkdirs(rpath, {public = true})
    end
    if not is_plat("windows", "mingw") then
        add_syslinks("m", {public = true})
        add_cxflags("-fPIC")
    end
target_end()

target("a")
    -- make as a static library
    set_kind("static")
    -- add the dependent target
    add_deps("a.objs")
    -- add the header files for installing
    if not table.empty(os.files("include/**.hpp")) and has_config("with-cxx") then
        add_headerfiles("include/(**.hpp)")
    end
    add_headerfiles("include/(**.h)")
    add_headerfiles("$(buildir)/a.xmake.h", {prefixdir = "a"})
    after_install(function (target)
        if target:installdir() then
            local old = "#if defined(A_HAVE_H)"
            local new = "#include \"a.xmake.h\"\n" .. old
            local includedir = path.join(target:installdir(), "include")
            io.replace(path.join(includedir, "a", "a.h"), old, new, {plain = true})
        end
    end)
target_end()

target("liba")
    set_basename("a")
    set_prefixname("lib")
    -- make as a shared library
    set_kind("shared")
    -- add the dependent target
    add_deps("a.objs")
    -- add the platform options
    if is_plat("windows") then
        add_defines("A_IMPORTS", {interface = true})
    end
target_end()

-- include lua sources
if os.exists("lua/xmake.lua") then
    includes("lua")
end

-- option: with-rust
option("with-rust")
    set_default(false)
    set_showmenu(true)
    set_description("Enable/Disable rust")
option_end()

if has_config("with-rust") then
    add_requires("cargo::liba", {configs = {cargo_toml = path.join(os.projectdir(), "Cargo.toml")}})
    target("a.rust")
        set_basename("a")
        set_kind("static")
        add_deps("a.objs")
        add_files("src/lib.rs")
        add_packages("cargo::liba")
    target_end()
end

-- include test sources
if os.exists("test/xmake.lua") then
    includes("test")
end
