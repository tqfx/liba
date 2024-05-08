---@diagnostic disable
-- option: liba-quickjs
option("liba-quickjs")
set_default(false)
set_showmenu(true)
set_category("liba")
set_description("Enable/Disable QuickJS")
option_end()

if not is_plat("windows") and has_config("liba-quickjs") then
    add_requires("quickjs")
    target("aqjs")
    set_kind("shared")
    add_files("src/**.c")
    add_defines("A_EXPORTS")
    on_load(function(target)
        target:set("targetdir", path.join(target:targetdir(), "quickjs"))
    end)
    on_install(function(target)
        local installdir = target:installdir()
        if installdir then
            print("installing %s to %s ..", target:name(), installdir)
            installdir = path.join(installdir, "lib", "quickjs")
            os.mkdir(installdir)
            os.vcp(target:targetfile(), installdir)
        end
    end)
    add_packages("quickjs")
    set_filename("liba.so")
    add_deps("a")
    target_end()
end
