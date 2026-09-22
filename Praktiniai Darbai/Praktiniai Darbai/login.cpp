#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <format>
#include "login.h"
#include "utils.h"
#include "user.h"

using namespace std;

/**
* @struct LoginData
* @brief Stores user login and account data retrieved from a file or database.
*/

struct LoginData {
    string _userName;
    string _password;
    string _userId;
    char _role{ 0 };
    EUserStatus _userStatus{ EUserStatus::Error };
    int _remainLoginAttempts{ 0 };

    bool getData(ifstream& _inFile) {
        if (!getline(_inFile, _userName, ';'))
            return false;
        getline(_inFile, _password, ';');
        getline(_inFile, _userId, ';');

        string _lookUpRole;
        getline(_inFile, _lookUpRole, ';');
        if (_lookUpRole.empty())
            return false;

        _role = _lookUpRole[0];

        string _status;
        getline(_inFile, _status, ';');

        if (_status == "Active")
            _userStatus = EUserStatus::Active;
        else if (_status == "Inactive")
            _userStatus = EUserStatus::Inactive;
        else if (_status == "Blocked")
            _userStatus = EUserStatus::Blocked;
        else 
            _userStatus = EUserStatus::Error;

        string _attempts;
        getline(_inFile, _attempts, ';');
        _remainLoginAttempts = stoi(_attempts);
        
        return true;
    }
};


bool login() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

    LoginData loginData;

}