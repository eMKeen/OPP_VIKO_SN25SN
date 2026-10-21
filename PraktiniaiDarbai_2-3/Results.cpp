/**
* @file Results.cpp
* @brief Implements player validation, scoring and result storage.
*
* Contains scoreboard validation, semicolon-separated file handling
* and UTF-8-aware result-table display.
*/
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <system_error>
#include "Results.h"

using namespace std;

//>-------------------Player information----------------
bool CPlayer::setUserName(const string& _value) {
    if (_value.empty() || CFormation::lithuanianLetters(_value) > 24 ||
        _value.find_first_not_of(' ') == string::npos || _value.find(';') != string::npos)
        return false;

    for (unsigned char _letter : _value) {
        if (_letter < 32 || _letter == 127)
            return false;
    }

    _userName = _value;
    return true;
}

string CPlayer::getUserName() const {
    return _userName;
}

//>-------------------Score calculation-----------------
CScore& CScore::operator+=(int _addedPoints) {
    if (_addedPoints >= 0 && _addedPoints <= 10000 && _points <= 10000 - _addedPoints)
        _points += _addedPoints;

    return *this;
}

int CScore::getPoints() const {
    return _points;
}

int CScore::calculatePoints(bool _correct, int _weight, double _seconds) const {
    if (!_correct || _weight < 1 || _weight > 2 || !isfinite(_seconds) || _seconds < 0)
        return 0;

    if (_seconds < 1)
        _seconds = 1;

    return 10 * _weight + static_cast<int>(90 * _weight / _seconds);
}

//>-----------------Text file storage-----------------
CFileStorage::CFileStorage(const string& _filePath) : _path(_filePath) {
}

bool CFileStorage::appendLine(const string& _line) const {
    ofstream _file(_path, ios::app);
    if (!_file)
        return false;

    _file << _line << endl;
    return static_cast<bool>(_file);
}

bool CFileStorage::readLines(vector<string>& _lines) const {
    _lines.clear();
    ifstream _file(_path);

    if (!_file) {
        error_code _error;
        bool _exists = filesystem::exists(_path, _error);
        return !_exists && !_error;
    }

    string _line;
    while (getline(_file, _line))
        _lines.push_back(_line);

    return !_file.bad();
}

//>------------------Scoreboard validation and storage-----------------
CScoreBoard::CScoreBoard(const string& _path) : CFileStorage(_path) {
}

bool CScoreBoard::isValid(const CResult& _result) const {
    CPlayer _player;
    return _player.setUserName(_result._userName) && //Check if the username is valid
        _result._total >= 10 && // At least 10 qwestions
        _result._total <= 50 && // No more than 50 qwestions
        _result._total % 10 == 0 && // Question count must be a multiple of 10
        _result._correct >= 0 && // Correct answer count cannot be negative
        _result._correct <= _result._total && // Correct answers cannot exceed total qwuestions
        isfinite(_result._seconds) && // Time cannot be infinity or NaN
        _result._seconds >= 0 && // Time cannot be negative
        _result._points >= 0 && // Points cannot be negative
        _result._points <= _result._correct * 200; // At most 200 points per correct answer
}

bool CScoreBoard::hasHigherScore(const CResult& _first, const CResult& _second) {
    return _first._points > _second._points;
}

bool CScoreBoard::saveResult(const CResult& _result) const {
    if (!isValid(_result))
        return false;

    ostringstream _line;
    _line.imbue(locale::classic()); // Use a dot as the decimal separator
    _line << _result._userName << ';' // Write the usernam
        << _result._correct << ';' // Write the correct answer count
        << _result._total << ';' // Write the total question count
        << fixed << setprecision(3) << _result._seconds << ';' // Write the with 3 desimal places
        << _result._points; //Write the total points

    return appendLine(_line.str());
}

bool CScoreBoard::getResults(vector<CResult>& _results, int& _skipped) const {
    _results.clear();
    _skipped = 0;
    vector<string> _lines;

    if (!readLines(_lines))
        return false;

    for (const string& _line : _lines) {
        CResult _result;
        istringstream _input(_line);
        _input.imbue(locale::classic());
        char _separator1{ 0 }, _separator2{ 0 }, _separator3{ 0 };

        bool _valid = static_cast<bool>(getline(_input, _result._userName, ';') &&
            (_input 
                >> _result._correct 
                >> _separator1 
                >> _result._total 
                >> _separator2 
                >> _result._seconds 
                >> _separator3 
                >> _result._points
                ));
        _input >> ws;

        if (_valid && _input.eof() && _separator1 == ';' && _separator2 == ';' &&
            _separator3 == ';' && isValid(_result))
            _results.push_back(_result);
        else
            _skipped++;
    }

    stable_sort(_results.begin(), _results.end(), hasHigherScore);
    return true;
}

//>------------------Scoreboard display------------------
void CScoreBoard::displayResults(const vector<CResult>& _results, const CFormation& _format) const {
    system("cls");

    vector<string> _lines{
        "REZULTATŲ LENTELĖ",
        _format.fitText("Vardas", 25) + 
        _format.fitText("Teisingi/Viso", 15) +
        _format.fitText("Laikas (s)", 14) + 
        "Taškai"
    };

    for (const CResult& _result : _results) {
        ostringstream _time;
        _time << fixed << setprecision(2) << _result._seconds;

        _lines.push_back(_format.fitText(_result._userName, 25) 
            + _format.fitText(to_string(_result._correct) + "/" + to_string(_result._total), 15) 
            + _format.fitText(_time.str(), 14) + to_string(_result._points));
    }

    if (_results.empty())
        _lines.push_back("Rezultatų dar nėra.");

    _format.displayBox(_lines);
}
