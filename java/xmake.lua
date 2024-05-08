---@diagnostic disable
-- option: liba-java
option("liba-java")
set_default(false)
set_showmenu(true)
set_category("liba")
set_description("Enable/Disable Java")
option_end()

rule("jar")
set_extensions(".java")
add_imports("lib.detect.find_tool", "utils.progress")
on_load(function(target)
    target:set("kind", "static")
    target:set("prefixname", "")
    target:set("extension", ".jar")
end)
on_build_files(function(target, sourcebatch, opt)
    local out = target:objectdir()
    local src = path.join(target:scriptdir(), "src")
    for _, sourcefile in ipairs(sourcebatch.sourcefiles) do
        local source = path.relative(sourcefile, src)
        source = source:replace(".java", ".class")
        local object = path.join(out, source)
        target:add("objectfiles", object)
    end
    sourcebatch.objectfiles = target:get("objectfiles")
    local javac = find_tool("javac", { paths = "$(env JAVA_HOME)/bin" })
    os.vrunv(javac.program, table.join("-cp", src, "-d", out, sourcebatch.sourcefiles))
end)
on_link(function(target, opt)
    local jar = find_tool("jar", { paths = "$(env JAVA_HOME)/bin" })
    progress.show(opt.progress, "${color.build.target}archiving.$(mode) %s", path.filename(target:targetfile()))
    os.vrunv(jar.program, table.join("-cf", target:targetfile(), target:get("objectfiles")))
end)
before_link(function(target)
    os.mkdir(target:targetdir())
end)
after_clean(function(target)
    os.tryrm(target:targetdir())
end)
rule_end()

if has_config("liba-java") then
    target("ajar")
    add_rules("jar")
    add_files("src/**.java")
    on_load(function(target)
        target:set("targetdir", path.join(target:targetdir(), "java"))
        target:set("installfiles", target:targetfile(), {
            prefixdir = path.join("share", "java"),
        })
    end)
    set_basename("liba")
    target_end()

    target("ajni")
    set_kind("shared")
    add_files("src/**.c")
    add_defines("A_EXPORTS")
    add_includedirs("include")
    on_load(function(target)
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
