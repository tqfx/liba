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
        del_files("*.cc")
    end
    add_deps("a")
    add_tests("")
end

target("test/a")
building({ "a.c", "a.cc" })
target_end()

target("test/avl")
building({ "avl.c", "avl.cc" })
target_end()

target("test/buf")
building({ "buf.c", "buf.cc" })
target_end()

target("test/complex")
building({ "complex.c", "complex.cc" })
target_end()

target("test/crc")
building({ "crc.c", "crc.cc" })
target_end()

target("test/hash")
building({ "hash.c", "hash.cc" })
target_end()

target("test/hpf")
building({ "hpf.c", "hpf.cc" })
target_end()

target("test/linalg_llt")
building({ "linalg_llt.c", "linalg_llt.cc" })
target_end()

target("test/linalg_plu")
building({ "linalg_plu.c", "linalg_plu.cc" })
target_end()

target("test/linalg")
building({ "linalg.c", "linalg.cc" })
target_end()

target("test/list")
building({ "list.c", "list.cc" })
target_end()

target("test/lpf")
building({ "lpf.c", "lpf.cc" })
target_end()

target("test/math")
building({ "math.c", "math.cc" })
target_end()

target("test/mf")
building({ "mf.c", "mf.cc" })
target_end()

target("test/notefreqs")
building({ "notefreqs.c", "notefreqs.cc" })
target_end()

target("test/pid")
building({ "pid.c", "pid.cc" })
target_end()

target("test/pid_expert")
building({ "pid_expert.c", "pid_expert.cc" })
target_end()

target("test/pid_fuzzy")
building({ "pid_fuzzy.c", "pid_fuzzy.cc" })
target_end()

target("test/pid_neuro")
building({ "pid_neuro.c", "pid_neuro.cc" })
target_end()

target("test/poly")
building({ "poly.c", "poly.cc" })
target_end()

target("test/que")
building({ "que.c", "que.cc" })
target_end()

target("test/rbt")
building({ "rbt.c", "rbt.cc" })
target_end()

target("test/regress")
building({ "regress.c", "regress.cc" })
target_end()

target("test/regress_linear")
building({ "regress_linear.c", "regress_linear.cc" })
target_end()

target("test/regress_simple")
building({ "regress_simple.c", "regress_simple.cc" })
target_end()

target("test/slist")
building({ "slist.c", "slist.cc" })
target_end()

target("test/str")
building({ "str.c", "str.cc" })
target_end()

target("test/test")
building({ "test.c", "test.cc" })
target_end()

target("test/tf")
building({ "tf.c", "tf.cc" })
target_end()

target("test/trajbell")
building({ "trajbell.c", "trajbell.cc" })
target_end()

target("test/trajpoly3")
building({ "trajpoly3.c", "trajpoly3.cc" })
target_end()

target("test/trajpoly5")
building({ "trajpoly5.c", "trajpoly5.cc" })
target_end()

target("test/trajpoly7")
building({ "trajpoly7.c", "trajpoly7.cc" })
target_end()

target("test/trajtrap")
building({ "trajtrap.c", "trajtrap.cc" })
target_end()

target("test/utf")
building({ "utf.c", "utf.cc" })
target_end()

target("test/vec")
building({ "vec.c", "vec.cc" })
target_end()

target("test/version")
building({ "version.c", "version.cc" })
target_end()
