#include <GL/glut.h>
#include <Math.h>
#include <time.h>
#include <iostream>
#include "texturas/RgbImage.h"

using namespace std;

float camaraX = -60;
float camaraY = 20;
float camaraZ = 60;

float angulo = 0;

GLuint texturas[5];
GLUquadric* quad;

void loadTexturesFromFile(const char* filename, int index) {
	RgbImage theTextMap(filename);
	glGenTextures(1, &texturas[index]);
	glBindTexture(GL_TEXTURE_2D, texturas[index]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, theTextMap.GetNumCols(),
		theTextMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTextMap.ImageData());
}
void iniciarVentana(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (float)w / (float)h, 1, 200);
}
void inicializarLuces() {

	GLfloat luz_ambiente[] = { 0.35,0.35,0.35,1 };
	GLfloat luz_difusa[] = { 0.5,0.5,0.5,1 };
	GLfloat luz_especular[] = { 0.3,0.3,0.3,1 };

	float posicionLuz[] = { 0,70,60,1 };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}

void piso() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[0]);
	glColor3ub(255, 255, 255);

	glPushMatrix();
	glTranslated(0, -1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3d(-50, 0, -50);
	glTexCoord2f(1, 1);  glVertex3d(50, 0, -50);
	glTexCoord2f(1, 0); glVertex3d(50, 0, 50);
	glTexCoord2f(0, 0); glVertex3d(-50, 0, 50);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}
void ejes() {
	glBegin(GL_LINES);

	glColor3ub(255, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(50, 0, 0);

	glColor3ub(0, 255, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 50, 0);

	glColor3ub(0, 0, 255);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 50);

	glEnd();
}
//primitivas
void dibujarPrimitivas() {
	glPushMatrix();
	glTranslated(30, 2, 0);
	glColor3ub(20, 200, 200);
	glutSolidTeapot(4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-40, 2, 40);
	glColor3ub(20, 200, 200);
	glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-30, 20, -30);
	glColor3ub(20, 200, 200);
	glutWireCube(4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 20, -30);
	glRotated(240, 1, 0, 0);
	glColor3ub(20, 200, 200);
	glutSolidCone(5, 16, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 20, 30);
	glRotated(240, 1, 0, 0);
	glColor3ub(20, 200, 200);
	glutWireCone(5, 16, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 20, 30);
	glRotated(240, 1, 0, 0);
	glColor3ub(20, 10, 200);
	glutSolidSphere(6, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslated(10, 8, 10);
	glRotated(240, 1, 0, 0);
	glColor3ub(20, 100, 210);
	glutWireSphere(6, 30, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-10, 8, -10);
	glColor3ub(200, 10, 210);
	glutSolidTorus(2, 4, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-30, 8, -10);
	glColor3ub(200, 10, 210);
	glutWireTorus(2, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(30, 8, -10);
	glColor3ub(20, 110, 210);
	gluCylinder(gluNewQuadric(), 3, 6, 20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(30, 20, 10);
	glColor3ub(20, 110, 210);
	gluDisk(gluNewQuadric(), 3, 6, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 10, 40);
	glColor3ub(20, 110, 210);
	gluPartialDisk(gluNewQuadric(), 3, 6, 20, 20, 0, 180);
	glPopMatrix();
}
void pared() {
	glBegin(GL_QUADS);
	glVertex3d(-10, 0, 0);
	glVertex3d(10, 0, 0);
	glVertex3d(10, 20, 0);
	glVertex3d(-10, 20, 0);
	glEnd();
}
void cubo() {


	glPushMatrix();
	glColor3ub(200, 0, 0);
	glTranslated(0, 0, 10);
	pared();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(200, 0, 0);
	glTranslated(0, 0, -10);
	pared();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 200, 0);
	glTranslated(-10, 0, 0);
	glRotated(90, 0, 1, 0);
	pared();
	glPopMatrix();

	glPushMatrix();
	glTranslated(10, 0, 0);
	glRotated(-90, 0, 1, 0);
	glColor3ub(0, 200, 0);
	pared();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 20, 10);
	glRotated(-90, 1, 0, 0);
	glColor3ub(0, 0, 200);
	pared();
	glPopMatrix();

}
void grupoCubos() {

	glPushMatrix();
	cubo();
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(20, 0, 0);
	cubo();
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(-20, 0, 0);
	cubo();
	glPopMatrix();

}
void cuadrilatero() {

	glPushMatrix();
	glColor3ub(250, 0, 0);
	glTranslated(-15, 0, 0);
	cubo();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 250, 0);
	glTranslated(0, 0, 0);
	cubo();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 250);
	glTranslated(15, 0, 0);
	cubo();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 250);
	glTranslated(-5, 20, 0);
	cubo();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 250);
	glTranslated(5, 20, 0);
	cubo();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 250);
	glTranslated(0, 30, 0);
	cubo();
	glPopMatrix();

}
//keny
//void pie(float posX) {
//	glPushMatrix();
//	glTranslated(posX, 0, 0);
//	glScaled(3, 0.6, 3);
//	glutSolidSphere(1.5, 50, 50);
//	glPopMatrix();
//}
//void pierna(float posX) {
//	glPushMatrix();
//	glTranslated(posX, 0, 0);
//	glRotated(-90, 1, 0, 0);
//	gluCylinder(gluNewQuadric(), 4, 4, 4, 50, 50);
//	glPopMatrix();
//}
//void cuerpo() {
//	glPushMatrix();
//	glTranslated(0, 3.5, 0);
//	glScaled(1, 0.7, 1);
//	glRotated(-90, 1, 0, 0);
//	gluCylinder(gluNewQuadric(), 8, 6, 10, 50, 50);
//	glPopMatrix();
//}
//void brazo(float posX, float rot) {
//	glPushMatrix();
//	glTranslated(posX, 9, 0);
//	glRotated(90, 0, 1, 0);
//	glRotated(rot, 1, 0, 0);
//	gluCylinder(gluNewQuadric(), 1.5, 1.5, 5, 50, 50);
//	glPopMatrix();
//}
//void mano(float posX) {
//	glPushMatrix();
//	glTranslated(posX, 5, 0);
//	glScaled(1, 0.75, 0.7);
//	glutSolidSphere(2, 50, 50);
//	glPopMatrix();
//}
//void cremallera() {
//	glPushMatrix();
//	glTranslated(0, 7, 6.5);
//	glRotated(-16, 1, 0, 0);
//	glScaled(1, 7, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//}
//void bufanda() {
//	glPushMatrix();
//	glTranslated(0, 10.5, 0);
//	glRotated(-90, 1, 0, 0);
//	glScaled(1, 1, 0.6);
//	glutSolidTorus(1, 5.5, 50, 50);
//	glPopMatrix();
//}
//void cabeza() {
//	glPushMatrix();
//	glTranslated(0, 16.2, 0);
//	glutSolidSphere(8, 50, 50);
//	glPopMatrix();
//}
//void gorra() {
//	glPushMatrix();
//	glTranslated(0, 17, 0);
//	glutSolidSphere(7.8, 50, 50);
//	glPopMatrix();
//}
//void pompom() {
//	glPushMatrix();
//	glTranslated(0, 24, 0);
//	glutSolidSphere(2, 50, 50);
//	glPopMatrix();
//}
//void aroGorra() {
//	glPushMatrix();
//	glTranslated(0, 19, 0);
//	glRotated(-90, 1, 0, 0);
//	glutSolidTorus(1, 7.5, 50, 50);
//	glPopMatrix();
//}
//void boca() {
//	glPushMatrix();
//	glTranslated(0, 13, 7.1);
//	glScaled(1, 0.8, 0.2);
//	glutSolidSphere(2, 80, 80);
//	glPopMatrix();
//}
//void diente() {
//	glPushMatrix();
//	glTranslated(0, 13, 7.3);
//	glScaled(1.5, 1, 1);
//	glutSolidCube(0.5);
//	glPopMatrix();
//}
//void ojo(float posX, float rot) {
//	glPushMatrix();
//	glTranslated(posX, 15.8, 6.6);
//	glRotated(rot, 0, 0, 1);
//	glScaled(0.9, 0.6, 0.6);
//	glutSolidSphere(3, 80, 80);
//	glPopMatrix();
//}
//void pupila(float posX) {
//	glPushMatrix();
//	glTranslated(posX, 15.6, 8);
//	glutSolidSphere(0.6, 80, 80);
//	glPopMatrix();
//}
//void keny() {
//	glColor3ub(155, 117, 6);
//	pie(3);
//	pie(-3);
//
//	glColor3ub(234, 115, 1);
//	pierna(3);
//	pierna(-3);
//	cuerpo();
//	brazo(5.2, 50);
//	brazo(-5.2, 130);
//
//	glColor3ub(155, 117, 6);
//	mano(8);
//	mano(-8);
//
//	glColor3ub(0, 0, 0);
//	cremallera();
//
//	glColor3ub(34, 223, 254);
//	bufanda();
//
//	glColor3ub(243, 193, 145);
//	cabeza();
//
//	glColor3ub(89, 59, 30);
//	gorra();
//
//	glColor3ub(254, 193, 0);
//	pompom();
//	aroGorra();
//
//	glColor3ub(0, 0, 0);
//	boca();
//
//	glColor3ub(255, 255, 255);
//	diente();
//
//	ojo(1.8, -40);
//	ojo(-1.8, 40);
//
//	glColor3ub(0, 0, 0);
//	pupila(1.7);
//	pupila(-1.7);
//}
//casa
//void base() {
//	glPushMatrix();
//	glColor3ub(149, 144, 137);
//	glTranslated(0, 5, 0);
//	glutSolidCube(10);
//	glPopMatrix();
//}
//void triangulo(float posZ) {
//	glPushMatrix();
//	glTranslated(0, 0, posZ);
//	glBegin(GL_TRIANGLES);
//	glVertex3d(-5, 10, 0);
//	glVertex3d(5, 10, 0);
//	glVertex3d(0, 15, 0);
//	glEnd();
//	glPopMatrix();
//}
//void tejado(float giro) {
//	glPushMatrix();
//	glColor3ub(173, 83, 7);
//	glTranslated(0, 10, 5);
//	glRotated(giro, 0, 0, 1);
//	glBegin(GL_QUADS);
//	glVertex3d(-5, 0, 0);
//	glVertex3d(0, 5, 0);
//	glVertex3d(0, 5, -10);
//	glVertex3d(-5, 0, -10);
//	glEnd();
//	glPopMatrix();
//}
//void barraDiagonal(float posX, float posZ, float rot) {
//	glPushMatrix();
//	glColor3ub(104, 64, 58);
//	glTranslated(posX, 12, posZ);
//	glRotated(rot, 0, 0, 1);
//	glScaled(8.5, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//}
//void barraLateral(float posX) {
//	glPushMatrix();
//	glColor3ub(104, 64, 58);
//	glTranslated(posX, 10, 0);
//	glRotated(45, 0, 0, 1);
//	glScaled(1, 1, 10);
//	glutSolidCube(1);
//	glPopMatrix();
//}
//void marco(int red, int green, int blue) {
//	glPushMatrix();
//	glColor3ub(red, green, blue);
//	glTranslated(0, 4, 4.53);
//	glScaled(5, 8, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//}
//void puerta() {
//	glPushMatrix();
//	marco(139, 90, 73);
//	glPushMatrix();
//	glTranslated(0, 0.7, 0.02);
//	glScaled(0.7, 0.8, 1);
//	marco(104, 64, 52);
//	glPopMatrix();
//	glPushMatrix();
//	glColor3ub(200, 172, 51);
//	glTranslated(1.5, 4, 5);
//	glutSolidSphere(0.3, 50, 50);
//	glPopMatrix();
//	glPopMatrix();
//}
//void balcon() {
//	glPushMatrix();
//	glColor3ub(174, 110, 75);
//	glTranslated(-4, 8, 0);
//	glutSolidCube(6);
//	glPopMatrix();
//	glPushMatrix();
//	glTranslated(-7, 11, 0);
//	glRotated(90, 0, 1, 0);
//	glBegin(GL_TRIANGLES);
//	glVertex3d(-3, 0, 0);
//	glVertex3d(3, 0, 0);
//	glVertex3d(0, 3, 0);
//	glEnd();
//	glPopMatrix();
//}
//void ventanita(float posY, float posZ) {
//	glPushMatrix();
//	glColor3ub(255, 255, 255);
//	glTranslated(-6.6, posY, posZ);
//	glScaled(1, 1.5, 0.8);
//	glutSolidCube(1);
//	glPopMatrix();
//}
//void tejado2(double posZ) {
//	glPushMatrix();
//	glColor3ub(172, 110, 65);
//	glTranslated(-4, 8, 0);
//	glBegin(GL_QUADS);
//	glVertex3d(-3, 3, posZ);
//	glVertex3d(-3, 6, 0);
//	glVertex3d(3, 6, 0);
//	glVertex3d(3, 3, posZ);
//	glEnd();
//	glPopMatrix();
//}
//void fondo() {
//	glPushMatrix();
//	glTranslated(0, -50, -50);
//	glRotated(180, 0, 1, 0);
//	glBegin(GL_POLYGON);
//	glColor3ub(108, 186, 217);
//	glVertex3d(-100, 200, 0);
//	glVertex3d(100, 200, 0);
//	glColor3ub(255, 255, 255);
//	glVertex3d(100, 0, 0);
//	glVertex3d(-100, 0, 0);
//	glEnd();
//	glPopMatrix();
//}
//void casita() {
//	base();
//	triangulo(5);
//	triangulo(-5);
//	tejado(0);
//	tejado(-90);
//	barraDiagonal(-2.7, 5, 45);
//	barraDiagonal(2.7, 5, -45);
//	barraDiagonal(-2.7, -5, 45);
//	barraDiagonal(2.7, -5, -45);
//	barraLateral(5);
//	barraLateral(-5);
//	puerta();
//	balcon();
//	tejado2(3);
//	tejado2(-3);
//	ventanita(6, 1);
//	ventanita(6, -1.5);
//	ventanita(8.5, 1);
//	ventanita(8.5, -1.5);
//	fondo();
//}

//imagenes
void cargarImagenes() {
	loadTexturesFromFile("texturas/piso1.bmp", 0);
	loadTexturesFromFile("texturas/goku.bmp", 1);
	loadTexturesFromFile("texturas/tierra.bmp", 2);
}

void tierra() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[2]);
	glColor3ub(255, 255, 255);

	glPushMatrix();
	glTranslated(0, 25, 0);
	glRotated(-90, 1, 0, 0);
	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 5, 50, 50);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

void cubito() {

	glColor3ub(140, 220, 250);
	glPushMatrix();
	glTranslated(0, 7.2, 0);
	glScaled(1.28, 0.72, 1.28);
	glutSolidCube(20);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[1]);
	glColor3ub(255, 255, 255);

	glPushMatrix();
	glTranslated(-12.8, 0, 12.81);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3d(0, 14.4, 0);
	glTexCoord2f(1, 1); glVertex3d(25.6, 14.4, 0);
	glTexCoord2f(1, 0); glVertex3d(25.6, 0, 0);
	glTexCoord2f(0, 0); glVertex3d(0, 0, 0);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}


void dibujar() {
	inicializarLuces();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camaraX, camaraY, camaraZ, 0, 0, 0, 0, 1, 0);
	glClearColor(255 / 255.0, 255 / 255.0, 210 / 255.0, 1);

	glPushMatrix();
	glRotated(angulo, 0, 1, 0);
	piso();
	ejes();

	cubito();
	tierra();

	glPopMatrix();

	glutSwapBuffers();

}
void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}
void teclado(int tecla, int x, int y) {
	switch (tecla)
	{
	case 101:
		camaraY += 0.2;
		break;
	case 103:
		camaraY -= 0.2;
		break;
	case 100:
		angulo -= 1;
		break;
	case 102:
		angulo += 1;
		break;
	}
}


int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1100, 750);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Bienvenidos a computacion grafica");
	cargarImagenes();
	glutReshapeFunc(iniciarVentana);
	glutDisplayFunc(dibujar);
	glutSpecialFunc(teclado);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;

}