/**
* @file Utils.cpp
* @brief Implements console formatting, input handling and timing.
*
* Provides UTF-8 character counting, table alignment, input validation,
* continuation messages and monotonic time measurement.
*/
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Utils.h"

using namespace std;

//>--------------Console formatting--------------------
CFormation::CFormation(int _length) {
    if (_length > 0)
        _lineLength = _length;
}

int CFormation::lithuanianLetters(const string& _text) {
    int _length{ 0 };

    // Counts only the first byte of each UTF-8 character
    for (unsigned char _letter : _text) {
        if ((_letter & 0b11000000) != 0b10000000)
            _length++;
    }

    return _length;
}

// Adjusts the line width for Lithuanian UTF-8 characters.
string CFormation::fitText(const string& _text, int _width) const {
    int _spaces = _width - lithuanianLetters(_text);
    if (_spaces < 0)
        _spaces = 0;

    return _text + string(_spaces, ' ');
}

void CFormation::displayBox(const vector<string>& _lines) const {
    int _width = _lineLength;
    for (const string& _line : _lines)
        _width = max(_width, lithuanianLetters(_line));

    string _border = "+" + string(_width + 2, '-') + "+";
    cout << _border << endl;

    for (const string& _line : _lines)
        cout << "| " << fitText(_line, _width) << " |" << endl;

    cout << _border << endl;
}

//>-------------------Input and messages-------------------
bool CFormation::getLine(const string& _prompt, string& _value) const {
    cout << _prompt << flush;
    return static_cast<bool>(getline(cin, _value));
}

bool CFormation::getInteger(const string& _prompt, int _minValue, int _maxValue, int& _value) const {
    string _text;

    while (getLine(_prompt, _text)) {
        istringstream _input(_text);
        int _number { 0 };

        if (_input >> _number) {
            _input >> ws;
            if (_input.eof() && _number >= _minValue && _number <= _maxValue) {
                _value = _number;
                return true;
            }
        }

        cout << "Įveskite sveikąjį skaičių nuo " << _minValue << " iki " << _maxValue << "." << endl;
    }

    return false;
}

bool CFormation::wait() const {
    string _wait;
    cout << endl;
    cout << "Norėdami tęsti, spauskite Enter..." << flush;

    if (!getline(cin, _wait))
        return false;

    system("cls");
    return true;
}

bool CFormation::announceMessage(const string& _text1, const string& _text2) const {
    vector<string> _lines{ _text1 };
    if (!_text2.empty())
        _lines.push_back(_text2);

    displayBox(_lines);
    return wait();
}

//>-----------------Question timer------------------
void CTimer::reset() {
    _start = chrono::steady_clock::now();
}

double CTimer::getSeconds() const {
    return chrono::duration<double>(chrono::steady_clock::now() - _start).count();
}
