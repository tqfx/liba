---@diagnostic disable
-- option: liba-qjs
option("liba-qjs")
set_default(false)
set_showmenu(true)
set_category("liba")
set_description("Enable/Disable QuickJS")
option_end()

if not is_plat("windows") and has_config("liba-qjs") then
    add_requires("quickjs")
    target("aqjs")
    set_kind("shared")
    add_files("src/**.c")
    add_defines("A_EXPORTS")
    on_load(function(target)
        target:set("targetdir", path.join(target:targetdir(), "quickjs"))
        target:set("installfiles", target:targetfile(), {
            prefixdir = path.join("lib", "quickjs"),
        })
    end)
    add_packages("quickjs")
    set_filename("liba.so")
    add_deps("a")
    target_end()
end
