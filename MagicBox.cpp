#include <windows.h>
#include <GL/glut.h>

bool isjumping = false;
GLfloat posX = 0.0f, posY = 0.0f;
bool white = false;
GLclampf v1[3] =
{ 1.0f, 0.0f, 0.0f }, v2[3] =
{ 0.0f, 1.0f, 0.0f }, v3[3] =
{ 0.0f, 0.0f, 1.0f }, v4[3] =
{ 0.1f, 0.0f, 0.5f };
GLclampf v1d[3] =
{ 1.0f, 0.0f, 0.0f }, v2d[3] =
{ 0.0f, 1.0f, 0.0f }, v3d[3] =
{ 0.0f, 0.0f, 1.0f }, v4d[3] =
{ 0.1f, 0.0f, 0.5f };
void gravity(GLfloat gravity);

void initGL();
void display();
void reshape(GLsizei width, GLsizei height);
void keyHandler(unsigned char key, int x, int y);
void colorCopy(GLclampf copy[], GLclampf original[]);
void Timer(int value);
void movement(unsigned char key);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("Color Wheel");
	glutInitWindowSize(640, 320);
	glutInitWindowPosition(0, 0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(0, Timer, 0);
	glutKeyboardFunc(keyHandler);
	initGL();
	glutMainLoop();

	return 0;
}
void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(posX, posY, 0.0f);
	glBegin(GL_QUADS);
	glColor3fv(v1);
	glVertex2f(0.0f, 0.0f);
	glColor3fv(v2);
	glVertex2f(0.0f, 0.5);
	glColor3fv(v3);
	glVertex2f(0.5f, 0.5f);
	glColor3fv(v4);
	glVertex2f(0.5f, 0.0f);
	glEnd();

	glutSwapBuffers();

	if (isjumping)
	{
		posY += 0.3f;
		isjumping = false;
	}
	else

		gravity(0.015);
}
void reshape(GLsizei width, GLsizei height)
{
	if (height == 0)
		height = 1;
	GLfloat aspect = (GLfloat) width / (GLfloat) height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

if(width >= height)
		gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
else
		gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);

}
void movement(unsigned char key)
{
	switch (key)
	{
	case 'a':
		posX -= 0.05f;
		break;
	case 'd':
		posX += 0.05f;
		break;
	case 'w':
		if (posY <= -1)
			isjumping = true;
	}
}

void colorCopy(GLclampf copy[], GLclampf original[])
{
	for (int i = 0; i < 3; i++)
		copy[i] = original[i];
}
void keyHandler(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'k':
		{
		if (white)
			{
			colorCopy(v1, v1d);
			colorCopy(v2, v2d);
			colorCopy(v3, v3d);
			colorCopy(v4, v4d);
			}
		else
			for (int i = 0; i < 3; i++)
			{
				v1[i] = 1.0;
				v2[i] = 1.0;
				v3[i] = 1.0;
				v4[i] = 1.0;
			}
		white = !white;
		break;
	}
	case 'w':
	case 'a':
	case 'd':
		movement(key);
		break;
	}

}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, Timer, 0);
}
void gravity(GLfloat gravity)
{
	if (posY > -1)
		posY -= gravity;
}


