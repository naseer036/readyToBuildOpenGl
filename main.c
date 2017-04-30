#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structures:

// A point in the window relative to the lower left corner.
// Up and right are positive directions.
// Measured as pixel coordinates.

struct point {
	int x;
	int y;
};

// A line between two points.

struct line {
	struct point start;
	struct point end;
};

// A rectangle between two opposite corners.

struct rectangle {
	struct point cornerA;
	struct point cornerB;
};

// A polygon represented as a dynamic array of points.
// These must be in counter-clockwise order (so the front is facing towards the
// camera)

struct polygon {
	struct point* vertices;
	size_t vertexCount;
};

// A circle on the window.
// It has an origin and a radius.

struct circle {
	struct point origin;
	int radius;
};

float j = 100.0;
float rotationAngle = 0.0f; // The angle of rotation for our object  
float i = 100.0f;
const double PI = 3.141592654;

// Functions:

void printText(struct point coords, const char* text) {
	// Set the starting position for the text
	glRasterPos2i(coords.x, coords.y);

	// Render the text
	for (size_t i = 0; text[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

void drawRectangles(struct rectangle* rectArray, size_t rectArrayLength) {
	struct rectangle currentRect;

	glBegin(GL_QUADS);

	// Pass in the vertices of each rectangle
	for (size_t i = 0; i < rectArrayLength; i++) {
		currentRect = rectArray[i];

		// This keeps the points being passed in in counter-clockwise order.
		if (currentRect.cornerA.x < currentRect.cornerB.x) {
			glVertex2i(currentRect.cornerA.x, currentRect.cornerA.y);
			glVertex2i(currentRect.cornerB.x, currentRect.cornerA.y);
			glVertex2i(currentRect.cornerB.x, currentRect.cornerB.y);
			glVertex2i(currentRect.cornerA.x, currentRect.cornerB.y);
		} else {
			glVertex2i(currentRect.cornerA.x, currentRect.cornerA.y);
			glVertex2i(currentRect.cornerA.x, currentRect.cornerB.y);
			glVertex2i(currentRect.cornerB.x, currentRect.cornerB.y);
			glVertex2i(currentRect.cornerB.x, currentRect.cornerA.y);
		}
	}

	glEnd();
}

void drawPoints(struct point* pointArray, size_t pointArrayLength) {
	struct point currentPoint;

	glBegin(GL_POINTS);

	// Pass in each point as a vertex
	for (size_t i = 0; i < pointArrayLength; i++) {
		currentPoint = pointArray[i];

		glVertex2i(currentPoint.x, currentPoint.y);
	}

	glEnd();
}

void drawLines(struct line* lineArray, size_t lineArrayLength) {
	struct line currentLine;

	glBegin(GL_LINES);

	// Pass in the start and end points of each line
	for (size_t i = 0; i < lineArrayLength; i++) {
		currentLine = lineArray[i];

		glVertex2i(currentLine.start.x, currentLine.start.y);
		glVertex2i(currentLine.end.x, currentLine.end.y);
	}

	glEnd();
}

void drawPolygons(struct polygon* polygonArray, size_t polygonArrayLength) {
	struct polygon currentPolygon;

	// Pass in the vertices of each polygon.
	for (size_t i = 0; i < polygonArrayLength; i++) {
		currentPolygon = polygonArray[i];

		glBegin(GL_POLYGON);

		for (size_t j = 0; j < currentPolygon.vertexCount; j++) {
			glVertex2i(currentPolygon.vertices[j].x, currentPolygon.vertices[j].y);
		}

		glEnd();
	}
}

void rocket() {
	// struct rectangle rectangle1 = { { 350, 175 }, { 450, 450 } };
	// struct rectangle rectangle2 = { { 500, 275 }, { 550, 550 } };
	struct rectangle rectangle3 = {
		{ 100, 100},
		{ 200, 200}
	};

	struct point allPoints[6] = {
		{ 100, 100},
		{ 300, 450},
		{ 450, 450},
		{ 450, 170},
		{ 550, 370},
		{ 150, 150}
	};
	//	printText(allPoints[0], "a");
	//	printText(allPoints[1], "b");
	//	printText(allPoints[2], "c");
	//	printText(allPoints[3], "d");
	struct line line1 = {allPoints[0], allPoints[5]};
	struct point polygonPoints[5] = {allPoints[0], allPoints[1], allPoints[2], allPoints[3], allPoints[4]};

	// No need to free polygonPoints after this is used, because local variable
	// If it were dynamically allocated (malloc, calloc) then it should be freed
	struct polygon polygon1 = {polygonPoints, 5};

	glColor3f(1.0, 1.0, 0.0);

	//	drawRectangles(&rectangle3, 1);
	drawLines(&line1, 1);
	//	drawPolygons(&polygon1, 1);
	//drawWheel;
	glColor3f(1.0, 0.0, 1.0);

	//	drawPoints(allPoints, 6);
}

void moveObject(void functionToDrawObject(), struct point offset) {
	glPushMatrix();
	glTranslatef(offset.x, offset.y, 0.0f);
	functionToDrawObject();
	glPopMatrix();
}

void rotateObjectWithMovement(void functionToDrawObject(), struct point pivot, float rotationAngle) {
	glPushMatrix();
	glTranslatef(pivot.x, pivot.y, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	functionToDrawObject();
	glPopMatrix();
}

void rotateObjectWithoutMovement(void functionToDrawObject(), struct point pivot, float rotationAngle) {
	glPushMatrix();
	glTranslatef(pivot.x, pivot.y, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-pivot.x, -pivot.y, 0.0f);
	functionToDrawObject();
	glPopMatrix();
}

//
//void drawDisk(double radius) {
//	int d;
//	glBegin(GL_POLYGON);
//	for (d = 0; d < 32; d++) {
//		double angle = 2 * PI / 32 * d;
//		glVertex2d(radius * cos(angle), radius * sin(angle));
//	}
//	glEnd();
//}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//	struct point offset = {i,200};
	//	struct point pivot = {100,170};

	//	glPushMatrix();
	//	glLoadIdentity();
	//	moveObject(rocket,offset);
	//	rotateObject(rocket,offset,rotationAngle);
	//	glPopMatrix();
//	glTranslated(j, 100, 0);
//	//	glScaled(0.3,0.3,1);
//	glRotatef(rotationAngle, 0, 0, 1);
//	rocket();
	struct point pivot={j,100};
//	rotateObjectWithoutMovement(rocket,pivot,rotationAngle);
	rotateObjectWithMovement(rocket,pivot,rotationAngle);

	glBegin(GL_LINES);
	glVertex2f(0, 100);
	glVertex2d(1000, 100);
	glEnd();
	j += 1;
	glutSwapBuffers(); // Swap our buffers  
	rotationAngle += 0.5f; // Increment our rotation value  
	if (rotationAngle > 360.0f) // If we have rotated beyond 360 degrees (a full rotation)  
		rotationAngle -= 360.0f; // Subtract 360 degrees off of our rotation
	//	i++;
}

void myinit() {
	//	glClearColor(0.0, 0.0, 0.8, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//     I'm guessing there's a reason to use right and top parameters different
	//     to the window dimensions
	gluOrtho2D(0.0, 988.0, 0.0, 999.0);
	glLineWidth(4.0);
	glPointSize(5.0);
	glClearColor(0.5f, 0.5f, 1, 1);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Hierarchical Modeling 2D Example");

	myinit();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	//    glutTimerFunc(200,doFrame,0); 

	glutMainLoop();
	return 0;
}