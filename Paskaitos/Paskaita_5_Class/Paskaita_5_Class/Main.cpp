#include <iostream>
#include <string>

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
	void setLastName(string lastName) {
		this->lastName = lastName;
	}
	string getLastName() {
		return this->lastName;
	}
	void setAge(int age) {
		this->age = age;
	}
	int getAge() {
		return this->age;
	}
};


class Teacher : public Person {
private:
	string subject;

public:
	class Room {
	private:
		int roomNum;
	};

	int setNum() {

	}
};


class Student : public Person {
private:
	int age;
	string group;
	string facult;
};

int main() {

	Student student;
	Teacher teacher;

	student.setName("Vardas1");
	teacher.setName("D_vardas1");

	cout << student.getName() << endl;

	cout << teacher.getName() << endl;

	return 0;

	Teacher::Room room;
}