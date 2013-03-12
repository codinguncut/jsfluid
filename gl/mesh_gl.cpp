
#include "../common/vector.h"
#include "../common/mesh.h"
#include "../common/mdebug.h"
#include <GL/glut.h>

void Mesh::DrawVertsCM ( float* viewmat, int a, int b )
{
	VertCM* v;

	glColor3f (1,0,0);
	glLoadMatrixf ( viewmat );
	glTranslatef ( mT.x, mT.y, mT.z );
	glBegin ( GL_POINTS );
	for (int n = a; n <= b; n++) {	
		v = GetVertCM (n);
		glVertex3f ( v->x, v->y, v->z );
		//glCallList ( m_GLObj );		
	}
	glEnd ();
}

void Mesh::DrawVertsFVF ( float* viewmat, int a, int b )
{
	VertFVF* v;
	glColor3f (1,0,0);
	glLoadMatrixf ( viewmat );
	glTranslatef ( mT.x, mT.y, mT.z );
	glBegin ( GL_POINTS );
	for (int n = a; n <= b; n++) {	
		v = GetVertFVF (n);
		glVertex3f ( v->x, v->y, v->z );
		//glCallList ( m_GLObj );		
	}
	glEnd ();
}

void Mesh::DrawFacesCM ( float* viewmat, int a, int b )
{
	FaceCM* f;
	VertCM* v;
	AttrNorm* vn;
	int noff = GetAttrOffset ( "norm" );
	glLoadMatrixf ( viewmat );
	glTranslatef ( mT.x, mT.y, mT.z );
	GLenum dm = GL_TRIANGLES;
	glBegin ( dm );
	f = GetFaceCM ( a );
	for (int n = a; n <= b; n++) {
		if ( f->v4 == -1 ) {
			if ( dm != GL_TRIANGLES ) {	glEnd (); glBegin ( GL_TRIANGLES ); dm = GL_TRIANGLES; }
			v = GetVertCM(f->v1);	vn = (AttrNorm*) ((char*) v + noff);
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			v = GetVertCM(f->v2);	vn = (AttrNorm*) ((char*) v + noff);
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			v = GetVertCM(f->v3);	vn = (AttrNorm*) ((char*) v + noff);
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
		} else {
			if ( dm != GL_QUADS )	{ glEnd (); glBegin ( GL_QUADS ); dm = GL_QUADS; }
			v = GetVertCM(f->v1);	vn = (AttrNorm*) ((char*) v + noff);
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			v = GetVertCM(f->v2);	vn = (AttrNorm*) ((char*) v + noff);
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			v = GetVertCM(f->v3);	vn = (AttrNorm*) ((char*) v + noff);
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			v = GetVertCM(f->v4);	vn = (AttrNorm*) ((char*) v + noff);
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
		}
		f++;
	}	
	glEnd ();
}

void Mesh::DrawFacesFVF ( float* viewmat, int a, int b )
{
	FaceFVF* f;
	VertFVF* v;
	AttrNorm* vn;
	AttrClr* vc;
	int noff = GetAttrOffset ( "norm" );
	int coff = GetAttrOffset ( "color" );
	coff = -1;

	//glLoadMatrixf ( viewmat );
	//glTranslatef ( mT.x, mT.y, mT.z );
	GLenum dm = GL_TRIANGLES;
	glBegin ( dm );
	f = GetFaceFVF ( a );
	for (int n = a; n <= b; n++) {
		if ( f->v4 == -1 ) {
			if ( dm != GL_TRIANGLES ) {	glEnd (); glBegin ( GL_TRIANGLES ); dm = GL_TRIANGLES; }
			v = GetVertFVF(f->v1);	vn = (AttrNorm*) ((char*) v + noff);	vc = (AttrClr*) ((char*) v +coff);
			if ( coff != -1 ) glColor4f ( RED(vc->clr), GRN(vc->clr), BLUE(vc->clr), ALPH(vc->clr) );
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			
			v = GetVertFVF(f->v2);	vn = (AttrNorm*) ((char*) v + noff);	vc = (AttrClr*) ((char*) v +coff);
			if ( coff != -1 ) glColor4f ( RED(vc->clr), GRN(vc->clr), BLUE(vc->clr), ALPH(vc->clr) );
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			
			v = GetVertFVF(f->v3);	vn = (AttrNorm*) ((char*) v + noff);	vc = (AttrClr*) ((char*) v +coff);
			if ( coff != -1 ) glColor4f ( RED(vc->clr), GRN(vc->clr), BLUE(vc->clr), ALPH(vc->clr) );
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
		} else {
			if ( dm != GL_QUADS )	{ glEnd (); glBegin ( GL_QUADS ); dm = GL_QUADS; }
			v = GetVertFVF(f->v1);	vn = (AttrNorm*) ((char*) v + noff);	vc = (AttrClr*) ((char*) v +coff);
			if ( coff != -1 ) glColor4f ( RED(vc->clr), GRN(vc->clr), BLUE(vc->clr), ALPH(vc->clr) );
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			
			v = GetVertFVF(f->v2);	vn = (AttrNorm*) ((char*) v + noff);	vc = (AttrClr*) ((char*) v +coff);
			if ( coff != -1 ) glColor4f ( RED(vc->clr), GRN(vc->clr), BLUE(vc->clr), ALPH(vc->clr) );
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			
			v = GetVertFVF(f->v3);	vn = (AttrNorm*) ((char*) v + noff);	vc = (AttrClr*) ((char*) v +coff);
			if ( coff != -1 ) glColor4f ( RED(vc->clr), GRN(vc->clr), BLUE(vc->clr), ALPH(vc->clr) );
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
			
			v = GetVertFVF(f->v4);	vn = (AttrNorm*) ((char*) v + noff);	vc = (AttrClr*) ((char*) v +coff);
			if ( coff != -1 ) glColor4f ( RED(vc->clr), GRN(vc->clr), BLUE(vc->clr), ALPH(vc->clr) );
			glNormal3f ( vn->nx, vn->ny, vn->nz );	glVertex3f ( v->x, v->y, v->z );
		}
		f++;
	}	
	glEnd ();
}

void Mesh::DrawEdgesCM ( float* viewmat, int a, int b )
{
	EdgeCM* e;
	
	glLoadMatrixf ( viewmat );
	glTranslatef ( mT.x, mT.y, mT.z );
	glBegin ( GL_LINES );
	e = GetEdgeCM ( a );
	for (int n = a; n <= b; n++) {
		glVertex3f ( GetVertCM(e->v1)->x, GetVertCM(e->v1)->y, GetVertCM(e->v1)->z );
		glVertex3f ( GetVertCM(e->v2)->x, GetVertCM(e->v2)->y, GetVertCM(e->v2)->z );
		e++;
	}
	glEnd ();
}

void Mesh::DrawGL ( float* viewmat )
{
	mT.Set(0,0,0);
	
	switch ( m_Mform ) {
	case CM: {
		glDepthRange (0.001, 1.001);
		//glColor3f ( 1, 0, 0 );		DrawVertsCM ( viewmat, 0, NumVert()-1 );
		glColor3f ( .6, .6, .6 );	DrawFacesCM ( viewmat, 0, NumFace()-1 );
		//glDepthRange (0.0005, 1.0005);
		//glColor3f ( 1, 1, 1);		DrawEdgesCM ( viewmat, 0, NumEdge()-1 );	
		} break;
	case FVF: { 
		//glColor3f (1,0,0);			DrawVertsFVF ( viewmat, 0, NumVert()-1 );
		//glEnable (GL_LIGHTING);
		
		glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
		glColor4f ( .9, .9, .9, 0.75 );	DrawFacesFVF ( viewmat, 0, NumFace()-1 );

		/*glDisable (GL_LIGHTING );
		glDepthRange (0.000, 1.00);
		glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
		glLineWidth ( 3 );
		glColor4f ( 0, 0, 0, 1.0 );	DrawFacesFVF ( viewmat, 0, NumFace()-1 );		
		glEnable ( GL_LIGHTING );

		glLineWidth ( 1);

		glDepthRange (0.0, 1.0);
		glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );*/

		} break;
	}
}

void Mesh::DrawFaceGL ( float* viewmat )
{
	mT.Set (0,0,0);
	if ( m_CurrF < 0 ) m_CurrF = NumFace()-1;
	if ( m_CurrF >= NumFace() ) m_CurrF = 0;
	
	switch ( m_Mform ) {
	case FVF: 
		glDepthRange (0.0, 1.0); glColor3f (1.0, 1.0, 1.0 );	
		DrawFacesFVF ( viewmat, m_CurrF, m_CurrF );
		break;
	case CM:
		glDepthRange (0.0, 1.0); glColor3f (1.0, 1.0, 1.0 );	
		DrawFacesCM ( viewmat, m_CurrF, m_CurrF );
		break;
	};
}


