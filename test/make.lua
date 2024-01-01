local lm = require("luamake")
lm:source_set("a.o")({
    defines = { "A_EXPORTS" },
    includes = { "../include" },
    sources = { "../src/*.c*" },
    links = lm.os ~= "windows" and { "m" } or {},
})
local executable = function(target)
    lm:executable(target)({
        defines = { "HAS_CXX" },
        includes = { "../include" },
        sources = { target .. ".c*" },
        deps = { "a.o" },
    })
end
executable("a")
executable("avl")
executable("buf")
executable("complex")
executable("crc")
executable("hpf")
executable("list")
executable("lpf")
executable("main")
executable("math")
executable("mf")
executable("notefreqs")
executable("operator")
executable("pid")
executable("pid_expert")
executable("pid_fuzzy")
executable("pid_neuro")
executable("poly")
executable("polytraj3")
executable("polytraj5")
executable("polytraj7")
executable("que")
executable("rbf")
executable("rbt")
executable("tf")
executable("str")
executable("slist")
executable("utf")
executable("vec")
executable("version")
