
//-------------------
//|     |     |     |
//| 3:1 | 3:2 | 3:3 |
//-------------------
//|     |     |     |
//| 2:1 | 2:2 | 2:3 |
//-------------------
//|     |     |     |
//| 1:1 | 1:2 | 1:3 |
//-------------------
#include <iostream>
#include <conio.h>

using namespace std;

class Position {
	int vert;
	int hor;

public:
	void setVert(int vert) {
		this->vert = vert;
	}
	int getVert() {
		return this->vert;
	}
	void setHor(int hor) {
		this->hor = hor;
	}
	int getHor() {
		return this->hor;
	}
};

class Piece {
	string type;
	string color;
	Position pos;

public:
	void setPos(int hor, int vert) {
		Position pos;
		pos.setHor(hor);
		pos.setVert(vert);
		this->pos = pos;
	}
	Position getPos() {
		return this->pos;
	}
	void moveUp() {
		if (pos.getVert() < 3) {
			pos.setVert(pos.getVert() + 1);
		}
	}
	void moveDown() {
		if (pos.getVert() > 1) {
			pos.setVert(pos.getVert() - 1);
		}
	}
	void moveRight() {
		if (pos.getHor() < 3) {
			pos.setHor(pos.getHor() + 1);
		}
	}
	void moveLeft() {
		if (pos.getHor() > 1) {
			pos.setHor(pos.getHor() - 1);
		}
	}
};

int main() {

	Piece piece;
	piece.setPos(2, 2);




	cout << "Current position is: "
		<< piece.getPos().getVert() << " - "
		<< piece.getPos().getHor() << endl;
}