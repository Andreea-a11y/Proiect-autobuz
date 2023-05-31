
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include <corecrt_math.h>

void myinit(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK display(void);
void MatriceUmbra(GLfloat puncte[3][3], GLfloat pozSursa[4], GLfloat mat[4][4]);
void calcCoeficientiPlan(float P[3][3], float coef[4]);
GLUquadric* q;

static GLfloat pozSursa[] = { -90, 240, -50, 0.1 };

void CALLBACK mutaSursaDreapta(void) {
	if (pozSursa[0] < 200)

		pozSursa[0] += 10;


}
void CALLBACK mutaSursaStanga(void) {
	if (pozSursa[0] > -200)
		pozSursa[0] -= 10;
}

static double rotireCub = 0;

void CALLBACK rotireDreapta(void) {
	rotireCub = rotireCub - (3.14 / 4);
}
void CALLBACK rotireStanga(void) {
	rotireCub = rotireCub + (3.14 / 4);
}

static GLfloat x = 0; static GLfloat y = 0;
static GLfloat z = 0;

void CALLBACK MutaDreapta(void)
{
	x = x + 30;
	y = y + 7.5;

}
void CALLBACK MutaStanga(void)
{
	x = x - 30;
	y = y - 7.5;

}

void CALLBACK MutaSus(void) {
	z = z + 2;
}
void CALLBACK MutaJos(void) {
	z = z - 2;
}

boolean umbra = 0;

void calcCoeficientiPlan(float P[3][3], float coef[4]) {
	float v1[3], v2[3];
	float length;
	static const int x = 0, y = 1, z = 2;

	
	v1[x] = P[0][x] - P[1][x];
	v1[y] = P[0][y] - P[1][y];
	v1[z] = P[0][z] - P[1][z];
	v2[x] = P[1][x] - P[2][x];
	v2[y] = P[1][y] - P[2][y];
	v2[z] = P[1][z] - P[2][z];

	coef[x] = v1[y] * v2[z] - v1[z] * v2[y];
	coef[y] = v1[z] * v2[x] - v1[x] * v2[z];
	coef[z] = v1[x] * v2[y] - v1[y] - v2[x];
	length = (float)sqrt(coef[x] * coef[x] + coef[y] * coef[y] + coef[z] * coef[z]);
	coef[x] /= length;
	coef[y] /= length;
	coef[z] /= length;
}
void MatriceUmbra(GLfloat puncte[3][3], GLfloat pozSursa[4], GLfloat mat[4][4]) {
	

	GLfloat coefPlan[4], temp;
	calcCoeficientiPlan(puncte, coefPlan);
	coefPlan[3] = -(coefPlan[0] * puncte[2][0] + coefPlan[1] * puncte[2][1] + coefPlan[2] * puncte[2][2]);

	temp = coefPlan[0] * pozSursa[0] + coefPlan[1] * pozSursa[1] + coefPlan[2] * pozSursa[2] + coefPlan[3] * pozSursa[3];
	//coloana 1
	mat[0][0] = temp - coefPlan[0] * pozSursa[0];
	mat[1][0] = 0.0f - coefPlan[1] * pozSursa[0];
	mat[2][0] = 0.0f - coefPlan[2] * pozSursa[0];
	mat[3][0] = 0.0f - coefPlan[3] * pozSursa[0];
	//coloana 2
	mat[0][1] = 0.0f - coefPlan[0] * pozSursa[1];
	mat[1][1] = temp - coefPlan[1] * pozSursa[1];
	mat[2][1] = 0.0f - coefPlan[2] * pozSursa[1];
	mat[3][1] = 0.0f - coefPlan[3] * pozSursa[1];
	//coloana 3
	mat[0][2] = 0.0f - coefPlan[0] * pozSursa[2];
	mat[1][2] = 0.0f - coefPlan[1] * pozSursa[2];
	mat[2][2] = temp - coefPlan[2] * pozSursa[2];
	mat[3][2] = 0.0f - coefPlan[3] * pozSursa[2];
	//coloana 4
	mat[0][3] = 0.0f - coefPlan[0] * pozSursa[3];
	mat[1][3] = 0.0f - coefPlan[1] * pozSursa[3];
	mat[2][3] = 0.0f - coefPlan[2] * pozSursa[3];
	mat[3][3] = temp - coefPlan[3] * pozSursa[3];
}

void myinit(void) {
	GLfloat ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 128.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	//permite urmarirea culorilor
	glEnable(GL_COLOR_MATERIAL);
	//seteaza proprietatile de material pt a urma valorile glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//seteaza sursa
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, pozSursa);

	//seteaza materialul
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// pt fundal
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST); // ascunderea suprafetelor
	q = gluNewQuadric();
	gluQuadricDrawStyle(q, GLU_FILL);
}


void Roata(void) {
	if (umbra == 1)
		glColor3f(0, 0, 0);
	else glColor3f(0, 0, 0);

	glPushMatrix();

	glRotatef(-x, 0, 0, 1);
	glTranslatef(0.0, 10.0, 0.0);
	auxSolidCylinder(0.5, 20);
	glTranslatef(0.0, -10.0, 0.0);

	glRotatef(75, 0, 0, 1);
	glTranslatef(0.0, 10.0, 0.0);
	auxSolidCylinder(0.5, 20);
	glTranslatef(0.0, -10.0, 0.0);
	glRotatef(-75, 0, 0, 1);
	auxSolidTorus(5, 15);
	glPopMatrix();
}

void Suport_roata(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else glColor3f(1, 0.5, 0.5);

	glPushMatrix();

	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(45, 0, 0, 1);

	gluCylinder(q, 10, 20, 13, 4, 2);
	glRotatef(-45, 0, 0, 1);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glPopMatrix();

}

void Sasiu(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else
		glColor3f(1.0, 0.5, 0.0);

	glTranslatef(0.0, 0, 15);
	Roata();
	glRotatef(90, 1, 0, 0);

	glRotatef(-90, 1, 0, 0);
	glTranslatef(70.0, 0, -60);

	glTranslatef(-60.0, 0, -15);
	Roata();
	glTranslatef(120, 0, 75);

	glTranslatef(-20.0, 0, -15);

	glTranslatef(-10.0, 0, 15);

	glRotatef(90, 1, 0, 0);

	glRotatef(-90, 1, 0, 0);
	glTranslatef(10.0, 0, -60);

	glTranslatef(-10.0, 0, -15);

	glTranslatef(-80, 0, 75);
}

void BAZA(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else glColor3f(1, 1, 1);

	glTranslatef(100, 11, -37);


	auxSolidBox(300, 200, 73);



	glTranslatef(-75, -11, 37);
	glTranslatef(0, 0, -15);
	Sasiu();

	glTranslatef(100, 0, -15);

	Sasiu();


}
void GEAM(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else glColor3f(1, 1, 1);
	glTranslatef(-65, 71, -13);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidBox(30, 30, 27);

	glTranslatef(-45, 0, 0);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidBox(30, 30, 27);

	glTranslatef(-45, 0, 0);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidBox(30, 30, 27);

	glTranslatef(-45, 0, 0);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidBox(30, 30, 27);

}
void GEAM2(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else glColor3f(1, 1, 1);
	glTranslatef(200, -5, -25);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidBox(30, 30, 27);

	glTranslatef(-45, 0, 0);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidBox(30, 30, 27);

	glTranslatef(-45, 0, 0);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidBox(30, 30, 27);

	glTranslatef(-45, 0, 0);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidBox(30, 30, 27);

}

void USA(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else glColor3f(1, 1, 1);
	glTranslatef(180, -45, 0);
	glColor3f(0.9, 0.9, 0.9);
	auxSolidBox(30, 70, 27);


}

void PARBRIZ(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else glColor3f(1, 1, 1);
	glTranslatef(265, 40, 25);
	glColor3f(0, 1, 1);
	auxSolidBox(70, 60, 60);

}
void STOPURI(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else glColor3f(1, 1, 1);
	glTranslatef(-258, 10, 1);
	glColor3f(1, 0, 0);
	auxSolidSphere(5);

	glTranslatef(0, 0, -50);
	glColor3f(1, 0, 0);
	auxSolidSphere(5);

}

void FARURI(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else glColor3f(1, 1, 1);
	glTranslatef(30, -60, 20);
	glColor3f(1, 1, 0);
	auxSolidSphere(8);

	glTranslatef(0, 0, -40);
	glColor3f(1, 1, 0);
	auxSolidSphere(8);

}

void LUNETA(void) {
	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else glColor3f(1, 1, 1);
	glTranslatef(-263, 70, 20);
	glColor3f(0, 1, 1);
	auxSolidBox(70, 40, 60);

}

void AUTOBUZ(void) {

	BAZA();


	glTranslatef(-72.0, 80.0, -34.0);

	if (umbra == 1)
		glColor3f(0.05, 0.05, 0.05);
	else
		glColor3f(1, 0, 1);




	glPushMatrix();



	glTranslatef(0.0, 65.0, -30.0);




	glPopMatrix();
}


void AUTO() {
	glPushMatrix();
	BAZA();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(170, 12, 0.0);

	glPopMatrix();
}
void AUTOBUZUL() {
	glTranslatef(-300, 0, 0.0);

	glTranslatef(230, 0, 0.0);
	AUTO();
	glTranslatef(230, 0, 0.0);
	GEAM();
	USA();
	STOPURI();
	PARBRIZ();
	FARURI();
	LUNETA();
	GEAM2();

}





void CALLBACK display(void) {


	GLfloat matUmbra[4][4];
	//oricare 3 pct din plan in sens CCW
	GLfloat puncte[3][3] = {
		{ -12.0f, -12.0f, -12.0f },
		{ -12.0f, -12.0f, 50.0f },
		{ 50.0f, -12.0f, 50.0f } };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MatriceUmbra(puncte, pozSursa, matUmbra);

	glPushMatrix();


	glLightfv(GL_LIGHT0, GL_POSITION, pozSursa);
	glColor3f(0.4, 0.4, 0.4);
	glRotatef(z, 0.0, 1.0, 0.0);
	glTranslatef(0, -17, 0.0);
	auxSolidBox(10000, 2, 500);
	glTranslatef(0, 17, 0.0);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-1000, -15, 0);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	gluCylinder(q, 3, 3, 20, 4, 10);
	glTranslatef(300, 15, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1000, -15, -95);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	gluCylinder(q, 3, 3, 2000, 4, 10);
	glTranslatef(300, 15, 75);
	glPopMatrix();

	glTranslatef(y, 0, 0.0);
	umbra = 0;
	glPushMatrix();

	glPushMatrix();



	glPopMatrix();

	AUTOBUZUL();

	glPopMatrix();
	


	glPopMatrix();
	glRotatef(z, 0.0, 0.0, 0.0);
	z = 0;
	
	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glMultMatrixf((GLfloat*)matUmbra);
	umbra = 1;

	glTranslatef(y, 0, 0.0);
	glPushMatrix();
	AUTOBUZUL();
	glPopMatrix();
	glPopMatrix();



  
	glPopAttrib();
	glPopMatrix();

	auxSwapBuffers();
}
void CALLBACK IdleFunction() {
	x = x + 30;
	y = y + 7.5;
	if (x == 300) {
		x = -120;
		y = -30;
	}
	display();
	Sleep(1000 / 20);

}

void CALLBACK myReshape(GLsizei w, GLsizei h) {
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-300, 300, -300 * (GLfloat)h / (GLfloat)w, 300 * (GLfloat)h / (GLfloat)w, -2000, 2000);
	else
		glOrtho(-300 * (GLfloat)w / (GLfloat)h, 300 * (GLfloat)w / (GLfloat)h, -300, 300, -2000, 2000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(30, 1, 0, 0);
	
}

int main(int argc, char** argv) {
	auxInitDisplayMode(AUX_DOUBLE | AUX_DEPTH16 | AUX_RGB);
	auxInitPosition(10, 10, 600, 600);
	auxKeyFunc(AUX_RIGHT, MutaDreapta);
	auxKeyFunc(AUX_LEFT, MutaStanga);
	auxKeyFunc(AUX_UP, MutaSus);
	auxKeyFunc(AUX_DOWN, MutaJos);
	auxKeyFunc(AUX_s, mutaSursaDreapta);
	auxKeyFunc(AUX_a, mutaSursaStanga);
	auxInitWindow("AUTOBUZ");
	myinit();
	auxReshapeFunc(myReshape);
	auxIdleFunc(IdleFunction);
	auxMainLoop(display);

	return 0;
}