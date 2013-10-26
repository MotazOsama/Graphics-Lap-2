/*
 * Model.h
 *
 *  Created on: Oct 10, 2013
 *      Author: motaz
 */

#ifndef MODEL_H_
#define MODEL_H_

class Model {

public:
	Model();
	char board[6][7];
	bool currentRole;

	virtual ~Model();
	char** getBoard();
	bool getCurrentRole();
	void setCurrentRole(bool flag);
	int setLoc(int x, char c);
	int checkWinner(int x, int y);
	bool isBoardFull();
private:

protected:

};

#endif /* MODEL_H_ */
