target("test/pid/expert")
    building({"expert.c", "expert.cpp"})
target_end()

target("test/pid/fuzzy")
    building({"fuzzy.c", "fuzzy.cpp"})
target_end()

target("test/pid/neuron")
    building({"neuron.c", "neuron.cpp"})
target_end()
