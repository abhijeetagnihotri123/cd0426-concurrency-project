memory_pool.o : memory_pool.h
	g++ -c memory_pool.h -o $@

executable:
	g++ memory_pool.h fixed_memory.h fixed_memory.cpp -o $@

clean:
	rm -rf *.o *.gch executable