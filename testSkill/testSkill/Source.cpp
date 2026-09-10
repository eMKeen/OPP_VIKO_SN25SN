#include <iostream>

using namespace std;

class Person abstract {
protected:
	string firstName;
	string lastName;
	int age;
public:
	void setName(string firstName) {
		this->firstName = firstName;
	}
	string getName() {
		return this->firstName;
	}
};

class Teacher : public Person {
private:
	string subject;
};

class Student : public Person{
	string group;
	string facult;
};

int main() {

	

}