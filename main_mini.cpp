/*
  FLUIDS v.1 - SPH Fluid Simulator for CPU and GPU
  Copyright (C) 2008. Rama Hoetzlein, http://www.rchoetzlein.com

  ZLib license
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "common/common_defs.h"

#include "fluids/fluid_system.h"

bool bTiming = false;
bool bRec = false;
int mFrame = 0;

// Globals
FluidSystem			psys;

float window_width  = 1024;
float window_height = 768;

Vector3DF	cam_from, cam_angs, cam_to;			// Camera stuff
Vector3DF	obj_from, obj_angs, obj_dang;
Vector3DF	light[2], light_to[2];				// Light stuff
float		light_fov, cam_fov;	

int		psys_rate = 0;							// Particle stuff
int		psys_freq = 1;
int		psys_demo = 0;
int		psys_nmax = 4096;

bool	bHelp = false;						// Toggles
int		iShade = 1;			
int		iClrMode = 0;
bool	bPntDraw = false;
bool    bPause = false;

// View matricies
float view_matrix[16];					// View matrix (V)
float model_matrix[16];					// Model matrix (M)
float proj_matrix[16];					// Projective matrix

// Mouse control
#define DRAG_OFF		0				// mouse states
#define DRAG_LEFT		1
#define DRAG_RIGHT		2
int		last_x = -1, last_y = -1;		// mouse vars
int		mode = 0;
int		dragging = 0;
int		psel;

// Different things we can move around
#define MODE_CAM		0
#define MODE_CAM_TO		1
#define MODE_OBJ		2
#define MODE_OBJPOS		3
#define MODE_OBJGRP		4
#define MODE_LIGHTPOS	5

#define MODE_DOF		6

void drawScene ( float* viewmat, bool bShade )
{
  //psys.Draw ( &viewmat[0], 0.55 );			// Draw particles
}

int frame;

void display () 
{
	// Do simulation!
	if ( !bPause ) psys.Run ();
  printf("display %d\n", psys.NumPoints());

  char *dat;
  Point *p;
  dat = psys.mBuf[0].data;
  for (int i = 0; i < psys.NumPoints(); i++) {
	  p = (Point*) dat;
	  printf("pos: (%f, %f, %f)\n",  p->pos.x, p->pos.y, p->pos.z);
    dat += psys.mBuf[0].stride; 
  }

	frame++;
}

void UpdateEmit ()
{	
	obj_from = psys.GetVec ( EMIT_POS );
	obj_angs = psys.GetVec ( EMIT_ANG );
	obj_dang = psys.GetVec ( EMIT_RATE );
}


void init ()
{
	srand ( time ( 0x0 ) );

  /*
	cam_angs.x = 29;		cam_angs.y = 75;		cam_angs.z = 80.0;
	cam_to.x = 0;		cam_to.y = 0;		cam_to.z = 5;
	cam_fov = 35.0;

	light[0].x = 39;		light[0].y = -60;	light[0].z = 43;
	light_to[0].x = 0;	light_to[0].y = 0;	light_to[0].z = 0;

	light[1].x = 15;		light[1].y = -5;	light[1].z = 145;	
	light_to[1].x = 0;	light_to[1].y = 0;	light_to[1].z = 0;  

	light_fov = 45;

  */
	obj_from.x = 0;		obj_from.y = 0;		obj_from.z = 20;		// emitter
	obj_angs.x = 118.7;	obj_angs.y = 200;	obj_angs.z = 1.0;
	obj_dang.x = 1;	obj_dang.y = 1;		obj_dang.z = 0;

	psys.Initialize ( BFLUID, psys_nmax );
	psys.SPH_CreateExample ( 0, psys_nmax );
	psys.SetVec ( EMIT_ANG, Vector3DF ( obj_angs.x, obj_angs.y, obj_angs.z ) );
	psys.SetVec ( EMIT_POS, Vector3DF ( obj_from.x, obj_from.y, obj_from.z ) );

	psys.SetParam ( PNT_DRAWMODE, int(bPntDraw ? 1:0) );
	psys.SetParam ( CLR_MODE, iClrMode );	

  while (true) {
    display();    
  }
}


int main ( int argc, char **argv )
{
	init();
  return 0;
}
