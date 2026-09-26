#include <iostream>
#include <string>
#include <windows.h>
#include "login.h"
#include "utils.h"

using namespace std;


int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	CUser user;

	login(user);

	string _userStatus;
    switch (user.getUserStatus()) {
    case EUserStatus::Active:
        _userStatus = "Active";
		break;

    case EUserStatus::Inactive:
        _userStatus = "Inactive";
		break;

    case EUserStatus::Blocked:
		_userStatus = "Blocked";
		break;

    default:
		_userStatus = "Error";
		break;
    }

	CFormation _format(50);
	_format.commonLine("", ELineType::Separator, 0);
	_format.commonLine("Objektas User gauna :", ELineType::CenteredText, 0);
	
	cout << "User: " << user.getUserName() << endl
		<< "Role: " << user.getRole() << endl
		<< "User ID: " << user.getUserId() <<endl 
		<< "Statusas: " << _userStatus << endl;
	_format.commonLine("", ELineType::Separator, 0);

	wait();

	return 0;
}