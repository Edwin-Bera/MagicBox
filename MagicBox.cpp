/*
 * Author: Edwin Bera
 * This program uses openGL to create a square that changes color based on a button press and can be moved around using the WASD keys.
 */
#include <windows.h>
#include <GL/glut.h>

bool isjumping = false;
GLfloat posX = 0.0f, posY = 0.0f;// the square's location in x, y coordinates.
bool white = false;
GLclampf v1[3], v2[3], v3[3], v4[3];// arrays that each store the RGB value of each of the squares vertices.
GLclampf v1d[3] =		//arrays containing the default color of the vertices.
{ 1.0f, 0.0f, 0.0f }, v2d[3] =
{ 0.0f, 1.0f, 0.0f }, v3d[3] =
{ 0.0f, 0.0f, 1.0f }, v4d[3] =
{ 0.1f, 0.0f, 0.5f };
/**
 * gravity -exerts a constant force on the square.
 * @gravity: TThe value of the downward force.
 */
void gravity(GLfloat gravity);
/**
 * initGL -Sets the background color to black and initializes the vertex colors to their default configuration.
 */
void initGL();
/**
 * display -handler function for displaying images on the screen.
 */
void display();
/**
 * reshape  -handler function for window resize event. Prevents objects on screen form becoming distorted
 * 			 due to change in the windows aspect ratio.
 * @width: width of the window.
 * @height: height of the window.
 */
void reshape(GLsizei width, GLsizei height);
/**
 * keyHandler -function for handling key presses.
 * @key: the key pressed.
 * @x: the mouse location in x coordinates.
 * @y: the mouse location in y coordinates.
 */
void keyHandler(unsigned char key, int x, int y);
/**
 * colorCopy -copy's RGB values from one array to the other.
 * @original: the array from which values are copied.
 *@copy: the array to which values are copied.
 */
void colorCopy(GLclampf copy[], const GLclampf original[]);
/**
 * Timer - waits the specified amount of time before putting up a new frame.
 * @value: the time to wait in milliseconds
 */
void Timer(int value);
/**
 * movement -handles the squares movement in the x direction
 * @key: the key pressed
 */
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
	colorCopy(v1, v1d);
	colorCopy(v2, v2d);
	colorCopy(v3, v3d);
	colorCopy(v4, v4d);
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

	if (isjumping)		//if jumping, move the square up in the y-direction
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
	case 'a':			//if 'a' is pressed, move the square to the left
		posX -= 0.05f;
		break;
	case 'd':			//if 'd' is pressed, move the square to the right
		posX += 0.05f;
		break;
	case 'w':			//if 'w' is pressed, jump
		if (posY <= -1)
			isjumping = true;
	}
}

void colorCopy(GLclampf copy[], const GLclampf original[])
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
			for (int i = 0; i < 3; i++)		//turn the square white
			{
				v1[i] = 1.0;
				v2[i] = 1.0;
				v3[i] = 1.0;
				v4[i] = 1.0;
			}
		white = !white;						//update state
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


