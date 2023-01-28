VPATH=src:src/*
EXE=hw2

BIN    	:= ./bin
SRC     := ./src
OBJ	 	:= ./obj
# Find all source files cpp
SRCS  	:= $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*/*.cpp)
# Replace the source path with the object path
OBJS    := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))

# Main target
all: main

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
MKDIR := md
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lglfw3 -lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=del /Q /S *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES)
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall -DGL_GLEXT_PROTOTYPES
LIBS=-lglfw -lglut -lGLU -lGL -lm
endif

MKDIR := mkdir -p
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Compile rules
$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	g++ -c $(CFLG) $< -I./include -o $@

#  Link
main: $(OBJS) | $(BIN)
	g++ $(CFLG) $^ -o $(BIN)/$(EXE) $(LIBS) 

#  Clean
clean:
	$(CLEAN)

# Create directories
$(BIN):
	$(MKDIR) $@

$(OBJ):
	$(MKDIR) "$@/engine"

run: main
	$(BIN)/$(EXE)
