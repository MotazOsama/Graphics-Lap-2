/*
 * Circle.cpp
 *
 *  Created on: Oct 10, 2013
 *      Author: AHMAD
 */

#include "Circle.h"
using namespace std;
const GLuint number_of_points = 31;
Circle::Circle() {
	vao = -1;
}
void Circle::setCircle(GLfloat x, GLfloat y, GLfloat radius, GLuint program) {
	create_circle(x, y, radius);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, &vboID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	GLuint loc1 = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc1);
	glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glBindVertexArray(0);
}

Circle::~Circle() {
}
void Circle::Bind() {
	glBindVertexArray(vao);
}
void Circle::unBind() {
	glBindVertexArray(0);
}

GLuint Circle::getVao() {
	return vao;
}
void Circle::setColor(char color) {
	for (int i = 0; i < number_of_points; ++i) {
		if (color == 'r')
			colors[i] = vec3(1.0, 0, 0);
		else if (color == 'y')
			colors[i] = vec3(1.0, 1.0, 0);
		else
			colors[i] = vec3(1.0, 1.0, 1.0);
	}
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

}
void Circle::create_circle(GLfloat x, GLfloat y, GLfloat radius) {
	GLuint i = 0;
	GLfloat twoPi = 2.0f * 3.14159f;
	points[i] = vec2(x, y);
	colors[i++] = vec3(0.0, 0.0, 0.0);
	for (int j = 0; j < number_of_points; j++) { // make $section number of circles
		GLfloat x1 = x + radius * cos(j * twoPi / number_of_points);
		GLfloat y1 = y + radius * sin(j * twoPi / number_of_points);
		points[i] = vec2(x1, y1);
		if (j > number_of_points / 2) {
			colors[i++] = vec3(1.0, 1.0, 1.0);
		} else {
			colors[i++] = vec3(0.0, 0.0, 0.0);
		}
	}
}

GLfloat Circle::centerX() {
	return points[0].x;
}
GLfloat Circle::centerY() {
	return points[0].y;
}
