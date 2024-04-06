---@diagnostic disable
-- option: liba-lua
option("liba-lua")
set_showmenu(true)
set_category("liba")
set_values("lua", "luajit")
set_description("Enable/Disable Lua")
option_end()

if has_config("liba-lua") then
    add_requires(get_config("liba-lua"))
    target("alua")
    set_kind("shared")
    add_files("src/**.c")
    add_defines("A_EXPORTS")
    on_load(function(target)
        local subdir = get_config("liba-lua")
        local libdir = path.join("lib", subdir)
        target:set("targetdir", path.join(target:targetdir(), subdir))
        target:set("installfiles", target:targetfile(), { prefixdir = libdir })
    end)
    add_packages(get_config("liba-lua"))
    if is_plat("windows", "mingw") then
        set_filename("liba.dll")
    else
        set_filename("liba.so")
    end
    add_deps("a")
    target_end()
end
