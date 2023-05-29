#makefile 
PROG ?= ep3
OBJS := ep3.o
LIBS := ep3.hpp
CXXFLAGS := -Wall -O0
CXX := g++

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $< -o $@ 
		
ep3.o: ep3.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

