SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c

# ************ Generación de documentación ******************
# documentacion:
# 	doxygen doc/doxys/Doxyfile

all: $(BIN)/ejecutable

$(BIN)/ejecutable: $(OBJ)/rutas_aereas.o $(OBJ)/imagenES.o $(OBJ)/imagen.o
	$(CXX) -o $(BIN)/ejecutable $(OBJ)/rutas_aereas.o $(OBJ)/imagenES.o $(OBJ)/imagen.o

$(OBJ)/rutas_aereas.o: $(SRC)/rutas_aereas.cpp $(INC)/imagen.h  $(INC)/Paises.h  $(INC)/AlmacenRutas.h
	$(CXX) $(CPPFLAGS) $(SRC)/rutas_aereas.cpp -o $(OBJ)/rutas_aereas.o

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $(SRC)/imagen.cpp -o $(OBJ)/imagen.o

$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp $(INC)/imagenES.h
	$(CXX) $(CPPFLAGS) $(SRC)/imagenES.cpp -o $(OBJ)/imagenES.o

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(BIN)/*

mrproper : clean
	-rm $(BIN)/* doc/html/*
