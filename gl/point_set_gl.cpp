
#include "gl_helper.h"
#include "../common/point_set.h"

void PointSet::Draw ( float* view_mat, float rad )
{
	char* dat;
	Point* p;
	glEnable ( GL_NORMALIZE );	

	if ( m_Param[PNT_DRAWMODE] == 0 ) {
		glLoadMatrixf ( view_mat );
		dat = mBuf[0].data;	
		for (int n = 0; n < NumPoints(); n++) {
			p = (Point*) dat;
			glPushMatrix ();
			glTranslatef ( p->pos.x, p->pos.y, p->pos.z );		
			glScalef ( 0.2, 0.2, 0.2 );			
			glColor4f ( RED(p->clr), GRN(p->clr), BLUE(p->clr), ALPH(p->clr) );
			drawSphere ();
			glPopMatrix ();		
			dat += mBuf[0].stride;
		}	
	} else if ( m_Param[PNT_DRAWMODE] == 1 ) {
		glLoadMatrixf ( view_mat );
		dat = mBuf[0].data;
		glBegin ( GL_POINTS );
		for (int n=0; n < NumPoints(); n++) {
			p = (Point*) dat;
			glColor3f ( RED(p->clr), GRN(p->clr), BLUE(p->clr) );			
			glVertex3f ( p->pos.x, p->pos.y, p->pos.z );			
			dat += mBuf[0].stride;
		}
		glEnd ();
	}
}

void PointSet::Grid_Draw ( float* view_mat )
{
	float clr;
	int cx, cy, cz;
	float x1, y1, z1;
	float x2, y2, z2;
	int g = 0;

	glLoadMatrixf ( view_mat );
	glColor3f ( 0.7, 0.7, 0.7 );

	glBegin ( GL_LINES );	

	cz = 0;
	//for ( cz = 0; cz < m_GridRes.z; cz++ ) {
	for ( cy = 0; cy < m_GridRes.y; cy++ ) {
	for ( cx = 0; cx < m_GridRes.x; cx++ ) {
		// Cell is not empty. Process it.
		//if ( m_Grid[g] != 0x0 ) {
		//	clr = m_GridCnt[g]/30.0;
			clr = 0.25;
			if ( clr <0.25) clr =0.25;
			if ( clr >1) clr =1 ;
			glColor3f ( clr, clr, clr );
			x1 = (cx * m_GridDelta.x) + m_GridMin.x;		x2 = ((cx+1) * m_GridDelta.x) + m_GridMin.x;
			y1 = (cy * m_GridDelta.y) + m_GridMin.y;		y2 = ((cy+1) * m_GridDelta.y) + m_GridMin.y;
			z1 = (cz * m_GridDelta.z) + m_GridMin.z;		z2 = ((cz+1) * m_GridDelta.z) + m_GridMin.z;
			glVertex3f ( x1, y1, z1 );			glVertex3f ( x2, y1, z1 );
			glVertex3f ( x2, y1, z1 );			glVertex3f ( x2, y2, z1 );
			glVertex3f ( x2, y2, z1 );			glVertex3f ( x1, y2, z1 );
			glVertex3f ( x1, y2, z1 );			glVertex3f ( x1, y1, z1 );
			glVertex3f ( x1, y1, z2 );			glVertex3f ( x2, y1, z2 );
			glVertex3f ( x2, y1, z2 );			glVertex3f ( x2, y2, z2 );
			glVertex3f ( x2, y2, z2 );			glVertex3f ( x1, y2, z2 );
			glVertex3f ( x1, y2, z2 );			glVertex3f ( x1, y1, z2 );
			glVertex3f ( x1, y1, z1 );			glVertex3f ( x1, y1, z2 );
			glVertex3f ( x1, y2, z1 );			glVertex3f ( x1, y2, z2 );
			glVertex3f ( x2, y2, z1 );			glVertex3f ( x2, y2, z2 );
			glVertex3f ( x2, y1, z1 );			glVertex3f ( x2, y1, z2 );
		//}
		g++;
	}
	}
	//}

	glEnd ();
}

