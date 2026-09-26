#pragma once

#include <string>

using namespace std;

/**
* @enum EUserStatus
* @brief Defines the current status of a user account in the system.
*
* Active   - The user account is active and the user can log in.
* Inactive - The user account is inactive and login is not allowed.
* Blocked  - The user account is blocked due to failed login attempts
*            or administrative action.
* Error    - The user account status is invalid or could not be determined.
*/
enum class EUserStatus {
    Active,
    Inactive,
    Blocked,
    Error
};

/**
* @class CUser
* @brief Represents an authenticated user in the system.
*
* _userName   - User account name.
* _role       - User role in the system.
* _userId     - Unique user identification number.
* _userStatus - Current status of the user account.
*/
class CUser {
private:
    string _userName;
    char _role{ ' ' };
    string _userId;
    EUserStatus _userStatus{ EUserStatus::Error };

public:

    /**
    * @brief Creates an empty user object.
    */
    CUser() = default;

    /**
    * @brief Creates a user object.
    *
    * @param[in] userName - User account name.
    * @param[in] role - User role in the system.
    * @param[in] userId - Unique user identification number.
    * @param[in] userStatus - Current status of the user account.
    */
    CUser(
        const string& userName,
        char role,
        const string& userId,
        EUserStatus userStatus
    ) 
    {
        _userName = userName;
        _role = role;
        _userId = userId;
        _userStatus = userStatus;
    }

    /**
    * @brief Sets the username.
    * 
    * @param[in] userName Username to be assigned to the user.
    */
    void setUserName(const string& userName) {
        _userName = userName;
    }

    /**
    * @brief Gets the username.
    *
    * @return Username of the user.
    */
    string getUserName() const {
        return _userName;
    }

    /**
    * @brief Sets the user role.
    *
    * @param[in] role Role to be assigned to the user.
    */  
    void setRole(char role) {
        _role = role;
    }

    /**
    * @brief Gets the user role.
    *
    * @return Role of the user.
    */
    char getRole() const {
        return _role;
    }

    /**
    * @brief Sets the unique user identification number.
    *
    * @param[in] userId Unique idenfitication number to be assigned to the user.
    */
    void setUserId(const string& userId) {
        _userId = userId;
    }

    /**
    * @brief Gets the unique user identification number.
    *
    * @return Unique idenfitication number of the user.
    */
    string getUserId() const {
        return _userId;
    }

    /**
    * @brief Sets the user account status.
    *
    * @param[in] userStatus Status to be assigned to the user account.
    */
    void setUserStatus(EUserStatus userStatus) {
        _userStatus = userStatus;
    }

    /**
    * @brief Gets the user account status.
    *
    * @return Current status of the user account.
    */
    EUserStatus getUserStatus() const {
        return _userStatus;
    }
};


/**
* @class CUserDetails
* @brief Stores additional information about a user.
*
* The information is stored in a file and may be stored in a database
* in the future. User details are linked to a user by the user ID.
*
* _firstName   - User's first name.
* _lastName    - User's last name.
* _phoneNumber - User's phone number.
* _userId      - Unique user identification number.
*/
class CUserDetails : public CUser {
private:
    string _firstName;
    string _lastName;
    string _phoneNumber;

public:

    /**
    * @brief Creates an extended user object with additional personal information.
    *
    * Initializes the base CUser class with account information and stores
    * additional personal information about the user.
    *
    * @param[in] userName User account name.
    * @param[in] role User role in the system.
    * @param[in] userId Unique user identification number.
    * @param[in] userStatus Current status of the user account.
    * @param[in] firstName User's first name.
    * @param[in] lastName User's last name.
    * @param[in] phoneNumber User's phone number.
    */
    CUserDetails(
        const string& userName,
        char role,
        const string& userId,
        EUserStatus userStatus,
        const string& firstName,
        const string& lastName,
        const string& phoneNumber
    )
        : CUser(userName, role, userId, userStatus)
    {
        _firstName = firstName;
        _lastName = lastName;
        _phoneNumber = phoneNumber;
    }

    /**
    * @brief Gets the user's first name.
    *
    * @return User's first name.
    */
    string getFirstName() const {
        return _firstName;
    }

    /**
    * @brief Gets the user's last name.
    *
    * @return User's last name.
    */
    string getLastName() const {
        return _lastName;
    }

    /**
    * @brief Gets the user's phone number.
    *
    * @return User's phone number.
    */
    string getPhoneNumber() const {
        return _phoneNumber;
    }
};