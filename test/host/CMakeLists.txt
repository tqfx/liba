set(TARGET_PREFIX ${TARGET_PREFIX}host_)

building(que que.c que.cpp)
unittest(que)

building(str str.c str.cpp)
unittest(str)

building(vec vec.c vec.cpp)
unittest(vec)

building(vector vector.c vector.cpp)
unittest(vector)
