---@diagnostic disable
-- option: liba-jni
option("liba-jni")
set_default(false)
set_showmenu(true)
set_category("liba")
set_description("Enable/Disable Java")
option_end()

if has_config("liba-jni") then
    target("ajni")
    set_kind("shared")
    add_files("src/**.c")
    add_defines("A_EXPORTS")
    add_includedirs("include")
    on_config(function(target)
        import("lib.detect.find_path")
        target:add(
            "includedirs",
            find_path("jni.h", "$(env JAVA_HOME)/include"),
            find_path("jni_md.h", "$(env JAVA_HOME)/include/*")
        )
        target:set("targetdir", path.join(target:targetdir(), "java"))
        target:set("installfiles", target:targetfile(), {
            prefixdir = path.join("lib", "jni"),
        })
    end)
    if is_plat("windows", "mingw") then
        set_filename("a.dll")
    else
        set_basename("a")
    end
    add_deps("a")
    target_end()
end
