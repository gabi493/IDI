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

int newx, newy, actualx, actualy, oldx, oldy;
float r = 0.0;
float g = 0.389;
float b = 0.0;

//funciones

void initGL(int argc, const char * argv[]) {
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("IDI: Practiques OpenGL");
}


void refresh(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, 0);	//green 389
	
	glBegin(GL_TRIANGLES);
		glColor3f(0.7, 0, 0);
		glVertex3f(-1/float(2), -1/float(3), 0);
		glColor3f(0, 0.7, 0);
		glVertex3f(1/float(2), -1/float(3), 0);
		glColor3f(0, 0, 0.7);
		glVertex3f(0, 2/float(3), 0);
	glEnd();
	
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
	if (button == GLUT_LEFT_BUTTON & state == GLUT_DOWN) {
		oldx = x;
		oldy = y;
	}
}


void mouseMoved(int x, int y) {
// 	r += float((600.0 - y) - oldy)/50000.0;
	r += float(y - oldy)/10000.0;
	if (r > 1) r = 1;
	if (r < 0) r = 0;
	g += float(x - oldx)/10000.0;
	if (g > 1) g = 1;
	if (g < 0) g = 0;
	glClearColor(r, g, b, 0);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'h') {
		cout << "-----HELP-----" << endl;
		cout << "h:	help" << endl;
		cout << "ESC	close" << endl;
		cout << "--------------" << endl;
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
	
	cout << "-----HELP-----" << endl;
	cout << "h:	help" << endl;
	cout << "ESC	close" << endl;
	
	glutMainLoop();
	return 0;
}