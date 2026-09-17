#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

namespace mano {
	int i = 0;
}

namespace tavo {
	int i = 0;
}



//Statinio nario classė
class StaticMemberClass {
private:
	static int staticMemberCounter;
	
public:
	StaticMemberClass() {
		staticMemberCounter++;
	}
	int getStaticMemberClass() {
		return staticMemberCounter;
	}

};


//Statinio nario aprašymas
int StaticMemberClass::staticMemberCounter = 0;


// variable life cycle
void contNonStatic() {
	int nonStaticCounter = 0;

	cout << "Non static counter: " << ++nonStaticCounter << endl;
}


void countStatic() {
	static int staticCounter = 0;

	cout << "Static counter: " << ++staticCounter << endl;

}

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	tavo::i = 8;
	mano::i = 10;

	contNonStatic();
	contNonStatic();
	contNonStatic();

	countStatic();
	countStatic();
	countStatic();

	StaticMemberClass obj1;
	cout << "Current counter value: " << obj1.getStaticMemberClass() << endl;
	StaticMemberClass obj2;
	cout << "Current counter value: " << obj2.getStaticMemberClass() << endl;
	StaticMemberClass obj3;
	cout << "Current counter value: " << obj3.getStaticMemberClass() << endl;
	StaticMemberClass obj4;
	cout << "Current counter value: " << obj4.getStaticMemberClass() << endl;


}