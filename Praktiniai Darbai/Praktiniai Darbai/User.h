#pragma once
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class SUser {
private:
	string _userName;
	char _role;
	string _userId;

public:
	SUser(const string &userName, char role, const string &userId) {
		_userName = userName;
		_role = role;
		_userId = userId;
	}

	string getUserName() {
		return this->_userName;
	}

	char getRole() {
		return this->_role;
	}

	string getUserId() {
		return this->_userId;
	}
};


class SUserDetails {
private:
	string _firstName;
	string _lastName;
	string _phoneNumber;
	string _userId;

public:
	SUserDetails(string firstName, string lastName, string phoneNumber, string userId) {
		_firstName = firstName;
		_lastName = lastName;
		_phoneNumber = phoneNumber;
		_userId = userId;
	}

	string getFirstName() {
		return this->_firstName;

	}
	string getLastName() {
		return this->_lastName;

	}
	string getPhoneNumber() {
		return this->_phoneNumber;

	}
	string getUserId() {
		return this->_userId;
	}
};