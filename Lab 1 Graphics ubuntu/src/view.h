/*
 * view.h
 *
 *  Created on: Oct 10, 2013
 *      Author: AHMAD
 */
#include "Circle.h"
#ifndef VIEW_H_
#define VIEW_H_

class view {
public:
	Circle circles[6][7];
	Circle topCircle;
	vec2 point[4];
	vec3 color[4];
	GLuint vao, vboID[2];
	GLuint programId;
	view();
	void updateTopCoin(GLfloat dx, GLfloat dy, GLfloat angle);
	void setView(GLuint program);
	void render(GLfloat mouseX, GLfloat mouseY, GLfloat angle);
	void updateCircle(GLuint x, GLuint y, char color);

	virtual ~view();
private:
	void create_rectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
};

#endif /* VIEW_H_ */
