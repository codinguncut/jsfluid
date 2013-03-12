COMMON_OBJS = common/geomx.o common/matrix.o common/mdebug.o common/mesh.o common/mtime.o common/particle.o common/point_set.o common/vector.o 
FLUIDS_OBJS = fluids/fluid_system.o
MAIN_OBJS   = main.o
GL_OBJS     = gl/point_set_gl.o gl/gl_helper.o gl/mesh_gl.o gl/fluid_system_gl.o
OBJS				= $(COMMON_OBJS) $(FLUIDS_OBJS) $(MAIN_OBJS) $(GL_OBJS)
all: main

main: $(OBJS)
	g++ -o $@ $(OBJS) -lGL -lglut -lGLU -lglee -ljpeg

.o: $@.cpp $@.h
	g++ -c $<

clean: 
	rm -f $(OBJS) main
