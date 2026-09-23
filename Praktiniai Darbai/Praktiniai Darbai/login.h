#pragma once
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
* @struct SLoginData
* @brief Stores user login and account data retrieved from a file or database.
*
* Contains the user account information required for authentication.
* The data is read from a file by the getData() funtion.
*
* @var _userName - user account name.
* @var _password - account password.
* @var _userId - Unique user identification number.
* @var _role - User role in the system.
* @var _userStatus - Current status of the user account.
* @var _remainLoginAttempts - Number of remaining login attempts.
*
* @note the user's account password is used only for authentication
*       and is not passed futher in the system
*/

struct SLoginData {
    string _userName;
    string _password;
    string _userId;
    char _role{ 0 };
    EUserStatus _userStatus{ EUserStatus::Error };
    int _remainLoginAttempts{ 0 };

    /**
    * @brief Reads user account data from a file.
    *
    * Reads the username, password, user ID, role, account status,
    * and number of remaining login attempts from the input file.
    *
    * @param[in] _inFile Input file stream containing  the user account data.
    * @return true if the user data was read successfully; otetherwise false.
    */
    bool getData(ifstream& _inFile) {

        /// Reads the username.
        if (!getline(_inFile, _userName, ';') || _userName.empty())
            return false;

        /// Reads the password.
        /// @note Password will be validated during authentication.
        getline(_inFile, _password, ';');

        /// Reads the unique user's ID number.
        if (!getline(_inFile, _userId, ';') || _userId.empty())
            return false;

        /// Reads the role.
        // Temporary string used to read the user role from the file.
        string _lookUpRole;
        if (!getline(_inFile, _lookUpRole, ';')
            || _lookUpRole.empty())
            return false;

        // Only the first character is used because the role is stored as a char.
        _role = _lookUpRole[0];

        /// Reads the status.
        // Temporary string used to read the user role from the file.
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

        /// Reads the number of login attepmpts.
        string _attempts;
        if (!getline(_inFile, _attempts, ';') || _attempts.empty())
            return false;

        // Converts the string to int because _remainLoginAttempts is stored as an integer.
        _remainLoginAttempts = stoi(_attempts);

        return true;
    }
};


bool login();