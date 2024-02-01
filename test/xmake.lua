---@diagnostic disable
del_files = remove_files or del_files
add_tests = add_tests or function() end

function building(sources)
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files(sources)
    if has_config("liba-cxx") then
        add_defines("HAS_CXX")
    else
        del_files("*.cpp")
    end
    add_deps("a")
    add_tests("")
end

target("test/a")
building({ "a.c", "a.cpp" })
target_end()

target("test/avl")
building({ "avl.c", "avl.cpp" })
target_end()

target("test/buf")
building({ "buf.c", "buf.cpp" })
target_end()

target("test/complex")
building({ "complex.c", "complex.cpp" })
target_end()

target("test/crc")
building({ "crc.c", "crc.cpp" })
target_end()

target("test/hpf")
building({ "hpf.c", "hpf.cpp" })
target_end()

target("test/list")
building({ "list.c", "list.cpp" })
target_end()

target("test/lpf")
building({ "lpf.c", "lpf.cpp" })
target_end()

target("test/main")
building({ "main.c", "main.cpp" })
target_end()

target("test/math")
building({ "math.c", "math.cpp" })
target_end()

target("test/mf")
building({ "mf.c", "mf.cpp" })
target_end()

target("test/notefreqs")
building({ "notefreqs.c", "notefreqs.cpp" })
target_end()

target("test/operator")
building({ "operator.c", "operator.cpp" })
target_end()

target("test/pid")
building({ "pid.c", "pid.cpp" })
target_end()

target("test/pid_expert")
building({ "pid_expert.c", "pid_expert.cpp" })
target_end()

target("test/pid_fuzzy")
building({ "pid_fuzzy.c", "pid_fuzzy.cpp" })
target_end()

target("test/pid_neuro")
building({ "pid_neuro.c", "pid_neuro.cpp" })
target_end()

target("test/poly")
building({ "poly.c", "poly.cpp" })
target_end()

target("test/polytraj3")
building({ "polytraj3.c", "polytraj3.cpp" })
target_end()

target("test/polytraj5")
building({ "polytraj5.c", "polytraj5.cpp" })
target_end()

target("test/polytraj7")
building({ "polytraj7.c", "polytraj7.cpp" })
target_end()

target("test/que")
building({ "que.c", "que.cpp" })
target_end()

target("test/rbf")
building({ "rbf.c", "rbf.cpp" })
target_end()

target("test/rbt")
building({ "rbt.c", "rbt.cpp" })
target_end()

target("test/tf")
building({ "tf.c", "tf.cpp" })
target_end()

target("test/traptraj")
building({ "traptraj.c", "traptraj.cpp" })
target_end()

target("test/str")
building({ "str.c", "str.cpp" })
target_end()

target("test/slist")
building({ "slist.c", "slist.cpp" })
target_end()

target("test/utf")
building({ "utf.c", "utf.cpp" })
target_end()

target("test/vec")
building({ "vec.c", "vec.cpp" })
target_end()

target("test/version")
building({ "version.c", "version.cpp" })
target_end()
