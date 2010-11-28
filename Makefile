.PHONY: libs all

LIBS = -lGL -lglut -lGLU -g 
all: cube

cube: libs cube.h
	g++ -o cube main.cpp libs/*.o $(LIBS) -DDEBUG

cube.h: const.h

libs:
	cd libs && make

clean:
	cd libs && make clean
	rm -f cube

run: cube
	./cube

gdb: libs cube.h
	g++ -o cube main.cpp libs/*.o $(LIBS) -DDEBUG
	gdb ./cube


