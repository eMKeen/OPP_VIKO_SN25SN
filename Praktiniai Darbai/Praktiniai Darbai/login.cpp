#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "login.h"
#include "utils.h"

using namespace std;

/**
* @brief Authenticates a user using account data stored in a file.
*
* Prompts the user to enter a username and password and searches for
* the corresponding account in the account file. The function checks
* the account status and validates the entered password.
*
* Failed login attempts decrease the number of remaining login attempts.
* If no attempts remain, the user account is blocked. After successful
* authentication, the authenticated account data is stored in the
* provided CUser object.
*
* @param[out] user User object that receives the authenticated account data.
* @return true if authentication is successful; otherwise false.
* 
* @note Information about failed login attempts is stored in the account file.
*     If the program is closed and restarted, the remaining login attempts
*     are not reset to the maximum value. The counter is reset only after
*     a successful login.
*/

bool login(CUser& user) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    CFormation format(50);

    string _filledName;
    string _filledPassword;

    fstream _inFile("accountInformation", ios::in | ios::out);

    if (!_inFile) {announceMessage("Nepavyko Atidaryti","",true);
        return false;
    }


    while (true) {

        // User enters login information.
        enterData(format, _filledName, _filledPassword);

        // Starts searching from the beginning of the file.
        _inFile.clear();
        _inFile.seekg(0);

        CLoginData loginData;


        while (loginData.getData(_inFile)) {

            // Searches for the entered username.
            if (loginData.getUserName() == _filledName) {

                // Checks whether the account is blocked.
                if (loginData.getUserStatus() == EUserStatus::Blocked) {
                    announceMessage("Naudotojas yra užblokuotas","",true);
                    return false;
                }

                // Checks the password.
                if (loginData.getPassword() != _filledPassword) {
                    loginData.failedLoginAttempt(_inFile);

                    if (loginData.getRemainLoginAttempts() > 0) {
                        cout << "Bandymas nesėkmingas" << endl;
                        cout << "Liko bandymų: "
                            << loginData.getRemainLoginAttempts()
                            << endl;
                        break;
                    }
                    else {
                        announceMessage("Naudotojas yra užblokuotas","",true);
                        return false;
                    }
                }

                // Successful authentication.
                loginData.successfulLoginAttempt(_inFile);

                user.setUserId(loginData.getUserId());
                user.setUserName(loginData.getUserName());
                user.setRole(loginData.getRole());
                user.setUserStatus(loginData.getUserStatus());

                announceMessage("Pavyko prisijungti","");
                return true;
            }
        }
    }
    return false;
}