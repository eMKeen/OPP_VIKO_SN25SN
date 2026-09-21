#include <string>
#include <algorithm>
#include "utils.h"
#include <iostream>
#include <format>

using namespace std;

string toLower(string text) {
    transform(text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c) {
            return tolower(c);
        });

    return text;
}

void wait() {
    string _wait;
    cin.ignore();
    getline(cin, _wait);
}

int menuSelect(int _select, int _quantity, int _notNULL) { //start _notNULL
    while (true) {
        while (!(cin >> _select) || _select < 0) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "------------------------------------------------" << endl;
            cout << ">> Pasirinkimas ne tinkamas, rinkites iš menių<<" << endl;
            cout << ">>Pakartokite įvedimą" << endl;
        }

        if (_select >= _notNULL && _select <= _quantity) {
            return _select;
        }
        cout << "------------------------------------------------" << endl;
        cout << ">> Pasirinkimas ne tinkamas, rinkites iš menių<<" << endl;
        cout << ">>Pakartokite įvedimą" << endl;
    }
}

void commonLine(int _lineLenght, string _text, int _select, int _menuSelect) {
    int _textLenght = _text.length();
    int _lineCorection = _text.length() - lithuanianLetters(_text);
    switch (_select) {
    default: {
        cout << format("{:-<{}}", _text, _lineLenght) << endl; //Brukšnis
    } break;
    case 1: {
        cout << format("{:<{}}", _text, _lineLenght) << endl; //Tiesig tekstas
    }break;
    case 2: {
        cout << format("{:<{}}{:<{}}", "", (_lineLenght - _textLenght) / 2, _text, _textLenght) << endl; //Tekstas centruotas
    }break;
    case 3: {
        string _menuText = " - " + to_string(_menuSelect);
        cout << format("{:<{}}{:>5}", _text, _lineLenght + _lineCorection - 5, _menuText) << endl; // Menu select
    }break;
    case 4: {
        cout << format("{:<{}}{:>3}", _text, _lineLenght + _lineCorection - 3, " - "); // Menu select
    }break;

    }
}

int lithuanianLetters(const string& txt) {
    int _lenght = 0;

    for (int i = 0; i < txt.length(); i++) {
        unsigned char c = txt[i];
        if ((c & 0b11000000) != 0b10000000) {
            _lenght++;
        }
    }
    return _lenght;
}