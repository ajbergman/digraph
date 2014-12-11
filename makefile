CPPFLAGS=-std=c++11 -g -O3 -Wall
EXECUTABLE=wgraph

all: $(EXECUTABLE)

$(EXECUTABLE): Main.o WeightedDigraph.o	
	g++ $(CPPFLAGS) Main.o WeightedDigraph.o -o $(EXECUTABLE)

WeightedDigraph.o: WeightedDigraph.cpp WeightedDigraph.h
	g++ $(CPPFLAGS) -c WeightedDigraph.cpp

Main.o: Main.cpp WeightedDigraph.o
	g++ $(CPPFLAGS) -c Main.cpp

clean: 
	rm -f *.o $(EXECUTABLE)
