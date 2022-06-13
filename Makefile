# Homework 2
EXE=hw2

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lglfw3 -lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
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
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $< -I./include

#  Link
hw2: model.o texture.o stb_image.o camera.o mesh.o ebo.o vao.o vbo.o perspective_camera.o shader.o orthographic_camera.o app.o hw2.o
	g++ $(CFLG) -o $@ $^  $(LIBS) 

#  Clean
clean:
	$(CLEAN)
