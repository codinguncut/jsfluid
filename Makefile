COMMON_OBJS = common/geomx.o common/matrix.o common/mdebug.o common/mesh.o common/particle.o common/point_set.o common/vector.o 
FLUIDS_OBJS = fluids/fluid_system.o
GL_OBJS     = gl/point_set_gl.o gl/gl_helper.o gl/mesh_gl.o gl/fluid_system_gl.o common/mtime.o 
OBJS				= $(COMMON_OBJS) $(FLUIDS_OBJS) $(GL_OBJS)
CC					= g++
EMCC_OPTS		= -O2 --minify 1 -s TOTAL_MEMORY=128000000 --pre-js pre.js -s EXPORTED_FUNCTIONS="['_step', '_init', '_get_points', '_get_num_points']"

all: jsfluid.js

jsfluid: $(COMMON_OBJS) $(FLUIDS_OBJS) jsfluid.o
	$(CC) -o $@ $(COMMON_OBJS) $(FLUIDS_OBJS) jsfluid.o

jsfluid.bc: $(COMMON_OBJS) $(FLUIDS_OBJS) jsfluid.o
	em++ -o $@ $(COMMON_OBJS) $(FLUIDS_OBJS) jsfluid.o

jsfluid.js: jsfluid.bc pre.js
	emcc -o $@ $< $(EMCC_OPTS)

.o: $@.cpp $@.h
	$(CC) -c $<

clean: 
	rm -f $(OBJS) jsfluid jsfluid.bc jsfluid.html jsfluid.o
