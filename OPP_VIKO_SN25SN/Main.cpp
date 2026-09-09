#include <iostream>
#include <windows.h>

using namespace std;

int task1();
int task2();

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	cout << "Pasirkinti uzduoti:" << endl;
	cout << "Uzduotis 1" << endl;
	cout << "Uzduotis 2" << endl;
	int _select;
	cin >> _select;

	switch(_select) {
	case 1:	{ 
		return task1();
	} break;
	case 2:	{ 
		return task2();
	} break;
	default: {
		cout << "Ivestis neteisinga" << endl;
		return 0;
	}
	}
}