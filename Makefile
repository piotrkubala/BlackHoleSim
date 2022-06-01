GPP=g++
FLAGS=-O3 -Wall

DIR=src/

LIB=-lsfml-graphics -lsfml-window -lsfml-system

BlackHoleSim: $(DIR)main.o $(DIR)gameWindow.o $(DIR)observer.o
	$(GPP) $(FLAGS) $(DIR)main.o $(DIR)gameWindow.o $(DIR)observer.o $(LIB) -o BlackHoleSim

main.o: $(DIR)main.cpp $(DIR)gameWindow.hpp
	$(GPP) $(FLAGS) $(DIR)main.cpp -c -o $(DIR)main.o

gameWindow.o: $(DIR)gameWindow.cpp $(DIR)gameWindow.hpp $(DIR)observer.hpp
	$(GPP) $(FLAGS) $(DIR)gameWindow.cpp -c -o $(DIR)gameWindow.o

observer.o: $(DIR)observer.cpp $(DIR)observer.hpp
	$(GPP) $(FLAGS) $(DIR)observer.cpp -c -o $(DIR)observer.o

clean:
	rm $(DIR)*.o 2> /dev/null

