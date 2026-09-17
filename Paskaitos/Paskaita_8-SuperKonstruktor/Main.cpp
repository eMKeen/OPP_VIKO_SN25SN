#include <string>
#include <iostream>
#include <windows.h>

using namespace std;


class CBaseAccount {
private:
	string name;
	string accountNumber;
	double balance = 100;
public:
	CBaseAccount() {};
	CBaseAccount(string name, double balance) : name(name), balance(balance) {}

	string getName() {
		return this->name;
	}
};



class CCardAccount : public CBaseAccount {
private:	
	string cardNumber;

public:
	CCardAccount(string cardNumber) : cardNumber(cardNumber) {}

	CCardAccount(string name, double balance, string cardNumber) : CBaseAccount(name, balance),
		cardNumber(cardNumber) {}
};




int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	CCardAccount cardAccount = CCardAccount("CardACC # 1", 300, "100001");

	cout << "Name: " << cardAccount.getName() << endl;


}