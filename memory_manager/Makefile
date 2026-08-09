memory_pool.o : memory_pool.h
	g++ -c memory_pool.h -o $@

executable_fixed:
	g++ memory_pool.h fixed_memory.h fixed_memory.cpp -o $@

executable_variable:
	g++ memory_pool.h variable_memory.h variable_memory.cpp -o $@
clean:
	rm -rf *.o *.gch executable_fixed executable_variable