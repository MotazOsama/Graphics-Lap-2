/*
 * Circle.h
 *
 *  Created on: Oct 10, 2013
 *      Author: AHMAD
 */
#include "include/Angel.h"
#ifndef CIRCLE_H_
#define CIRCLE_H_

class Circle {
public:
	vec2 points[31];
	vec3 colors[31];
	Circle();
	void setCircle(GLfloat x, GLfloat y, GLfloat radius, GLuint program);
	void Bind();
	void unBind();
	GLuint getVao();
	void setColor(char color);
	GLfloat centerY();
	GLfloat centerX();
	virtual ~Circle();
private:
	void create_circle(GLfloat x, GLfloat y, GLfloat radius);

	GLuint vao;
	GLuint vboID[2];

};

#endif /* CIRCLE_H_ */
