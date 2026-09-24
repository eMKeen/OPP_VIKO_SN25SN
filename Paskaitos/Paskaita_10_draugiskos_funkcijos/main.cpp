#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

class CMultiplier;

class CCordinates {
private:
    int x, y;

public:
    CCordinates(int x, int y) {
        this->x = x;
        this->y = y;
    }

    friend int calculateDiff(CCordinates AB);

    int multiply(CMultiplier AB);
};


class CMultiplier {
private:
    int multiplyX, multiplyY;

public:
    CMultiplier(int x, int y) {
        this->multiplyX = x;
        this->multiplyY = y;
    }

    friend int CCordinates::multiply(CMultiplier AB);
};


int CCordinates::multiply(CMultiplier AB) {
    return this->x * AB.multiplyX * this->y * AB.multiplyY;
}


int calculateDiff(CCordinates AB) {
    return AB.x - AB.y;
}


int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


	CCordinates coord(3, 5);

	cout << "Kordinatės yra: " << calculateDiff(coord) << endl;

    CMultiplier multiplier(2, 4);

    cout << "Daugyba: " << coord.multiply(multiplier) << endl;

}