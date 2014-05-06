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
float newx, newy;				//noves posicions moviment Translated
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
float longitudSuelo = 1.5;
float lado = longitudSuelo/2.;
double escalado;
double tamanyQueVolem = 0.5;		//tamany del model
double subirBase;
bool changeState = false;
float newx2, newz2;
//------------------bloc3.2------------------
double extremTerra = sqrt((.75*.75) + (.75*.75));
double tamEsferaCont = sqrt((extremTerra*extremTerra) + (.5*.5));		//se calcula a mano


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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
}

void pinta_model() {
	const int &n = m.faces().size();
	for (int i = 0; i < n; ++i) {
		const Face &f = m.faces()[i];
		glColor4fv(Materials[f.mat].diffuse);
		glBegin(GL_TRIANGLES);		//pintar triangle
		for (int j = 0; j < 3; ++j) {
			glVertex3dv(&m.vertices()[f.v[j]]);	
		}
		glEnd();
	}
}

void calcularCapsaMinimaContenidora() {
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
	
	tamx = xmax - xmin;		//tamx = ancho
	tamy = ymax - ymin;		//tamy = alto
	tamz = zmax - zmin;		//tamz = profundo

	diametro = sqrt((tamx*tamx) + (tamy*tamy) + (tamz*tamz));
	
	escalado = tamanyQueVolem/tamy;			//escalado = tamanyQueVolem/alto
	subirBase = tamanyQueVolem/2.;
}

void refresh(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, 0);	//green 389

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

//----------------------Rotar--------------------
	glRotated(double(anglex), 1., roty, rotz);	//anglex es un integer per poder fer %360
	glRotated(double(angley), rotx, 1., rotz);	//angley es un integer
	glutPostRedisplay();
//---------------------Traslladar----------------
	glTranslatef(newx, 0., 0.);
	glTranslatef(0., newy, 0.);
	glutPostRedisplay();	
//---------------------Escalar-------------------
	glScaled(actx, acty, actz);			//actx, acty, actz poden ser < 0 i > 1
	glutPostRedisplay();




//---------------ESFERA CONTENEDORA ESCENA-------
	glPushMatrix();
	  glColor3f(.0, .0, .8);	//blue sphere
	  glutWireSphere(tamEsferaCont, slices, stacks);
	glPopMatrix();

//---------------------Ninot---------------------
	glPushMatrix();
		
		glTranslatef(0., 0., 0.);	//moure el ninot del (0., -.4, 0.) a on em demanen -> mesura 1 en total
		  
		  //-------Base-------
		  glPushMatrix();
		    glColor3f(1., 1., 1.);
		    glutWireSphere(radiusBase, slices, stacks);	
		  glPopMatrix();
		  //-------Head------
		  glPushMatrix();
		    glTranslatef(translateHeadX, translateHeadY, translateHeadZ);
		    glColor3f(.8, .8, 0.);	//yellow head
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
	    glVertex3f(-lado, -.4, -lado);
	    glVertex3f(-lado, -.4, lado);
	    glVertex3f(lado, -.4, lado);
	    glVertex3f(lado, -.4, -lado);
	  glEnd();
	glPopMatrix();						


//----------------------MODEL--------------------
	glTranslatef(newx2, 0., 0.);
	glTranslatef(0., 0., newz2);
	glutPostRedisplay();
	
	glPushMatrix();	
		glTranslatef(.75, subirBase - .4, .75);			//el movem on ens demanen 
		glScaled(escalado, escalado, escalado);
		glTranslatef(-centrox, -centroy, -centroz);
		pinta_model();
		if (first) {
			calcularCapsaMinimaContenidora();
			first = false;
		}
	glPopMatrix();



// 	glutPostRedisplay();
	glutSwapBuffers();
}


void reshape(int width, int height) {
	if (width < height) {
		glViewport(0, (height - width)/2, width, width);
	}
	else {
		glViewport((width - height)/2, 0, height, height);
	}
	w = width;
	h = height;
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
		newx2 += float(x-oldx)*1.5/float(w);
		oldx = x;
		if (newx2 > 0) newx2 = 0;		//el modelo esta abajo a la derecha
		if (newx2 < -2*lado) newx2 = -2*lado;
		
		newz2 += float(y-oldy)*1.5/float(h);
		oldy = y;
		if (newz2 > 0) newz2 = 0;		//el modelo esta abajo a la derecha
		if (newz2 < -2*lado) newz2 = -2*lado;		
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
		cout << "c:	change state" << endl;
		cout << "d:	dades" << endl;
		cout << "h:	help" << endl;
		cout << "i:	inspect object" << endl;
		cout << "t:	translate object" << endl;
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
		cout << "CAPSA MINIMA CONTENIDORA" << endl;
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
		cout << "  ..................." << endl << endl;
		cout << "TERRA" << endl;
		cout << "  longitud suelo = " << longitudSuelo << endl;
		cout << "  coordenadas suelo = " << lado << endl;
		cout << "------------------------" << endl << endl;
		cout << "ESFERA CONTENEDORA ESCENA" << endl;
		cout << "  radio = " << tamEsferaCont << endl;
		cout << "------------------------" << endl << endl;
		cout << "h:	help" << endl;
		cout << "ESC:	close" << endl;
		cout << "------------------------" << endl;

	}
	else if (key == 'c') {
		changeState = !changeState;
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

