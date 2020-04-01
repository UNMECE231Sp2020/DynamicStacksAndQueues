all: main.o
	g++ main.o -o run_saq

main.o: main.cpp StackDynamic.hpp QueueDynamic.hpp
	g++ -c main.cpp

clean:
	rm *.o
	rm run_saq
