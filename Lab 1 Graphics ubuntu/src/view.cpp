/*
 * view.cpp
 *
 *  Created on: Oct 10, 2013
 *      Author: AHMAD
 */

#include "view.h"
#include <stdio.h>
using namespace std;

view::view() {
	vao = -1;
}
void view::setView(GLuint program) {
	programId = program;
	GLfloat x = -0.80f, y = 0.75f - 3 * 0.09f;

	for (int i = 0; i < 6; i++) {
		x = -0.80f;
		for (int j = 0; j < 7; j++) {
			circles[i][j].setCircle(x, y, 0.09f, program);
			x += (3 * 0.09f);
		}
		y -= (3 * 0.09f);
	}

	GLfloat centerX = -0.80f, centerY = 0.75f;
	topCircle.setCircle(centerX, centerY, 0.09f, program);
	topCircle.setColor('r');

	create_rectangle(-.99, .65, .99, -.99);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, &vboID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	GLuint loc1 = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc1);
	glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

}

view::~view() {
	// TODO Auto-generated destructor stub
}
void view::create_rectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	GLuint i = 0;
	point[i] = vec2(x1, y1);
	color[i++] = vec3(0, 0, 1.0);
	point[i] = vec2(x2, y1);
	color[i++] = vec3(0, 0, 1.0);
	point[i] = vec2(x2, y2);
	color[i++] = vec3(0, 0, 1.0);
	point[i] = vec2(x1, y2);
	color[i++] = vec3(0, 0, 1.0);
}
void view::updateCircle(GLuint x, GLuint y, char color) {
	circles[x][y].setColor(color);
}
void view::updateTopCoin(GLfloat deltaX, GLfloat deltaY, GLfloat angle) {
	float myFloats[16] = { cos(angle * M_PI / 180.0), -sin(
			angle * M_PI / 180.0), 0.0f, deltaX, sin(angle * M_PI / 180.0), cos(
			angle * M_PI / 180.0), 0.0f, deltaY, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f };
	GLint uniTrans = glGetUniformLocation(programId, "mvMatrix");
//	glEnableVertexAttribArray(uniTrans);
	glUniformMatrix4fv(uniTrans, 1, false, myFloats);

}
void view::render(GLfloat mouseX, GLfloat mouseY, GLfloat angle) {
	GLfloat cX = topCircle.centerX();
	GLfloat diffX = mouseX - cX;
	GLfloat diffY = 0.0;

	updateTopCoin(0, 0, 0);
	glBindVertexArray(vao);
	glDrawArrays(GL_POLYGON, 0, 4);
	glBindVertexArray(0);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			circles[i][j].Bind();
			glDrawArrays(GL_TRIANGLE_FAN, 1, 30);
			circles[i][j].unBind();
		}
	}
	updateTopCoin(diffX, diffY, angle);
	glBindVertexArray(0);
	topCircle.Bind();
	glDrawArrays(GL_TRIANGLE_FAN, 1, 30);
	topCircle.unBind();
	updateTopCoin(0.0, 0.0, 0.0);

}

