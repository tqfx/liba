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
on_load(function(target)
    import("lib.detect.find_tool")
    target:set("kind", "static")
    target:set("prefixname", "")
    target:set("extension", ".jar")
    local opt = { paths = { "$(env JAVA_HOME)/bin" }, check = function(...) end }
    target:set("javac", assert(find_tool("javac", opt), "javac not found!").program)
    local opt = { paths = { "$(env JAVA_HOME)/bin" }, check = function(...) end }
    target:set("jar", assert(find_tool("jar", opt), "jar not found!").program)
end)
on_build_files(function(target, sourcebatch, opt)
    sourcebatch.objectfiles = {}
    local out = target:objectdir()
    local classpath = path.join(target:scriptdir(), "src")
    for _, sourcefile in ipairs(sourcebatch.sourcefiles) do
        local source = path.relative(sourcefile, classpath):replace(".java", ".class")
        table.insert(sourcebatch.objectfiles, path.join(out, source))
        target:add("objectfiles", source)
    end
    os.mkdir(out)
    os.vrunv(target:get("javac"), table.join("-classpath", classpath, "-d", out, sourcebatch.sourcefiles))
end)
on_link(function(target, opt)
    import("utils.progress")
    os.mkdir(target:targetdir())
    local objectfiles = target:get("objectfiles")
    local targetfile = path.absolute(target:targetfile())
    progress.show(opt.progress, "${color.build.target}archiving.$(mode) %s", path.filename(targetfile))
    os.vrunv(target:get("jar"), table.join("-cf", targetfile, objectfiles), { curdir = target:objectdir() })
end)
on_install(function(target)
    local installdir = target:installdir()
    if installdir then
        print("installing %s to %s ..", target:name(), installdir)
        installdir = path.join(installdir, "share", "java")
        os.mkdir(installdir)
        os.vcp(target:targetfile(), installdir)
    end
end)
rule_end()

if has_config("liba-java") then
    target("ajar")
    add_rules("jar")
    add_files("src/**.java")
    on_load(function(target)
        target:set("targetdir", path.join(target:targetdir(), "java"))
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
    end)
    on_install(function(target)
        local installdir = target:installdir()
        if installdir then
            print("installing %s to %s ..", target:name(), installdir)
            installdir = path.join(installdir, "lib", "jni")
            os.mkdir(installdir)
            os.vcp(target:targetfile(), installdir)
        end
    end)
    if is_plat("windows", "mingw") then
        set_filename("a.dll")
    else
        set_basename("a")
    end
    add_deps("a")
    target_end()
end
