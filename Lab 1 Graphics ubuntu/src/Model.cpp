/*
 * Model.cpp
 *
 *  Created on: Oct 10, 2013
 *      Author: motaz
 */

#include "Model.h"
#include <iostream>
using namespace std;

/**
 * Default Constructor.
 */
Model::Model() {
	// initiating attributes and the board.
	currentRole = false;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = 'a';
		}
	}
}

Model::~Model() {
}

void Model::setCurrentRole(bool flag) {
	currentRole = flag;
}

bool Model::getCurrentRole() {
	return currentRole;
}

/**
 * give it a column number so it can search for the suitable free location in the board to set it by the char c.
 */
int Model::setLoc(int x, char c) {
	if (x < 7 && x >= 0) {
		int loc = 5;
		for (int i = 0; i < 6; i++) {
			if (board[i][x] != 'a') {
				loc = i - 1;
				break;
			}
		}
		board[loc][x] = c;
		return loc;
	}
	return -1;
}

/**
 * Check the score.
 */

int Model::checkWinner(int x, int y) {
	// check the right hand side.
	char c = board[y][x];
	int count = 0;
	for (int i = x; i < 7; i++) {
		if (c == board[y][i])
			count++;
		else
			break;

	}

	// checking the left hand side.
	for (int i = x - 1; i >= 0; i--) {
		if (c == board[y][i])
			count++;
		else
			break;
	}
	if (count >= 4)
		return 1;

	// checking the bottom.
	count = 0;
	for (int i = y; i < 7; i++) {
		if (c == board[i][x])
			count++;
		else
			break;
	}
	if (count >= 4)
		return 1;

	// checking the Right + UP.
	count = 0;
	int j = x;
	for (int i = y; i >= 0; i--) {
		if (j < 7 && c == board[i][j])
			count++;
		else
			break;
		j++;
	}

	// checking the left + down.
	j = x - 1;
	for (int i = y + 1; i < 7; i++) {
		if (j >= 0 && c == board[i][j])
			count++;
		else
			break;
		j--;
	}

	if (count >= 4)
		return 1;

	// checking the left + UP.
	count = 0;
	j = x;
	for (int i = y; i >= 0; i--) {
		if (j >= 0 && c == board[i][j])
			count++;
		else
			break;
		j--;
	}

	// checking the right + down.
	j = x + 1;
	for (int i = y + 1; i < 7; i++) {
		if (j < 7 && c == board[i][j])
			count++;
		else
			break;
		j++;
	}

	if (count >= 4)
		return 1;
	return -1;
}
/**
 * Check if the Board is Full or Not.
 */
bool Model::isBoardFull() {
	int count = 0;
	for (int i = 0; i < 7; i++) {
		if (board[0][i] != 'a') {
			count++;
		}
	}
	if (count == 7) {
		return true;
	}
	return false;
}
