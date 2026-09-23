#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <format>
#include "login.h"
#include "utils.h"

using namespace std;

bool login() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

    SLoginData loginData;
    CFormation format(50);

    string _userName;
    string _password;
    int _select = 0;

    format.commonLine("", ELineType::Separator, 0);
    format.commonLine("Įveskite prisijungimo varda: ", ELineType::CenteredText, 0);

    return false;
}