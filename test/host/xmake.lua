---@diagnostic disable

target("test/host/que")
building({ "que.c", "que.cpp" })
target_end()

target("test/host/str")
building({ "str.c", "str.cpp" })
target_end()

target("test/host/vec")
building({ "vec.c", "vec.cpp" })
target_end()

target("test/host/vector")
building({ "vector.c", "vector.cpp" })
target_end()
