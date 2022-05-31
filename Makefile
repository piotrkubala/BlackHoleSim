GPP=g++
FLAGS=-O3

DIR=src/

BlackHoleSim: $(DIR)main.o $(DIR)gameWindow.o
	$(GPP) $(FLAGS) $(DIR)main.o $(DIR)gameWindow.o -o BlackHoleSim

main.o: $(DIR)main.cpp $(DIR)gameWindow.hpp
	$(GPP) $(FLAGS) $(DIR)main.cpp -c -o $(DIR)main.o

gameWindow.o: $(DIR)gameWindow.cpp $(DIR)gameWindow.hpp
	$(GPP) $(FLAGS) $(DIR)gameWindow.cpp -c -o $(DIR)gameWindow.o


clean:
	rm *.o

