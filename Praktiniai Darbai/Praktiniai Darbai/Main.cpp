#include <iostream>
#include <string>
#include <windows.h>
#include "login.h"
#include "utils.h"

using namespace std;


int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	login();

	wait();
	return 0;
}