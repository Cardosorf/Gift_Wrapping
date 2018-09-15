#include <OpenGL/gl.h>     // The GL Header File
#include <cmath>
#include <stdlib.h>
#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
//Width and height of the window. If necessary, change these values.
#define WIDTH 800
#define HEIGHT 600

using namespace std;

//Creates a class to handle OrderedPairs
class OrderedPair {

public:
	float getAxis_x(void);
	float getAxis_y(void);
	OrderedPair(float x_value, float y_value);

private:
	float x;
	float y;
};

//Sets the ordered pair
OrderedPair::OrderedPair(float x_value, float y_value) {
	x = x_value;
	y = y_value;
}

float OrderedPair::getAxis_x(void) {
	return x;
}

float OrderedPair::getAxis_y(void) {
	return y;
}

int firstClick = 0;
bool polygon = false;
vector<OrderedPair> pointsArray;

void mouse(int button, int state, int x, int y) {

	float dx, dy;
	int intercept = 0;

	
	glColor3f(0.0, 0.0, 1.0);
	//Left button click draws points on the screen and each point is stored inside a vector. 
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
		pointsArray.push_back(OrderedPair((2.*x) / WIDTH - 1, -(2.*y) / HEIGHT + 1));
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPointSize(6);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < (int)pointsArray.size(); i++) {
			glVertex2f(pointsArray[i].getAxis_x(), pointsArray[i].getAxis_y());
		}
		glEnd();
		glFlush();
		glutSwapBuffers();
	}

	//Finds the points wich belong to the convex hull.
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && pointsArray.size() > 2) {
		OrderedPair leftmost = pointsArray[0];
		for (int i = 0; i < (int)pointsArray.size(); i++) {
			if (pointsArray[i].getAxis_x() < leftmost.getAxis_x())
				leftmost = pointsArray[i];
		}

		OrderedPair previous = leftmost;
		vector<OrderedPair> temp; 
		temp.push_back(leftmost);
		OrderedPair next(leftmost.getAxis_x(), -1);

		while (true) {
			float val;
			OrderedPair pivottemp = pointsArray[0];

			for (int i = 0; i < (int)pointsArray.size(); i++) {

				//Cross Product: ab * ac
				val = ((previous.getAxis_y() - pointsArray[i].getAxis_y()) * (previous.getAxis_x() - next.getAxis_x())) - ((previous.getAxis_y() - next.getAxis_y()) * (previous.getAxis_x() - pointsArray[i].getAxis_x()));
			
				//if Cross Product > 0, then this point may be one of those from the convex hull if the following val are < 0.
				if (val > 0) {
					next = pointsArray[i];
				}
			
			}

			temp.push_back(next);
			pivottemp = next;
			next = previous;
			previous = pivottemp;

			if (temp.front().getAxis_x() == temp.back().getAxis_x() && temp.front().getAxis_y() == temp.back().getAxis_y()) {
				break;
			}

		}

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < (int)temp.size(); i++) {
			glVertex2f(temp[i].getAxis_x(), temp[i].getAxis_y());
		}
		glEnd();
		glFlush();
		glutSwapBuffers();

	}

}

//Print the header with my name, dre and instructions
void header() {
	//Sets the position of the text in the window using the x and y coordinates
	glRasterPos2f(-1, 0.9);
	string name = "Rafael Pais Cardoso\n";
	string dre = "DRE: 116140788";
	string instruction1 = "Left mouse button -> creates connected points by lines";
	string instruction2 = "Right mouse button -> Gift wrap the points";
	string instruction3 = "Enjoy :)";
	int len_name = (int)name.length();
	int len_dre = (int)dre.length();
	int len_instruction1 = (int)instruction1.length();
	int len_instruction2 = (int)instruction2.length();
	int len_instruction3 = (int)instruction3.length();

	//Loops to display character by character
	for (int i = 0; i < len_name; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name[i]);
	}

	glRasterPos2f(-1, 0.8);
	for (int i = 0; i < len_dre; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, dre[i]);
	}

	glRasterPos2f(-1, 0.7);
	for (int i = 0; i < len_instruction1; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction1[i]);
	}

	glRasterPos2f(-1, 0.6);
	for (int i = 0; i < len_instruction2; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction2[i]);
	}

	glRasterPos2f(-1, 0.5);
	for (int i = 0; i < len_instruction3; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction3[i]);
	}
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(4.0);
	header();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Rafael Pais Cardoso");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
	return EXIT_SUCCESS;
}
