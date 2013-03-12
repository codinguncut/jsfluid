COMMON_OBJS = common/geomx.o common/matrix.o common/mdebug.o common/mesh.o common/particle.o common/point_set.o common/vector.o 
FLUIDS_OBJS = fluids/fluid_system.o
GL_OBJS     = gl/point_set_gl.o gl/gl_helper.o gl/mesh_gl.o gl/fluid_system_gl.o common/mtime.o 
OBJS				= $(COMMON_OBJS) $(FLUIDS_OBJS) $(GL_OBJS)
CC					= g++
EMCC_OPTS		= --pre-js pre.js -s EXPORTED_FUNCTIONS="['_step', '_init', '_get_points', '_get_num_points']"

all: main_mini

main: $(OBJS) main.o
	$(CC) -o $@ $(OBJS) main.o -lGL -lglut -lGLU #-ljpeg #-lglee 

main_mini: $(COMMON_OBJS) $(FLUIDS_OBJS) main_mini.o
	$(CC) -o $@ $(COMMON_OBJS) $(FLUIDS_OBJS) main_mini.o

main_mini.bc: $(COMMON_OBJS) $(FLUIDS_OBJS) main_mini.o
	em++ -o $@ $(COMMON_OBJS) $(FLUIDS_OBJS) main_mini.o

main_mini.js: main_mini.bc pre.js
	emcc -o $@ $< $(EMCC_OPTS)

main_mini.html: main_mini.bc pre.js
	emcc -o $@ $< $(EMCC_OPTS)

.o: $@.cpp $@.h
	$(CC) -c $<

clean: 
	rm -f $(OBJS) main main.bc main.js main.html main_mini main_mini.bc main_mini.js main_mini.html main.o main_mini.o
