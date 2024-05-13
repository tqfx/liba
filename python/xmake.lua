---@diagnostic disable
-- option: liba-python
option("liba-python")
set_showmenu(true)
set_category("liba")
set_values("python3", "python2")
set_description("Enable/Disable Python")
option_end()

rule("cython")
set_extensions(".pyx")
on_load(function(target)
    import("lib.detect.find_tool")
    local python = get_config("liba-python")
    local python = assert(find_tool(python) or find_tool("python"), "python not found!")
    local cython = assert(find_tool("cython3") or find_tool("cython"), "cython not found!")
    local suffix = os.iorunv(python.program, {
        "-c",
        'import sysconfig;print(sysconfig.get_config_var("EXT_SUFFIX") or sysconfig.get_config_var("SO"))',
    })
    local prefix = os.iorunv(python.program, { "-c", 'import sysconfig;print(sysconfig.get_path("data"))' })
    local platlib = os.iorunv(python.program, { "-c", 'import sysconfig;print(sysconfig.get_path("platlib"))' })
    target:set("python", python.program)
    target:set("cython", cython.program)
    target:set("kind", "shared")
    target:set("prefixname", "")
    target:set("extension", suffix:trim())
    target:set("installdir", prefix:trim())
    target:add("runenvs", "PYTHONPATH", target:targetdir())
    target:set("platlib", path.relative(platlib:trim(), prefix:trim()))
end)
on_buildcmd_file(function(target, batchcmds, sourcefile, opt)
    local sourcefile_c = sourcefile:replace(".pyx", ".c")
    local objectfile = target:objectfile(sourcefile_c)
    table.insert(target:objectfiles(), objectfile)

    batchcmds:show_progress(opt.progress, "${color.build.object}compiling.cython %s", sourcefile)
    batchcmds:vrunv(target:get("cython"), { "--fast-fail", "--module-name", target:basename(), sourcefile })

    batchcmds:show_progress(opt.progress, "${color.build.object}compiling.$(mode) %s", sourcefile_c)
    batchcmds:compile(sourcefile_c, objectfile)

    batchcmds:add_depfiles(sourcefile)
    batchcmds:set_depmtime(os.mtime(objectfile))
    batchcmds:set_depcache(target:dependfile(objectfile))
end)
rule_end()

if has_config("liba-python") then
    add_requires(get_config("liba-python"))
    target("apy")
    add_rules("cython")
    add_files("src/a.pyx")
    add_defines("A_EXPORTS")
    on_install(function(target)
        local installdir = target:installdir()
        if installdir then
            print("installing %s to %s ..", target:name(), installdir)
            installdir = path.join(installdir, target:get("platlib"))
            os.mkdir(installdir)
            os.vcp(target:targetfile(), installdir)
            for _, installfile in ipairs(target:installfiles()) do
                os.vcp(installfile, installdir)
            end
        end
    end)
    add_packages(get_config("liba-python"))
    add_installfiles("liba.pyi")
    set_basename("liba")
    set_warnings("all")
    set_targetdir(".")
    add_deps("a")
    target_end()
end
