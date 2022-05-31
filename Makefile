GPP=g++
FLAGS=-O3 -Wall

DIR=src/

LIB=-lsfml-graphics -lsfml-window -lsfml-system

BlackHoleSim: $(DIR)main.o $(DIR)gameWindow.o
	$(GPP) $(FLAGS) $(DIR)main.o $(DIR)gameWindow.o $(LIB) -o BlackHoleSim

main.o: $(DIR)main.cpp $(DIR)gameWindow.hpp
	$(GPP) $(FLAGS) $(DIR)main.cpp -c -o $(DIR)main.o

gameWindow.o: $(DIR)gameWindow.cpp $(DIR)gameWindow.hpp
	$(GPP) $(FLAGS) $(DIR)gameWindow.cpp -c -o $(DIR)gameWindow.o


clean:
	rm $(DIR)*.o 2> /dev/null

