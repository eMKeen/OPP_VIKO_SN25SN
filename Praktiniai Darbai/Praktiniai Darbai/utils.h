#pragma once
#include <string>

using namespace std;

string toLower(string text);

void wait();

int menuSelect(int _select, int _quantity, int _notNULL);

void commonLine(int _lineLenght, string _text, int _select, int _menuSelect);

int lithuanianLetters(const string& txt);