#if defined(__APPLE__)
	#include <UpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/freeglut.h>
#endif

#include <iostream>
using namespace std;

//variables
// ------------------bloc1.4-----------------
int actualx, actualy, oldx, oldy, oldz, tam, w, h;	//tam = tamany window
float r = 0.0;						//colors window
float g = 0.389;
float b = 0.0;
// ------------------bloc1.5-----------------
bool background = false;
bool triangles = false;
float x1, y1, x2, y2, x3, y3;			//punts del triangle a dibuixar (z1, z2 i z3 = 0)
float X1, Y1, X2, Y2, X3, Y3;			//punts del triangle original
int count3 = 0;
//-------------------bloc2.1-----------------
double size = 0.5;				//tamany tetera
double rotx, roty, rotz;			//variables glRotated
int anglex, angley;
bool inspect = false;
//------------------bloc2.2------------------
bool translate = false;
float newx, newy;				//noves posicions moviment Translated
//------------------bloc2.3------------------
bool scalex = false;
bool scaley = false;
bool scalez = false;
double actx = 1.;
double acty = 1.;
double actz = 1.;
//------------------bloc2.4------------------
int angleMultipleObjects;
bool multipleObjects = false;
//------------------bloc3--------------------
double radiusBase;
int slices;
int stacks;
double radiusHead;
float translateHeadX; 
float translateHeadY;
float translateHeadZ;
double radiusCone;
double heightCone;
float translateConeX;
float translateConeY;
float translateConeZ;
int angleCone;
//funciones

void initGL(int argc, const char * argv[]) {
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
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
}


void refresh(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, 0);	//green 389

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	rotx = 0.;
	roty = 0.;
	rotz = 0.;

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


//---------------------Ninot---------------------
	radiusBase = .4;
	slices = 40;
	stacks = 30;
	radiusHead = .2;
	translateHeadX = 0.;
	translateHeadY = .6;
	translateHeadZ = 0.;
	radiusCone = .1;
	heightCone = .2;
	translateConeX = .1;
	translateConeY = .6;
	translateConeZ = 0.;
	angleCone = 90;
	//-------Base-------
	glPushMatrix();
	  glColor3f(1., 1., 1.);
	  glutWireSphere(radiusBase, slices, stacks);	
	glPopMatrix();
	//-------Head------
	glPushMatrix();
	  glTranslatef(translateHeadX, translateHeadY, translateHeadZ);
	  glutWireSphere(radiusHead, slices, stacks);
	glPopMatrix();
	//-------Cone------
	glPushMatrix();
	  glColor3f(.7, .3, .0);  
	  glTranslatef(translateConeX, translateConeY, translateConeZ);
	  glRotated(double(angleCone), 0., 1., 0.);
	  glutWireCone(radiusCone, heightCone, slices, stacks);
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
		y1 = y2;
		y2 = y3;
		y3 = oldy;
		if (triangles)	++count3;
		glutPostRedisplay();
	}
}


void mouseMoved(int x, int y) {
	if (background) {
		r += float(y - oldy)/(tam);
		if (r > 1) r = 1;
		if (r < 0) r = 0;
		g += float(x - oldx)/(tam);
		if (g > 1) g = 1;
		if (g < 0) g = 0;
		glClearColor(r, g, b, 0);
		glutPostRedisplay();
		oldx = x;
		oldy = y;
	}
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
	
	if (scalex) {
		if ((x - oldx) > 0) actx += .01;
		else if ((x - oldx) < 0) actx -= .01;
		oldx = x;
	}
	if (scaley) {
		if ((y - oldy) > 0) acty -= .01;	//primer restem perque el pixel (0,0) esta a dalt a la esquerra
		else if ((y - oldy) < 0) acty += .01;
		oldy = y;
	}
	if (scalez) {
		if ((x - oldx) > 0) actz += .01;	//x - oldx perque no pux calcular eix z sobre els pixels
		else if ((x - oldx) < 0) actz -= .01;
		oldx = x;
	}
	if (multipleObjects) {
		angleMultipleObjects = float(x - oldx)*360./(w);
		angleMultipleObjects %= 360;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'h') {
		cout << "----------HELP----------" << endl;
		cout << "f:	background color" << endl;
		cout << "h:	help" << endl;
		cout << "i:	inspect object" << endl;
		cout << "m:	multiple objects" << endl;
		cout << "t:	translate object" << endl;
		cout << "x: 	scale X axis" << endl;
		cout << "y:	scale Y axis" << endl;
		cout << "z:	scale Z axis" << endl;
		cout << "ESC:	close" << endl;
		cout << "------------------------" << endl;
	}
	else if (key == 27) glutLeaveMainLoop();
	else if (key == 'f') {
		background = !background;
	}
	else if (key == 'i') {
		inspect = !inspect;
	}
	else if (key == 't') {
		translate = !translate;
	}
	else if (key == 'x') {
		scalex = !scalex;
	}
	else if (key == 'y') {
		scaley = !scaley;
	}
	else if (key == 'z') {
		scalez = !scalez;
	}
	else if (key == 'm') {
		multipleObjects = !multipleObjects;
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
// 	-----------------------------------------------------
	
	cout << "h:	help" << endl;
	cout << "ESC:	close" << endl;
	
	glutMainLoop();
	return 0;
}

