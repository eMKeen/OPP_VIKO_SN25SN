#include <string>
#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;


class CBaseAccount {
public:
	CBaseAccount() {
		cout << "Call to base class countructor" << endl;
	}
	~CBaseAccount() {
		cout << "Call to base class destructor" << endl;
	}
};

class CBankAccount : CBaseAccount {
private:
	double dBalance;

public:
	//Constructor
	CBankAccount() {
		this->dBalance = 100;
		cout << "Call to inharitance class countructor" << endl;
	}

	/* Another metod constructor with param
	CBankAccount() : dBalance(100) {}
	*/

	//Custom copy constructor
	CBankAccount(const CBankAccount &initial) {
		cout << "Call to custom copy constructor" << endl;
		this->dBalance = initial.dBalance * 1.5;
	}

	CBankAccount(double initialBalance) : dBalance(initialBalance) {}

	//CBankAccount(int newBalance) : dBalance(newBalance) {}

	//Destructor
	~CBankAccount() {
		cout << "Call to inharitance class destructor" << endl;
	}

	//GET // SET
	void setBalance(double dBalance) {
		this->dBalance = dBalance;
	}
	double getBalance() {
		return this->dBalance;
	}
};


int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


	CBankAccount bankAcc1;
	CBankAccount bankAcc2 = CBankAccount(200);
	CBankAccount bankAcc3 = CBankAccount(300);
	CBankAccount bankAcc4 = CBankAccount(400.25);
	CBankAccount bankAcc5 = CBankAccount(bankAcc3);
	

	cout << "Jūsų balansas : " << bankAcc1.getBalance() << endl;
	cout << "Jūsų balansas : " << bankAcc2.getBalance() << endl;
	cout << "Jūsų balansas : " << bankAcc3.getBalance() << endl;
	cout << "Jūsų balansas : " << bankAcc4.getBalance() << endl;
	cout << "Jūsų balansas 5 ACC : " << bankAcc5.getBalance() << endl;

}