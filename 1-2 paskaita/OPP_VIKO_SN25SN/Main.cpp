#include <iostream>
#include <windows.h>

using namespace std;

int task1();
int task2();

void summ(int& _summ, int  _randomNumbers[19]);

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	cout << "Pasirkinti uzduotį:" << endl;
	cout << "Užduotis - 1" << endl;
	cout << "Užduotis - 2" << endl;
	cout << "Užbaigti - 0" << endl;
	int _select;
	cin >> _select;

	switch(_select) {
	case 0: { 
		return 0;
	}
	case 1:	{ 
		return task1();
	} break;
	case 2:	{ 
		return task2();
	} break;
	default: {
		cout << "Įvestis neteisinga" << endl << endl;
		return main();
	}break;
	}
}