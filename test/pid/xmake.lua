target("test/pid/_expert")
    building({"expert.c", "expert.cpp"})
target_end()

target("test/pid/_fuzzy")
    building({"fuzzy.c", "fuzzy.cpp"})
target_end()

target("test/pid/_neuron")
    building({"neuron.c", "neuron.cpp"})
target_end()
