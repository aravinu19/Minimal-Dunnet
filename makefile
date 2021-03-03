#Makefile for Dunnet Clone (Generic MAP version)

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -O0 -g3 -std=c++14

All: all
all: main

main: main.cpp MapHandler.hpp game.hpp state.hpp DataModels.hpp
	$(CXX) $(CXXFLAGS) main.cpp MapHandler.hpp game.hpp state.hpp DataModels.hpp -o main

test: main.cpp MapHandler.hpp game.hpp state.hpp DataModels.hpp
	$(CXX) $(CXXFLAGS) main.cpp MapHandler.hpp game.hpp state.hpp DataModels.hpp -o game

deepclean:
	rm -f *~ *.o main *.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump main

clean-win:
	del /F *~ *.o *.exe *.stackdump