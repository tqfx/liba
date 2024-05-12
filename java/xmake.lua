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
    local opt = { paths = { "$(env JAVA_HOME)/bin" }, check = function(...) end }
    target:set("javac", assert(find_tool("javac", opt), "javac not found!").program)
    local opt = { paths = { "$(env JAVA_HOME)/bin" }, check = function(...) end }
    target:set("jar", assert(find_tool("jar", opt), "jar not found!").program)
    target:set("kind", "static")
    target:set("prefixname", "")
    target:set("extension", ".jar")
end)
on_buildcmd_files(function(target, batchcmds, sourcebatch, opt)
    local src = path.join(target:scriptdir(), "src")
    local src = path.relative(src, os.projectdir())
    local out = path.join(target:objectdir(), src)
    local targetfile = target:targetfile()

    sourcebatch.objectfiles = {}
    sourcebatch.dependfiles = {}
    for _, sourcefile in ipairs(sourcebatch.sourcefiles) do
        local objectfile = target:objectfile(sourcefile):gsub("(.+)%.java.+$", "%1.class")
        local dependfile = target:dependfile(objectfile)
        table.insert(sourcebatch.objectfiles, objectfile)
        table.insert(sourcebatch.dependfiles, dependfile)
    end

    batchcmds:show_progress(opt.progress, "${color.build.object}compiling.java %s", path.filename(targetfile))
    batchcmds:mkdir(out)
    batchcmds:vrunv(target:get("javac"), table.join("-classpath", src, "-d", out, sourcebatch.sourcefiles))

    batchcmds:add_depfiles(sourcebatch.sourcefiles)
    for _, objectfile in ipairs(sourcebatch.objectfiles) do
        batchcmds:set_depmtime(os.mtime(objectfile))
        batchcmds:set_depcache(sourcebatch.dependfiles[_])
    end
end)
on_linkcmd(function(target, batchcmds, opt)
    local src = path.join(target:scriptdir(), "src")
    local src = path.relative(src, os.projectdir())
    local cwd = path.join(target:objectdir(), src)
    local targetfile = target:targetfile()

    local objectfiles = {}
    for _, objectfile in ipairs(target:objectfiles()) do
        table.insert(objectfiles, path.relative(objectfile, cwd))
    end

    batchcmds:show_progress(opt.progress, "${color.build.target}archiving.java %s", path.filename(targetfile))
    batchcmds:mkdir(target:targetdir())
    batchcmds:vrunv(target:get("jar"), table.join("-cf", path.absolute(targetfile), objectfiles), { curdir = cwd })

    batchcmds:add_depfiles(target:objectfiles())
    batchcmds:set_depmtime(os.mtime(targetfile))
    batchcmds:set_depcache(target:dependfile(targetfile))
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
