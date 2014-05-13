#if defined(__APPLE__)
	#include <UpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/freeglut.h>
#endif

#include <iostream>
#include <cmath>
#include "model.h"
using namespace std;

//variables
// ------------------bloc1.4-----------------
int actualx, actualy, oldx, oldy, oldz, tam, w, h;	//tam = tamany window
float r = 0.0;						//colors window
float g = 0.389;
float b = 0.0;
// ------------------bloc1.5-----------------
float x1, yy1, x2, y2, x3, y3;			//punts del triangle a dibuixar (z1, z2 i z3 = 0) //yy1 porque cmath no me deja y1
float X1, Y1, X2, Y2, X3, Y3;			//punts del triangle original
int count3 = 0;
//-------------------bloc2.1-----------------
double size = 0.5;				//tamany tetera
double rotx, roty, rotz = 0.;			//variables glRotated
int anglex, angley;
bool inspect = false;
//------------------bloc2.2------------------
bool translate = false;
float newx, newy;							//noves posicions moviment Translated
//-------------------------------------------
bool scaley = false;
bool scalez = false;
double actx = 1.;
double acty = 1.;
double actz = 1.;
//------------------bloc2.3------------------
double radiusBase = .4;
int slices = 40;
int stacks = 30;
double radiusHead = .2;
float translateHeadX = 0.;
float translateHeadY = .6;
float translateHeadZ = 0.;
double radiusCone = .1;
double heightCone = .2;
float translateConeX = .1;
float translateConeY = .6;
float translateConeZ = 0.;
int angleCone = 90;	

//------------------bloc2.4------------------
Model m;
bool first = true;
double xmax, xmin, ymax, ymin, zmax, zmin;
double centrox, centroy, centroz;
double tamx, tamy, tamz, diametro;
//------------------bloc2.5------------------
float longitudSuelo = 10.;
float lado = longitudSuelo/2.;
double escalado;
double tamanyQueVolem = 1.;						//tamany del model
double subirBase;
bool changeState = false;
float newx2, newz2;
double ancho_escalado, alto_escalado, profundo_escalado;
//------------------bloc3.2------------------
double extremTerra = sqrt((lado*lado) + (lado*lado));
double tamEsferaCont = sqrt((extremTerra*extremTerra) + (1.2*1.2));	//se calcula a mano
double FOV, FOV2, RAw, RA, zN, zF, d, R;				//gluPerspective(FOV, RA, zN, zF);
bool changeCam = true;							//axonometrica
double VRPx, VRPy, VRPz;						//perspectiva
//------------------bloc3.7------------------
//longitudSuelo cambia de 1.5 a 10.;
//tamanyQueVolem pasa de 0.5 a 1, pero no de alto, sino su mayor longitud
double tamanyQueVolem2 = 1.5;
double escalado2;
bool first2 = true;
double subirBase2;
double ancho_escalado2, alto_escalado2, profundo_escalado2;
double centrox2, centroy2, centroz2;
double tamx2, tamy2, tamz2, diametro2;

//---PARET1---
double scalePared1X = 4.;
double scalePared1Y = 1.5;
double scalePared1Z = .2;

double translatePared1X = 2.5;
double translatePared1Y = 0.;
double translatePared1Z = -1.5;
//------------
//---PARET2---
double scalePared2X = .2;
double scalePared2Y = 1.5;
double scalePared2Z = 10.;

double translatePared2X = -4.9;
double translatePared2Y = 0.;
double translatePared2Z = 0.;
//------------
bool visible = true;
bool zoom = false;



//funciones
void initGL(int argc, const char * argv[]) {
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	tam = w = h = 600;
	glutInitWindowSize(w, h);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("IDI: Practiques OpenGL");
	X1 = -1/float(2);
	Y1 = -1/float(3);
	X2 = 1/float(2);
	Y2 = -1/float(3);
	X3 = 0;
	Y3 = 2/float(3);


	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	
	//----------INICIALIZAR OPTICA----(posicionar la camara)----------
	d = tamEsferaCont*2;						//me invento el valor inicial, ha de ser > radio
	R = tamEsferaCont;
	FOV = 2*(asin(R/d))*180/3.14;					//FOV en grados
	zN = d-R;
	zF = d+R;
	RAw = 1;							//porque es una circunferencia lo que tiene dentro
	VRPx = 0.;
	VRPy = 0.; 
	VRPz = 0.;
}

void pinta_model() {
	const int &n = m.faces().size();
	for (int i = 0; i < n; ++i) {
		const Face &f = m.faces()[i];
		glColor4fv(Materials[f.mat].diffuse);
		glBegin(GL_TRIANGLES);					//pintar triangle
		for (int j = 0; j < 3; ++j) {
			glVertex3dv(&m.vertices()[f.v[j]]);	
		}
		glEnd();
	}
}

void calcularCapsaMinimaContenidora() {
	first = false;
	const int &tam = m.vertices().size();
	const Vertex *v;
	const Face &f = m.faces()[0];
	v = &m.vertices()[f.v[0]];
	xmax = xmin = (*v);
	ymax = ymin = *(v+1);
	zmax = zmin = *(v+2);
	for (int i = 0; i < tam; i+=3) {
	       if (m.vertices()[i] > xmax) xmax = m.vertices()[i];
	       if (m.vertices()[i+1] > ymax) ymax = m.vertices()[i+1];
	       if (m.vertices()[i+2] > zmax) zmax = m.vertices()[i+2];
	       if (m.vertices()[i] < xmin) xmin = m.vertices()[i];
	       if (m.vertices()[i+1] < ymin) ymin = m.vertices()[i+1];
	       if (m.vertices()[i+2] < zmin) zmin = m.vertices()[i+2];
	}
	centrox = (xmax + xmin)/2.;
	centroy = (ymax + ymin)/2.;
	centroz = (zmax + zmin)/2.;
	
	tamx = xmax - xmin;					//tamx = ancho
	tamy = ymax - ymin;					//tamy = alto
	tamz = zmax - zmin;					//tamz = profundo

	diametro = sqrt((tamx*tamx) + (tamy*tamy) + (tamz*tamz));
	
	if (tamx >= tamy and tamx >= tamz) escalado = tamanyQueVolem/tamx;
	else if (tamy >= tamx and tamy >= tamz) escalado = tamanyQueVolem/tamy;
	else if (tamz >= tamx and tamz >= tamy) escalado = tamanyQueVolem/tamz;
	//escalado = tamanyQueVolem/dimensionMasGrande

	subirBase = tamanyQueVolem/2.;

	ancho_escalado = tamx*escalado;
	alto_escalado = tamy*escalado;
	profundo_escalado = tamz*escalado;
}

void calcularCapsaMinimaContenidora2() {
	first2 = false;
	const int &tam = m.vertices().size();
	const Vertex *v;
	const Face &f = m.faces()[0];
	v = &m.vertices()[f.v[0]];
	xmax = xmin = (*v);
	ymax = ymin = *(v+1);
	zmax = zmin = *(v+2);
	for (int i = 0; i < tam; i+=3) {
	       if (m.vertices()[i] > xmax) xmax = m.vertices()[i];
	       if (m.vertices()[i+1] > ymax) ymax = m.vertices()[i+1];
	       if (m.vertices()[i+2] > zmax) zmax = m.vertices()[i+2];
	       if (m.vertices()[i] < xmin) xmin = m.vertices()[i];
	       if (m.vertices()[i+1] < ymin) ymin = m.vertices()[i+1];
	       if (m.vertices()[i+2] < zmin) zmin = m.vertices()[i+2];
	}
	centrox2 = (xmax + xmin)/2.;
	centroy2 = (ymax + ymin)/2.;
	centroz2 = (zmax + zmin)/2.;
	
	tamx2 = xmax - xmin;					//tamx = ancho
	tamy2 = ymax - ymin;					//tamy = alto
	tamz2 = zmax - zmin;					//tamz = profundo

	diametro2 = sqrt((tamx2*tamx2) + (tamy2*tamy2) + (tamz2*tamz2));
	
	if (tamx2 >= tamy2 and tamx2 >= tamz2) escalado2 = tamanyQueVolem2/tamx2;
	else if (tamy2 >= tamx2 and tamy2 >= tamz2) escalado2 = tamanyQueVolem2/tamy2;
	else if (tamz2 >= tamx2 and tamz2 >= tamy2) escalado2 = tamanyQueVolem2/tamz2;
	//escalado2 = tamanyQueVolem2/dimensionMasGrande

	subirBase2 = tamanyQueVolem2/2.;

	ancho_escalado2 = tamx2*escalado2;
	alto_escalado2 = tamy2*escalado2;
	profundo_escalado2 = tamz*escalado2;
}


void refresh(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, 0);				//green 389

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0., 0., -d);
	glRotated(anglex, 1., 0., 0.);
	glRotated(angley, 0., 1., 0.);
	glTranslatef(-VRPx, -VRPy, -VRPz);

//---------------ESFERA CONTENEDORA ESCENA-------
	glPushMatrix();
	  glColor3f(.0, .0, .8);				//blue sphere
	  glutWireSphere(tamEsferaCont, slices, stacks);
	glPopMatrix();

//-----------------ESCENA FINAL------------------
//-----------------------------------------------
//---------------------Ninot1--------------------
	glPushMatrix();
		glTranslatef(2.5, radiusBase, 2.5);		//moure el ninot del (0., -.4, 0.) a on em demanen -> mesura 1 en total
		  
		  //-------Base-------
		  glPushMatrix();
		    glColor3f(1., 1., 1.);
		    glutWireSphere(radiusBase, slices, stacks);	
		  glPopMatrix();
		  //-------Head------
		  glPushMatrix();
		    glTranslatef(translateHeadX, translateHeadY, translateHeadZ);
		    glColor3f(.8, .8, 0.);			//yellow head
		    glutSolidSphere(radiusHead, slices, stacks);
		  glPopMatrix();
		  //-------Cone------
		  glPushMatrix();
		    glColor3f(.7, .3, .0);  
		    glTranslatef(translateConeX, translateConeY, translateConeZ);
		    glRotated(double(angleCone), 0., 1., 0.);
		    glutWireCone(radiusCone, heightCone, slices, stacks);
		  glPopMatrix();
	glPopMatrix();

//---------------------Ninot2--------------------
	glPushMatrix();
		glTranslatef(-2.5, radiusBase, 2.5);		//moure el ninot del (0., -.4, 0.) a on em demanen -> mesura 1 en total
		  
		  //-------Base-------
		  glPushMatrix();
		    glColor3f(1., 1., 1.);
		    glutWireSphere(radiusBase, slices, stacks);	
		  glPopMatrix();
		  //-------Head------
		  glPushMatrix();
		    glTranslatef(translateHeadX, translateHeadY, translateHeadZ);
		    glColor3f(.8, .8, 0.);			//yellow head
		    glutSolidSphere(radiusHead, slices, stacks);
		  glPopMatrix();
		  //-------Cone------
		  glPushMatrix();
		    glColor3f(.7, .3, .0);  
		    glTranslatef(translateConeX, translateConeY, translateConeZ);
		    glRotated(double(angleCone), 0., 1., 0.);
		    glutWireCone(radiusCone, heightCone, slices, stacks);
		  glPopMatrix();
	glPopMatrix();

//---------------------Ninot3--------------------
	glPushMatrix();
		glTranslatef(-2.5, radiusBase, -2.5);		//moure el ninot del (0., -.4, 0.) a on em demanen -> mesura 1 en total
		  
		  //-------Base-------
		  glPushMatrix();
		    glColor3f(1., 1., 1.);
		    glutWireSphere(radiusBase, slices, stacks);	
		  glPopMatrix();
		  //-------Head------
		  glPushMatrix();
		    glTranslatef(translateHeadX, translateHeadY, translateHeadZ);
		    glColor3f(.8, .8, 0.);			//yellow head
		    glutSolidSphere(radiusHead, slices, stacks);
		  glPopMatrix();
		  //-------Cone------
		  glPushMatrix();
		    glColor3f(.7, .3, .0);  
		    glTranslatef(translateConeX, translateConeY, translateConeZ);
		    glRotated(double(angleCone), 0., 1., 0.);
		    glutWireCone(radiusCone, heightCone, slices, stacks);
		  glPopMatrix();
	glPopMatrix();

//----------------------QUADRAT------------------
	glPushMatrix();
	  glBegin(GL_QUADS);
	    glColor3f(.3, .01, .01);
	    glVertex3f(-lado, 0., -lado);
	    glVertex3f(-lado, 0., lado);
	    glVertex3f(lado, 0., lado);
	    glVertex3f(lado, 0., -lado);
	  glEnd();
	glPopMatrix();						

//----------------------MODEL1--------------------
	glPushMatrix();
		glTranslatef(newx2, 0., newz2);
		glutPostRedisplay();
	
		glPushMatrix();	
			glTranslatef(0. + ancho_escalado/2., subirBase, 0. + profundo_escalado/2.);		//el movem on ens demanen 
			glScaled(escalado, escalado, escalado);
			glTranslatef(-centrox - tamx/2., -centroy, -centroz - tamz/2.);
			pinta_model();
			if (first) {
				calcularCapsaMinimaContenidora();
			}
		glPopMatrix();
	glPopMatrix();

//----------------------MODEL2--------------------
	glPushMatrix();
		glTranslatef(2.5, 0., -2.5);
		glRotated(90, 0., 1., 0.);
		glPushMatrix();	
			glTranslatef(ancho_escalado2/2., subirBase2, profundo_escalado2/2.);	//el movem on ens demanen 
			glScaled(escalado2, escalado2, escalado2);
			glTranslatef(-centrox2 - tamx2/2., -centroy2, -centroz2 - tamz2/2.);
			pinta_model();
			if (first2) {
				calcularCapsaMinimaContenidora2();
			}
		glPopMatrix();
	glPopMatrix();

//----------------------PARET1-------------------
	if (visible) {
		glPushMatrix();
			glTranslatef(translatePared1X, translatePared1Y + .75, translatePared1Z);
			glScaled(scalePared1X, scalePared1Y, scalePared1Z);
			glColor3f(.1, .1, .1);
			glutSolidCube(1.);
		glPopMatrix();

//----------------------PARET2-------------------
		glPushMatrix();
			glTranslatef(translatePared2X, translatePared2Y + .75, translatePared2Z);
			glScaled(scalePared2X, scalePared2Y, scalePared2Z);
			glColor3f(.1, .1, .1);
			glutSolidCube(1.);
		glPopMatrix();
	}
//-----------------------------------------------

	glutSwapBuffers();
}

void setOptica() {
	RA = float(w)/h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (changeCam) {
		//------CAMARA PERSPECTIVA------
		if (RA >= 1) {
			gluPerspective(FOV, RA, zN, zF);	//FOV es en grados
		}
		else {
			FOV2 =2*(atan(tan(double(FOV*3.14/180)/2)/RA))*180/3.14;	//FOV2 = arctg(tg(alfaV)/RAv) -> FOV = 2*alfaV
			gluPerspective(FOV2, RA, zN, zF);
		}
		glMatrixMode(GL_MODELVIEW);
	//	gluLookAt(0, 0, d, 0, 0, 0, 0, 1, 0);		//OBSx, OBSy, OBSz, VRPx, VRPy, VRPz, UPx, UPy, UPz
	}
	else {
		//------CAMARA AXONOMETRICA------
		glOrtho(-tamEsferaCont, tamEsferaCont, -tamEsferaCont, tamEsferaCont, tamEsferaCont, 3*tamEsferaCont);
	//	glOrtho(0., 0., w, h, tamEsferaCont, 3*tamEsferaCont);	//glOrtho(left, right, bottom, top, zN, zF);
		glMatrixMode(GL_MODELVIEW);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);
	}
}



void reshape(int width, int height) {
	w = width;
	h = height;
/*	if (!changeCam) {				//CAMARA AXONOMETRICA
		if (width < height) {
			glViewport(0, (height - width)/2, width, width);
		}
		else {
			glViewport((width - height)/2, 0, height, height);
		}
	}
	*/ 
	glViewport(0, 0, w, h);
	setOptica();
	glutPostRedisplay();
}

 void mousePressed(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN) {
		oldx = float(x);
		oldy = float(w - y);
		x1 = x2;
		x2 = x3;
		x3 = oldx;
		yy1 = y2;
		y2 = y3;
		y3 = oldy;
		glutPostRedisplay();
	}
	if (button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN) {
		zoom = true;
		oldy = float(w) - y;
	}
	if (button == GLUT_RIGHT_BUTTON and state == GLUT_UP) {
		zoom = false;
	}
}


void mouseMoved(int x, int y) {
	if (inspect) {
		anglex = float(y - oldy)*360./(h);
		anglex %= 360;
		angley = float(x - oldx)*360./(w);
		angley %= 360;
	}
	if (translate) {
		newx = float(x)*2./w - 1;
		newy = 2. - float(y)*2./h - 1;		//"2. - " perque el pixel (0,0) esta a dalt a la esquerra
	}
	if (changeState) {
		newx2 += float(x-oldx)*longitudSuelo/float(w);
		oldx = x;
	//-------------------hacer que no se salga del cuadrado----------------------------
		if (newx2 > lado - ancho_escalado/2.) newx2 = lado - ancho_escalado/2.;		//el modelo esta abajo a la derecha
		if (newx2 < -lado + ancho_escalado/2.) newx2 = -lado + ancho_escalado/2.;
	//---------------------------------------------------------------------------------	

		newz2 += float(y-oldy)*longitudSuelo/float(h);
		oldy = y;
	//-------------------hacer que no se salga del cuadrado----------------------------
		if (newz2 > lado - profundo_escalado/2.) newz2 = lado - profundo_escalado/2.;	//el modelo esta abajo a la derecha
		if (newz2 < -lado + profundo_escalado/2.) newz2 = -lado + profundo_escalado/2.;		
	//---------------------------------------------------------------------------------	
	}
	if (zoom) {
	//	if (changeCam) {
			FOV += float(y - oldy)/(h);
			if (FOV >= 180) FOV = 180.;
			if (FOV <= 1) FOV = 1.;
	//	}
	//	else {
			tamEsferaCont += float(y - oldy)*.1/(h);
	//	}
		setOptica();
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'h') {
		cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
		cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
		cout << "----------HELP----------" << endl;
	//	cout << "a:	change cam" << endl;
		cout << "c:	change state" << endl;
		cout << "d:	dades" << endl;
		cout << "h:	help" << endl;
		cout << "i:	inspect object" << endl;
		cout << "p:	perspective cam" << endl;
		cout << "r:	reset state" << endl;
		cout << "t:	translate object" << endl;
		cout << "v:	visible/invisible walls" << endl;
		cout << "x:	axonimetric cam" << endl;
		cout << "ESC:	close" << endl;
		cout << "------------------------" << endl;
	}
	else if (key == 27) glutLeaveMainLoop();
	else if (key == 'i') {
		inspect = !inspect;
	}
	else if (key == 't') {
		translate = !translate;
	}
	else if (key == 'd') {
		cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
		cout << endl << endl << endl << endl << endl << endl;
		cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
		cout << endl << endl << endl << endl << endl << endl;
		cout << endl << endl << endl << endl << endl << endl;
		cout << "CAPSA MINIMA CONTENIDORA NINOT" << endl;
		cout << "  xmax = " << xmax << endl;
		cout << "  ymax = " << ymax << endl;
		cout << "  zmax = " << zmax << endl;
		cout << "  xmin = " << xmin << endl;
		cout << "  ymin = " << ymin << endl;
		cout << "  zmin = " << zmin << endl;
		cout << "  ..................." << endl;
		cout << "  centrox = " << centrox << endl;
		cout << "  centroy = " << centroy << endl;
		cout << "  centroz = " << centroz << endl;
		cout << "  ..................." << endl;
		cout << "  diametro = " << diametro << endl;
		cout << "  subirBase = " << subirBase << endl;
		cout << "  ancho = " << tamx << endl;
		cout << "  alto = " << tamy << endl;
		cout << "  profundo = " << tamz << endl;
		cout << "  ..................." << endl;
		cout << "  ancho_escalado = " << ancho_escalado << endl;
		cout << "  alto_escalado = " << alto_escalado << endl;
		cout << "  profundo_escalado = " << profundo_escalado << endl;
		cout << "  ..................." << endl << endl;
		cout << "TERRA" << endl;
		cout << "  longitud suelo = " << longitudSuelo << endl;
		cout << "  coordenadas suelo = " << lado << endl;
		cout << "------------------------" << endl << endl;
		cout << "ESFERA CONTENEDORA ESCENA" << endl;
		cout << "  radio = " << tamEsferaCont << endl;
		cout << "------------------------" << endl << endl;
		cout << "TIPUS CAMERA" << endl;
		cout << "  cam = ";
		if (changeCam) {
			cout << "perspectiva" << endl;
			cout << "  FOV2 = " << FOV2 << endl;
		}
		else {
			cout << "axonometrica" << endl;
			cout << "  FOV = " << FOV << endl;
		}
		cout << "  RA = " << RA << endl;
		cout << "------------------------" << endl << endl; 
	}
	else if (key == 'c') {
		changeState = !changeState;
	}
	else if (key == 'x') {
		changeCam = false;
		setOptica();
		glutPostRedisplay();	}
	else if (key == 'p') {
		changeCam = true;
		setOptica();
		glutPostRedisplay();
	}
	else if (key == 'r') {
		rotx, roty, rotz = 0.;	
		inspect = false;
		translate = false;
		changeState = false;
		changeCam = true;
		newx2 = 0.;	//posicion OBJ
		newz2 = 0.;	//posicion OBJ
		anglex = 0.;
		angley = 0.;
		tamEsferaCont = sqrt((extremTerra*extremTerra) + (1.2*1.2));
		d = tamEsferaCont*2;						//me invento el valor inicial, ha de ser > radio
		R = tamEsferaCont;
		FOV = 2*(asin(R/d))*180/3.14;					//FOV en grados
		zN = d-R;
		zF = d+R;
		RAw = 1;							//porque es una circunferencia lo que tiene dentro
		VRPx = 0.;
		VRPy = 0.; 
		VRPz = 0.;
	
		setOptica();
		glutPostRedisplay();
		cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
		cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
		cout << "RESET DONE" << endl;
		cout << "CAMARA ";
		if (changeCam) cout << "PERSPECTIVA" << endl;
		else cout << "AXONOMETRICA" << endl;
		cout << "------------------------" << endl;
		cout << "h:	help" << endl;
		cout << "ESC:	close" << endl;
		cout << "------------------------" << endl;

	}
	if (key == 'v') {
		visible = !visible;
	}
	if (key != 'h' and key != 'd' and key != 'r') {
		cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
		cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
                cout << endl << endl << endl << endl << endl << endl;
		cout << "CAMARA ";
		if (changeCam) cout << "PERSPECTIVA" << endl;
		else cout << "AXONOMETRICA" << endl;
		cout << "------------------------" << endl;
		cout << "h:	help" << endl;
		cout << "ESC:	close" << endl;
		cout << "------------------------" << endl;
	}
}

int main(int argc, const char * argv[]) {
// 	-------------------INICIALIZAR-----------------------
	initGL(argc, argv);
// 	-------------------PINTAR----------------------------
	glutDisplayFunc(refresh);
// 	-------------------RATON-----------------------------
	glutMouseFunc(mousePressed);	//uso raton
	glutMotionFunc(mouseMoved);	//movimiento raton
// 	-------------------TECLADO---------------------------
	glutKeyboardFunc(keyboard);
// 	-------------------VENTANA---------------------------
	glutReshapeFunc(reshape);	//ventana proporcional
// 	-------------------CARGAR MODELO---------------------
	m.load(argv[1]);
//	----------------------------------------------------
	
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
	cout << "h:	help" << endl;
	cout << "ESC:	close" << endl;
	
	glutMainLoop();
	return 0;
}

