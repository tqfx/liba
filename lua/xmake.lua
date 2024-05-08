---@diagnostic disable
-- option: liba-lua
option("liba-lua")
set_showmenu(true)
set_category("liba")
set_values("lua5.4", "lua5.3", "lua5.2", "lua5.1", "luajit")
set_description("Enable/Disable Lua")
option_end()

if has_config("liba-lua") then
    add_requires(get_config("liba-lua"))
    target("alua")
    set_kind("shared")
    add_files("src/**.c")
    add_defines("A_EXPORTS")
    on_load(function(target)
        target:set("targetdir", path.join(target:targetdir(), get_config("liba-lua")))
    end)
    on_install(function(target)
        local installdir = target:installdir()
        if installdir then
            local lua = get_config("liba-lua")
            if lua:match("luajit") then
                lua = "lua/5.1"
            elseif lua:match("lua%d") then
                lua = lua:replace("lua", "lua/")
            end
            print("installing %s to %s ..", target:name(), installdir)
            installdir = path.join(installdir, "lib", lua)
            os.mkdir(installdir)
            os.vcp(target:targetfile(), installdir)
        end
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
