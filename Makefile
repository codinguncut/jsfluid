COMMON_OBJS = common/geomx.o common/matrix.o common/mdebug.o common/mesh.o common/mtime.o common/particle.o common/point_set.o common/vector.o 
FLUIDS_OBJS = fluids/fluid_system.o
GL_OBJS     = gl/point_set_gl.o gl/gl_helper.o gl/mesh_gl.o gl/fluid_system_gl.o
OBJS				= $(COMMON_OBJS) $(FLUIDS_OBJS) $(GL_OBJS)
CC					= g++

all: main

main: $(OBJS) main.o
	$(CC) -o $@ $(OBJS) main.o -lGL -lglut -lGLU #-ljpeg #-lglee 

main_mini: $(OBJS) main_mini.o
	$(CC) -o $@ $(OBJS) main_mini.o -lGL -lglut -lGLU #-ljpeg #-lglee 

main_mini.bc: $(OBJS) main_mini.o
	em++ -o $@ $(OBJS) main_mini.o

main_mini.js: main_mini.bc
	emcc -o $@ $<

main_mini.html: main_mini.bc
	emcc -o $@ $< -s TOTAL_MEMORY=128000000

.o: $@.cpp $@.h
	$(CC) -c $<

clean: 
	rm -f $(OBJS) main main.bc main.js main.html main_mini main_mini.bc main_mini.js main_mini.html main.o main_mini.o
