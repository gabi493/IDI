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
int newx, newy, actualx, actualy, oldx, oldy, tam;	//tam = tamany window
float r = 0.0;
float g = 0.389;
float b = 0.0;
// ------------------bloc1.5-----------------
bool background;
bool triangles = false;
float x1, y1, x2, y2, x3, y3;		//punts del triangle a dibuixar (z1, z2 i z3 = 0)
float X1, Y1, X2, Y2, X3, Y3;		//punts del triangle original
int count3 = 0;
//-------------------bloc2.1-----------------
double size = 0.5;		//tamany tetera

//funciones

void initGL(int argc, const char * argv[]) {
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	tam = 600;
	glutInitWindowSize(tam, tam);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("IDI: Practiques OpenGL");
	X1 = -1/float(2);
	Y1 = -1/float(3);
	X2 = 1/float(2);
	Y2 = -1/float(3);
	X3 = 0;
	Y3 = 2/float(3);
}


void refresh(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, 0);	//green 389
/*	if (count3 == 3) {
		X1 = float(x1*2./tam)-1;	//transformacio de les coordenades de pixel a -1, -1, -1, 1, 1, 1
		Y1 = float(y1*2./tam)-1;
		X2 = float(x2*2./tam)-1;
		Y2 = float(y2*2./tam)-1;
		X3 = float(x3*2./tam)-1;
		Y3 = float(y3*2./tam)-1;
		triangles = false;
		count3 = 0;
	}
*/
	glBegin(GL_TRIANGLES);
		glColor3f(0.7, 0, 0);
		glVertex3f(X1, Y1, 0);
		glColor3f(0, 0.7, 0);
		glVertex3f(X2, Y2, 0);
		glColor3f(0, 0, 0.7);
		glVertex3f(X3, Y3, 0);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glutWireTeapot(size);
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
	glutPostRedisplay();
	
}

 void mousePressed(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN) {
		oldx = float(x);
		oldy = float(tam - y);
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
		r += float(y - oldy)/10000.0;
		if (r > 1) r = 1;
		if (r < 0) r = 0;
		g += float(x - oldx)/10000.0;
		if (g > 1) g = 1;
		if (g < 0) g = 0;
		glClearColor(r, g, b, 0);
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'h') {
		cout << "----------HELP----------" << endl;
		cout << "f:	background color" << endl;
		cout << "h:	help" << endl;
		cout << "ESC:	close" << endl;
		cout << "------------------------" << endl;
	}
	if (key == 'f') {
		background = !background;
	}
	else if (key == 27) glutLeaveMainLoop();
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

