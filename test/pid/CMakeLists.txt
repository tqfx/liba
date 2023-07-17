set(TARGET_PREFIX ${TARGET_PREFIX}pid_)

building(expert expert.c expert.cpp)
unittest(expert NAME pid_expert)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(expert ../3.gp expert.log)
endif()

building(fuzzy fuzzy.c fuzzy.cpp)
unittest(fuzzy NAME pid_fuzzy)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(fuzzy ../3.gp fuzzy.log)
endif()

building(neuron neuron.c neuron.cpp)
unittest(neuron NAME pid_neuron)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(neuron ../3.gp neuron.log)
endif()
