.PHONY: libs all

all: cube

cube: libs
	g++ -o cube main.cpp libs/*.o -lGL -lglut -lGLU

libs:
	cd libs && make

clean:
	cd libs && make clean
	rm -f cube
