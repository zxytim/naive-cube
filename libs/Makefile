all: cube_math.o cube_image.o

cube_math.o: cube_math.h cube_math.cpp
	g++ -c cube_math.cpp -o cube_math.o -lGL -lglut -lGLU

cube_image.o: cube_image.h cube_image.cpp
	g++ -c cube_image.cpp -o cube_image.o -lGL -lglut -lGLU

clean:
	rm *.o -f
