#include <windows.h>
#include <GL/glut.h>

void display();
void reshape(GLsizei width, GLsizei height);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("Color Wheel");
	glutInitWindowSize(640, 320);
	glutInitWindowPosition(0, 0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.5);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, 0.5f);
	glColor3f(0.1f, 0.0f, 0.5f);
	glVertex2f(0.5f, 0.0f);
	glEnd();

	glFlush();
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
