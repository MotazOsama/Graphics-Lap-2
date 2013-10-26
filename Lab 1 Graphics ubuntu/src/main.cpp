/*
 * main.cpp
 *
 *      Controller Class.
 *
 *  Created on: Oct 8, 2013
 *      Author: AHMAD
 */
#include <math.h>
#include "include/Angel.h"
#include "Circle.h"
#include "view.h"
#include "Model.h"
#include <sstream>
#include <string> // this should be already included in <sstream>
using namespace std;
view myview;
Model model;
GLuint program, win_width, startX, radius, lastLoc, red_score, yellow_score,
		falling_counter = 1;
GLfloat mouseX = -0.80f, mouseY = 0.75f, falling_dest, dy = 0, rotation_angle =
		0;
GLchar top_coin_color;

void text() {
	glRasterPos2f(-.99f, .90f);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	string Result;
	ostringstream convert;
	convert << red_score;
	Result = convert.str();
	ostringstream convert1;
	string Result1;
	convert1 << yellow_score;
	Result1 = convert1.str();
	string c = "Red score : " + Result + " Yellow score : " + Result1;
	for (int i = 0; i < c.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c.data()[i]);
	}
}

void init() {
	// Load shaders and use the resulting shader program
	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);
	red_score = 0;
	yellow_score = 0;
	myview.setView(program);
	glClearColor(1.0, 1.0, 1.0, 1.0); // white background

}
void update(int value) {

	if (myview.topCircle.centerY() + dy >= falling_dest) {
		falling_counter = 1;
		dy = 0;
//		myview.updateCircle()
	} else {
		dy = 0.04;
		falling_counter++;
		rotation_angle = 30;
		//Tell GLUT to call update again in 25 milliseconds
		glutTimerFunc(25, update, 0);
	}
	glutPostRedisplay(); //Tell GLUT that the scene has changed

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);     // clear the window
	text();
	myview.render(mouseX, dy * falling_counter, rotation_angle);
	glFlush();
}

/**
 * Callback for the keyboard handle.
 */

void keyboardHandle(unsigned char key, int x, int y) {
	int col = lastLoc;
	char color = 'w';
	if (key == 13 && col < 7 && col >= 0) {
		//glutTimerFunc(25, update, 0); //Add a timer
		int row = 0;
		if (model.currentRole == false) {
			row = model.setLoc(col, 'b');
			if (row != -1) {
				color = 'r';
				top_coin_color = 'y';
				model.currentRole = true;
			}
		} else {
			row = model.setLoc(col, 'c');
			if (row != -1) {
				color = 'y';
				top_coin_color = 'r';
				model.currentRole = false;
			}
		}
		if (row != -1) {
			myview.topCircle.setColor(top_coin_color);
			myview.updateCircle(row, col, color);
			glutPostRedisplay();
			if (model.checkWinner(col, row) == 1) {
				if (model.currentRole == true) {
					cout << "Red Player Wins." << endl;
					red_score++;
				} else {
					cout << "Yellow Player Wins." << endl;
					yellow_score++;
				}
			}
		}
	} else if (key == 114 && model.isBoardFull()) {
		Model m;
		model = m;
		cout << "yes i am here" << endl;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				myview.updateCircle(i + 1, j, 'w');
			}
		}
		glutPostRedisplay();
	}
}

/**
 * Callback for Mouse Handle.
 */
void mouseClickHandle(int button, int state, int x, int y) {
	if (state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON) {
			//glutTimerFunc(25, update, 0); //Add a timer
			int x_relToBoard = x - (startX) - radius;
			int col = ceil(x_relToBoard / (3 * radius));
			cout << "column " << col << endl;
			if (col <= 6) {
				char color = 'w';
				int row = 0;
				if (model.currentRole == false) {
					row = model.setLoc(col, 'b');
					cout << "row " << row << endl;
					if (row != -1) {
						color = 'r';
						top_coin_color = 'y';
						model.currentRole = true;
					}
				} else {
					row = model.setLoc(col, 'c');
					cout << "row " << row << endl;
					if (row != -1) {
						color = 'y';
						top_coin_color = 'r';
						model.currentRole = false;
					}
				}
				if (row != -1) {
					myview.topCircle.setColor(top_coin_color);
					myview.updateCircle(row, col, color);
					glutPostRedisplay();
					if (model.checkWinner(col, row) == 1) {
						if (model.currentRole == true) {
							cout << "Red Player Wins." << endl;
							red_score++;
						} else {
							cout << "Yellow Player Wins." << endl;
							yellow_score++;
						}
					}
				}
			}
		}
	}
}
/**
 * Callback for Mouse Motion without any clicks.
 */
void mouseMotionHandle(int x, int y) {
//	GLuint mouseX = 1 ;
//	GLuint mouseY = 1 ;

	int x_relToB = x - (startX) - radius;
	int col = ceil(x_relToB / (3 * radius));
	if (col > 6) {
//		myview.updateCircle(0, lastLoc, 'w');
		mouseX = myview.circles[0][lastLoc].centerX();
	} else {
//		myview.updateCircle(0, lastLoc, 'w');
		lastLoc = col;
		mouseX = myview.circles[0][col].centerX();

//		myview.updateCircle(0, col, top_coin_color);
	}
//	mouseX = x_relToB;
//	mouseY = y;
	glutPostRedisplay();
}

/**
 * Callback for resizing window.
 */
void reshape(int w, int h) {
	win_width = w;
	startX = w / 2 - 250;
	radius = 500 / 2 * 0.09;
//	glViewport(0, h - 470, (GLsizei) 500, (GLsizei) 500); // Set our viewport to the size of our window
	glViewport(w / 2 - 250, h - 500, (GLsizei) 500, (GLsizei) 500); // Set our viewport to the size of our window
}

int main(int argc, char **argv) {

	lastLoc = 0;
	top_coin_color = 'r';

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Connect 4");
	glewInit();
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardHandle);
	glutMouseFunc(mouseClickHandle);
	glutPassiveMotionFunc(mouseMotionHandle);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

