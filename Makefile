OBJS = common/geomx.o common/gl_helper.o common/image.o common/matrix.o common/mdebug.o common/mesh.o common/mtime.o common/particle.o common/point_set.o common/vector.o fluids/fluid.o fluids/fluid_system.o main.o
all: main

main: $(OBJS)
	g++ -o $@ $(OBJS) -lGL -lglut -lGLU -lglee -ljpeg

.o: $@.cpp $@.h
	g++ -c $<

clean: 
	rm -f $(OBJS) main
