#include <string>
#include <iostream>
#include "Paskaita_3-4.h"
#include <cstdlib> //Need for rang() and srand()
#include <ctime> //Need for time()


using namespace std;

struct sStudent
{
	int id;
	string name;
	string lastName;
	string group;
};


int main() {

	srand(time(0));

	int _randomNum = (rand() % 6) + 1;
	sStudent foundStudent;
	bool found = false;


	sStudent _student[] = {
	1, "Vardas1", "Pavardenis1", "IS25SN",
	2, "Vardas2", "Pavardenis2", "IS25SN",
	3, "Vardas3", "Pavardenis3", "IS25SN",
	4, "Vardas4", "Pavardenis4", "IS25SN",
	5, "Vardas5", "Pavardenis5", "IS25SN",
	6, "Vardas6", "Pavardenis6", "IS25SN"
	};

	for (int i = 0; i < size(_student); i++) {
		displayStudents(_student[i]);
	}

	for (int i = 0; i < size(_student); i++) {
		if (_student[i].id == _randomNum) {
			foundStudent = _student[i];
			found = true;
			break;
		}
	}

	if (found) {
		cout << "Studentas su ID " << foundStudent.id << endl;
		displayStudents(foundStudent);
	}
	else {
		cout << "Studentas su ID " << _randomNum << " nerastas!" << endl;
	}

	wait();
	
}

void wait()
{
	string _wait;
	cin.ignore();
	getline(cin, _wait);
}


void displayStudents(struct sStudent _student)
{
	cout << "Student id: " << _student.id << " | ";
	cout << "Student Name: " << _student.name << " | ";
	cout << "Student Pavarde: " << _student.lastName << " | ";
	cout << "Student Grupe: " << _student.group << endl;
}
