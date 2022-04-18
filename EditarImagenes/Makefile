SRC = src
INC = inc
OBJ = obj
BIN = bin
LIB = lib
CXX = g++
CPPFLAGS = -Wall -g -I$(INC) -c

NAME = main

all: $(BIN)/$(NAME)
# *********************+ Compilacion de modulos ***************
$(BIN)/$(NAME): $(OBJ)/$(NAME).o $(LIB)/$(LIB)formas.a
	$(CXX) -L$(LIB)/ -o $(BIN)/$(NAME) $(OBJ)/$(NAME).o -lformas

$(OBJ)/$(NAME).o: $(SRC)/$(NAME).cpp $(INC)/Imagen.h
	$(CXX) $(CPPFLAGS) $(SRC)/$(NAME).cpp -o $(OBJ)/$(NAME).o

$(OBJ)/Imagen.o: $(SRC)/Imagen.cpp $(INC)/Imagen.h
	$(CXX) $(CPPFLAGS) $(SRC)/Imagen.cpp -o $(OBJ)/Imagen.o

$(LIB)/$(LIB)formas.a: $(OBJ)/Imagen.o
		ar rsv $(LIB)/$(LIB)formas.a $(OBJ)/Imagen.o

# ******************* Limpieza *******************
clean:
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~