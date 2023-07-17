del_files = remove_files or del_files

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
end

target("test/_a")
    building({"a.c", "a.cpp"})
target_end()

target("test/_avl")
    building({"avl.c", "avl.cpp"})
target_end()

target("test/_buf")
    building({"buf.c", "buf.cpp"})
target_end()

target("test/_complex")
    building({"complex.c", "complex.cpp"})
target_end()

target("test/_crc")
    building({"crc.c", "crc.cpp"})
target_end()

target("test/_hpf")
    building({"hpf.c", "hpf.cpp"})
target_end()

target("test/_list")
    building({"list.c", "list.cpp"})
target_end()

target("test/_lpf")
    building({"lpf.c", "lpf.cpp"})
target_end()

target("test/_main")
    building({"main.c", "main.cpp"})
target_end()

target("test/_math")
    building({"math.c", "math.cpp"})
target_end()

target("test/_notefreqs")
    building({"notefreqs.c", "notefreqs.cpp"})
target_end()

target("test/_operator")
    building({"operator.c", "operator.cpp"})
target_end()

target("test/_pid")
    building({"pid.c", "pid.cpp"})
target_end()

target("test/_poly")
    building({"poly.c", "poly.cpp"})
target_end()

target("test/_polytrack")
    building({"polytrack.c", "polytrack.cpp"})
target_end()

target("test/_rbf")
    building({"rbf.c", "rbf.cpp"})
target_end()

target("test/_rbt")
    building({"rbt.c", "rbt.cpp"})
target_end()

target("test/_tf")
    building({"tf.c", "tf.cpp"})
target_end()

target("test/_slist")
    building({"slist.c", "slist.cpp"})
target_end()

target("test/_utf")
    building({"utf.c", "utf.cpp"})
target_end()

target("test/_version")
    building({"version.c", "version.cpp"})
target_end()

if not table.empty(os.files("*/xmake.lua")) then
    includes("*/xmake.lua")
end
