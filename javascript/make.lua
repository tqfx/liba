local lm = require("luamake")
lm.rootdir = WORKDIR
lm.workdir = WORKDIR
lm:executable("liba")({
    defines = { "A_EXPORTS" },
    includes = { "../include" },
    sources = { "../src/*.c*", "src/*.c*" },
    ldflags = { "--bind", "-sWASM_ASYNC_COMPILATION=0" },
})
