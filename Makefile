#CC : le compilateur à utiliser
CC=g++

#CFLAGS : les options de compilation  (en C++ moderne, et voir les warning)
CFLAGS= -std=c++17 -Wall -g

# les fichiers sources : tous les fichiers présents dans src/
SRC=$(wildcard src/*.cpp)

# les fichiers objets (.o)
OBJ=$(patsubst src/%.cpp,obj/%.o,$(SRC))

#edition des liens : génération de l'exécutable à partir des .o 
bin/exe: $(OBJ)
	$(CC) $(OBJ) -o $@

# génération des .o à partir des .cpp et .hpp correspondants :
obj/main.o : src/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@
obj/%.o: src/%.cpp src/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

#nettoyage : destruction des .o et de l'exécutable
clean:
	rm obj/*.o bin/exe


