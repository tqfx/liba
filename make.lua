local lm = require("luamake")
lm.workdir = WORKDIR
lm:source_set("a")({
    defines = { "A_EXPORTS" },
    includes = { "include" },
    sources = { "src/*.c*" },
    flags = lm.os ~= "windows" and { "-fPIC" } or {},
    links = lm.os ~= "windows" and { "m" } or {},
})
lm:static_library("alib")({
    basename = "a",
    deps = { "a" },
})
lm:shared_library("liba")({
    deps = { "a" },
})
