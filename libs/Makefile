
CXX = g++
LIBS = -lGL -lglut -lGLU -g
OBJS = cube_math.o cube_image.o cube_time.o cube_structure.o cube_config.o \
	   cube_color.o

all: $(OBJS)

cube_math.o: cube_math.h cube_math.cpp
	g++ -c cube_math.cpp -o cube_math.o $(LIBS)

cube_image.o: cube_image.h cube_image.cpp
	g++ -c cube_image.cpp -o cube_image.o $(LIBS) 

cube_time.o: cube_time.h cube_time.cpp
	g++ -c cube_time.cpp -o cube_time.o $(LIBS)

cube_structure.o: cube_structure.h cube_structure.cpp
	g++ -c cube_structure.cpp -o cube_structure.o $(LIBS)

cube_config.o: cube_config.h cube_config.cpp
	g++ -c cube_config.cpp -o cube_config.o $(LIBS)

cube_color.o: cube_color.h cube_color.cpp
	g++ -c cube_color.cpp -o cube_color.o $(LIBS)

clean:
	rm *.o -f
