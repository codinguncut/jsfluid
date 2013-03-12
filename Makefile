COMMON_OBJS = common/geomx.o common/matrix.o common/mdebug.o common/mesh.o common/mtime.o common/particle.o common/point_set.o common/vector.o 
FLUIDS_OBJS = fluids/fluid_system.o
MAIN_OBJS   = main.o
GL_OBJS     = gl/point_set_gl.o gl/gl_helper.o gl/mesh_gl.o gl/fluid_system_gl.o
OBJS				= $(COMMON_OBJS) $(FLUIDS_OBJS) $(MAIN_OBJS) $(GL_OBJS)
CC					= g++

all: main

main: $(OBJS)
	$(CC) -o $@ $(OBJS) -lGL -lglut -lGLU #-ljpeg #-lglee 

main.bc: $(OBJS)
	em++ -o $@ $(OBJS)

main.js: main.bc
	emcc -o $@ $<

main.html: main.bc
	emcc -o $@ $< -s TOTAL_MEMORY=128000000

.o: $@.cpp $@.h
	$(CC) -c $<

clean: 
	rm -f $(OBJS) main main.bc main.js main.html
