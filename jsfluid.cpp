/*
  FLUIDS v.1 - SPH Fluid Simulator for CPU and GPU
  Copyright (C) 2008. Rama Hoetzlein, http://www.rchoetzlein.com

  ZLib license
*/

#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "common/common_defs.h"

#include "fluids/fluid_system.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

// Globals
FluidSystem			psys;

Vector3DF	obj_from, obj_angs, obj_dang;

const int		psys_nmax = 512;
int		iClrMode = 0;
bool	bPntDraw = false;
bool    bPause = false;
int frame;


void PointSet::Draw ( float* view_mat, float rad )
{
}

extern "C" {
float cpoints[psys_nmax*3];

int get_num_points() {
  return psys.NumPoints();
}

float *get_points() {
  char *dat;
  Point *p;
  float *cp;

  dat = psys.mBuf[0].data;
  for (int i = 0; i < psys.NumPoints(); i++) {
	  p = (Point*) dat;
    cpoints[i*3+0] = p->pos.x;
    cpoints[i*3+1] = p->pos.y;
    cpoints[i*3+2] = p->pos.z;
    dat += psys.mBuf[0].stride; 
  }
  return cpoints;
}

void step () 
{
	psys.Run();
	frame++;
}


void init ()
{
	srand ( time ( 0x0 ) );
	
  obj_from.x = 0;		obj_from.y = 0;		obj_from.z = 20;		// emitter
	obj_angs.x = 118.7;	obj_angs.y = 200;	obj_angs.z = 1.0;

	psys.Initialize ( BFLUID, psys_nmax );
	psys.SPH_CreateExample ( 0, psys_nmax );
	psys.SetVec ( EMIT_ANG, Vector3DF ( obj_angs.x, obj_angs.y, obj_angs.z ) );
	psys.SetVec ( EMIT_POS, Vector3DF ( obj_from.x, obj_from.y, obj_from.z ) );

	psys.SetParam ( PNT_DRAWMODE, int(bPntDraw ? 1:0) );
	psys.SetParam ( CLR_MODE, iClrMode );	
}

void run()
{
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(step, 60, true);
#else
  while (true) {
    step();    
  }
#endif
}
} // extern "C"

int main ( int argc, char **argv )
{
	init();
  return 0;
}
