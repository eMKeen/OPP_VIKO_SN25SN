
//-------------------
//|     |     |     |
//| 1:1 | 1:2 | 1:3 |
//-------------------
//|     |     |     |
//| 2:1 | 2:2 | 2:3 |
//-------------------
//|     |     |     |
//| 3:1 | 3:2 | 3:3 |
//-------------------
#include <iostream>
#include <conio.h>
#include "Source.h"
#include <format>
#include <windows.h>

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
		if (pos.getVert() < table.getTableHeight()) {
			pos.setVert(pos.getVert() + 1);
		}
	}
	void moveDown() {
		if (pos.getVert() > 1) {
			pos.setVert(pos.getVert() - 1);
		}
	}
	void moveRight() {
		if (pos.getHor() < table.getTableWidth()) {
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
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Piece piece;
	piece.setPos(1, 1);

	int _step = 0;
	int _select = 0;

	cout << format("{:-<19} \n", "");
	cout << format("Įveskite lentelės plotį: ");
	cin >> _select;
	table.setTableWidth(_select);
	cout << endl;
	cout << format("{:-<19} \n", "");
	cout << format("Įveskite lentelės Aukštį: ");
	cin >> _select;
	table.setTableHeight(_select);



	printTable(piece.getPos().getVert(), piece.getPos().getHor(), _step);

	while (true) {
		int _key = _getch();

		if (_key == 27) {
			break;
		}

		_step++;

		if (_key == 0 || _key == 224) {
			_key = _getch();

			switch (_key) {
				case 80: { // UP (revert)
					piece.moveUp();
				}break;
				case 72: { // DOWN (revert)
					piece.moveDown();
				}break;
				case 75: { // LEFT
					piece.moveLeft();
				}break;
				case 77: { // RIGHT
					piece.moveRight();
				}break;
			}
		}

		//cout << "Current position is: "
		//	<< piece.getPos().getVert() << " - "
		//	<< piece.getPos().getHor() << endl;
		printTable(piece.getPos().getVert(), piece.getPos().getHor(), _step);
	}
}