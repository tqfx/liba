---@diagnostic disable
-- option: liba-python
option("liba-python")
set_default(false)
set_showmenu(true)
set_category("liba")
set_description("Enable/Disable Python")
option_end()

rule("cython")
set_extensions(".pyx")
add_imports("lib.detect.find_tool")
on_load(function(target)
    local python = assert(find_tool("python"), "python not found!")
    local so = os.iorunv(python.program, {
        "-c",
        'import sysconfig;print(sysconfig.get_config_var("EXT_SUFFIX") or sysconfig.get_config_var("SO"))',
    })
    target:set("kind", "shared")
    target:set("prefixname", "")
    target:set("extension", so:trim())
    target:add("runenvs", "PYTHONPATH", target:targetdir())
end)
on_buildcmd_file(function(target, batchcmds, sourcefile, opt)
    local cython = assert(find_tool("cython") or find_tool("cython3"), "cython not found!")

    batchcmds:show_progress(opt.progress, "${color.build.object}compiling.$(mode) %s", sourcefile)
    batchcmds:vrunv(cython.program, { "--fast-fail", "--module-name", target:basename(), sourcefile })

    local sourcefile_c = sourcefile:replace(".pyx", ".c")
    local objectfile = target:objectfile(sourcefile_c)
    table.insert(target:objectfiles(), objectfile)
    batchcmds:compile(sourcefile_c, objectfile)

    batchcmds:add_depfiles(sourcefile)
    batchcmds:set_depmtime(os.mtime(objectfile))
    batchcmds:set_depcache(target:dependfile(objectfile))
end)
rule_end()

if has_config("liba-python") then
    add_requires("python")
    target("apy")
    set_kind("shared")
    add_rules("cython")
    add_files("src/a.pyx")
    add_defines("A_EXPORTS")
    add_imports("lib.detect.find_tool")
    on_load(function(target)
        target:set("targetdir", path.join(target:targetdir(), "python"))
    end)
    on_install(function(target)
        local installdir = target:installdir()
        if installdir then
            print("installing %s to %s ..", target:name(), installdir)
            installdir = path.join(installdir, "lib", "python")
            os.mkdir(installdir)
            os.vcp(target:targetfile(), installdir)
        end
    end)
    add_packages("python")
    set_basename("liba")
    add_deps("a")
    target_end()
end
