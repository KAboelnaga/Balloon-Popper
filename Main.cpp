#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int viewWidth = 800;
int viewHeight = 600;
int logWidth = 100;
int logHeight = 100;
int centerX = logWidth / 2, centerY = logHeight / 2;
bool bUp1 = true;
int dy1 = 0;
bool bUp2 = true;
int dy2 = 0;
int maxY = 100;
bool flag = false;
int status = 0;
double mouseXX, mouseYY;
int r = 2;
int cx1 = 30, cy1 = 0, cx2 = 60, cy2 = 0;
int score = 0;
int bcount = 0;
int sqWid = 20;
int alphaX = 0;
int new1;
int new2;
int window1;
int flag2 = 0;
int game = 1;
void init()
{

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, logWidth, 0.0, logHeight);

}
void printSome(char* str, int x, int y) {
	glColor3f(1, 1, 1);
	glRasterPos2d(x - 4, y);
	for (int i = 0; i < strlen(str); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	glFlush();
}
void Keyboard(unsigned char key, int x, int y) {
	if (key == 'a' )
		alphaX -= 5;
		if (key == 'd')
		alphaX += 5;
		glutPostRedisplay();
}
void specialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		alphaX -= 5;
	if (key == GLUT_KEY_RIGHT)
		alphaX += 5;
	if (key == GLUT_KEY_F1)
	{
		dy1 = 0;
		dy2 = -50;
		score = 0;
		bcount = 0;
		game = 1;
	}
	glutPostRedisplay();
}
void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseXX = x;
		mouseXX = 0.5 + 1.0 * mouseXX * logWidth / viewWidth;
		mouseYY = viewHeight - y;
		mouseYY = 0.5 + 1.0 * mouseYY * logHeight / viewHeight;
		if (bUp1 && (mouseXX >= (cx1 - r) && mouseXX <= (cx1 + r) && mouseYY >= (cy1 - dy1 - r) && mouseYY <= (cy1 + dy1 + r)))
		{
			bcount++;
			status = 1;
			score += 1;
			dy1 = -50;
			cy1 = 0;
			new1 = rand() % 1000;
			cx1 = (cx1 + new1) % 100;
			bUp1 = true;
		}
		if (bUp2 && (mouseXX >= (cx2 - r) && mouseXX <= (cx2 + r) && mouseYY >= (cy2 - dy2 - r) && mouseYY <= (cy2 + dy2 + r)))
		{
			bcount++;
			status = 2;
			score += 2;
			dy2 = -50;
			cy2 = 0;
			new2 = rand() % 1000;
			cx2 = (cx2 + new2) % 100;
			bUp2 = true;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		status = 0;
	}
	glutPostRedisplay();
}

void Timer(int value) {

	glutTimerFunc(15, Timer, value);
	glutPostRedisplay();

}
void DrawCircle2(float cx, float cy, float r, int num_segments)
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
		float cx2 = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx2 + cx + 2, y + cy + dy2);
	}
	glEnd();
	if (abs(dy2) > maxY) bUp2 = !bUp2;
	if (bUp2) dy2 += 1; else dy2 -= 3;
	if (!bUp2 && dy2 < 3) {
		new2 = rand() % 1000;
		cx2 = (cx2 + new2) % 100;
		bcount ++;
		bUp2 = true;
	}
	if (!bUp2 && dy2 <= 6) {
		if (cx2 > centerX - sqWid / 2 + alphaX && cx2 < centerX + sqWid / 2 + alphaX)
		{
			score++;
		}
		else
		{
			score--;
		}
	}

}
void DrawCircle(int cx, int cy, float r, int num_segments)
{

		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		for (int i = 0; i < num_segments; i++) {
			float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
			float x = r * cosf(theta);
			float y = r * sinf(theta);
			glVertex2f(x + cx, y + cy + dy1);
		}
		glEnd();
		if (abs(dy1) > maxY) bUp1 = !bUp1;
		if (bUp1) dy1 += 1; else dy1 -= 3;
		if (!bUp1 && dy1 < 3) {
			new1 = rand() % 1000;
			bcount++;
			cx1 = (cx1 + new1) % 100;
			bUp1 = true;
		}
		if (!bUp1 && dy1 <= 6) {
			if ( cx1 > centerX - sqWid / 2 + alphaX && cx1 < centerX + sqWid / 2 + alphaX)
			{
				score++;
			}
			else
			{
				score--;
			}
		}
		if (bUp1 && dy1 > 40)
		{
			flag = true;
		}
		if (flag)
		{
			DrawCircle2(cx2, cy2, r, 360);
		}

}

void Display()
{
	
	char scoreF[32];
	int scoreFinal;
	if (game == 1)
	{
		glClearColor(0.0, 0.0, 1.0, 1.0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		DrawCircle(cx1, cy1, r, 360);
		glColor3f(0, 1, 0);
		glBegin(GL_QUADS);

		glVertex2i(0, 0);
		glVertex2i(0, 10);
		glVertex2i(100, 10);
		glVertex2i(100, 0);

		glEnd();
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glBegin(GL_POLYGON); // Each set of 4 vertices form a quad
		glVertex2f(centerX - sqWid / 2 + alphaX, 0); // x, y
		glVertex2f(centerX + sqWid / 2 + alphaX, 0); // x, y
		glVertex2f(centerX + sqWid / 2 + alphaX, 15); // x, y
		glVertex2f(centerX - sqWid / 2 + alphaX, 15); // x, y
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		char scoreText[32];
		snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
		printSome(scoreText, centerX, maxY - 10);
		char count[32];
		snprintf(count, sizeof(count), "Balloons: %d", bcount);
		printSome(count, centerX, maxY - 15);
	}
	if (bcount == 20)
	{
		game = 0;
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1.0);
		glColor3f(0.0, 0.0, 0.0);
		scoreFinal = score;
		snprintf(scoreF, sizeof(scoreF), "Score: %d", scoreFinal);
		printSome(scoreF, centerX, centerY + 5);
		char play[32];
		snprintf(play, sizeof(play), "press F1 to play");
		printSome(play, centerX, centerY - 5);
	}
	glFlush();
	glutSwapBuffers();

}
int main(int argc, char** argv)
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(viewWidth, viewHeight);
		window1 = glutCreateWindow("balloon Popper");
		init();
		glutDisplayFunc(Display);
		glutDisplayFunc(Display);
		glutMouseFunc(mouseClick);
		glutSpecialFunc(specialKeyboard);
		glutKeyboardFunc(Keyboard);
		Timer(0);
		glutMainLoop();
	}