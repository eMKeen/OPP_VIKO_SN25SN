#pragma once

#include <string>
#include <fstream>
#include "user.h"
#include "utils.h"

using namespace std;

/**
* @class CLoginData
* @brief Stores and manages user authentication data.
*
* The class stores user account information retrieved from the account file
* and provides methods required during authentication.
*
* _userName - User account name.
* _password - User account password.
* _userId - Unique user identification number.
* _role - User role in the system.
* _userStatus - Current status of the user account.
* _remainLoginAttempts - Number of remaining login attempts.
* _attemptsPosition - Position of the login attempts value in the file.
* _statusPosition - Position of the user status value in the file.
*
* @note The user's password is used only for authentication
*       and is not passed further into the system.
*/
class CLoginData {
private:
    string _userName;
    string _password;
    string _userId;
    char _role{ 0 };
    EUserStatus _userStatus{ EUserStatus::Error };
    int _remainLoginAttempts{ 0 };

    streampos _attemptsPosition;
    streampos _statusPosition;

public:
    /**
    * @brief Reads user account data from a file.
    *
    * Reads the username, password, user ID, role, account status,
    * and number of remaining login attempts.
    *
    * @param[in] file File stream containing the user account data.
    * @return true if the user data was read successfully; otherwise false.
    */
    bool getData(fstream& file) {

        // Reads the username.
        if (!getline(file, _userName, ';') || _userName.empty())
            return false;

        // Reads the password.
        getline(file, _password, ';');

        // Reads the unique user ID.
        if (!getline(file, _userId, ';') || _userId.empty())
            return false;

        // Reads the user role.
        string lookUpRole;

        if (!getline(file, lookUpRole, ';') || lookUpRole.empty())
            return false;

        _role = lookUpRole[0];

        // Saves the position of the account status in the file.
        _statusPosition = file.tellg();

        // Reads the account status.
        string status;
        getline(file, status, ';');

        if (status == "a")
            _userStatus = EUserStatus::Active;
        else if (status == "i")
            _userStatus = EUserStatus::Inactive;
        else if (status == "b")
            _userStatus = EUserStatus::Blocked;
        else
            _userStatus = EUserStatus::Error;

        // Saves the position of the remaining login attempts.
        _attemptsPosition = file.tellg();

        // Reads the number of remaining login attempts.
        string attempts;

        if (!getline(file, attempts) || attempts.empty())
            return false;

        _remainLoginAttempts = stoi(attempts);

        // An account with no remaining attempts is blocked.
        if (_remainLoginAttempts == 0)
            _userStatus = EUserStatus::Blocked;

        return true;
    }

    /**
    * @brief Processes a failed login attempt.
    *
    * Decreases the number of remaining login attempts by one
    * and updates the value in the account file.
    *
    * If no attempts remain, the account is blocked and its
    * status in the file is changed to 'b'.
    *
    * @param[in,out] file Account file stream.
    */
    void failedLoginAttempt(fstream& file) {

        if (_remainLoginAttempts > 0)
            _remainLoginAttempts--;

        file.clear();
        file.seekp(_attemptsPosition);
        file << _remainLoginAttempts;

        if (_remainLoginAttempts == 0) {

            _userStatus = EUserStatus::Blocked;

            file.seekp(_statusPosition);
            file << 'b';
        }

        file.flush();
    }


    /**
    * @brief Processes a successful login attempt.
    *
    * Resets the failed login attempt counter.
    *
    * @param[in,out] file Account file stream.
    */
    void successfulLoginAttempt(fstream& file) {

        _remainLoginAttempts = 4;

        file.clear();
        file.seekp(_attemptsPosition);
        file << _remainLoginAttempts;
        file.flush();
    }

    /**
    * @brief Gets the username.
    *
    * @return User account name.
    */
    string getUserName() const {
        return _userName;
    }

    /**
    * @brief Gets the password.
    *
    * @return User account password.
    */
    string getPassword() const {
        return _password;
    }

    /**
    * @brief Gets the user ID.
    *
    * @return Unique user identification number.
    */
    string getUserId() const {
        return _userId;
    }

    /**
    * @brief Gets the user role.
    *
    * @return User role.
    */
    char getRole() const {
        return _role;
    }

    /**
    * @brief Gets the account status.
    *
    * @return Current user account status.
    */
    EUserStatus getUserStatus() const {
        return _userStatus;
    }

    /**
    * @brief Gets the number of remaining login attempts.
    *
    * @return Number of remaining login attempts.
    */
    int getRemainLoginAttempts() const {
        return _remainLoginAttempts;
    }
};


bool login(CUser& user);

void enterData(CFormation& format, string& filledName, string& filledPassword);