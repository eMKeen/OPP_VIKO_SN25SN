#include <string>
#include <algorithm>
#include "utils.h"
#include <iostream>
#include <format>

using namespace std;

/**
* @brief Converts all characters in a string to lowercase.
*
* Transforms each character of the provided string to its lowercase
* equivalent and returns the modified string.
*
* @param[in] text Text to be converted to lowercase.
* @return String containing the converted lowercase text.
*/
string toLower(string text) {
    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c) {
            return tolower(c);
        });

    return text;
}

/**
* @brief Waits for the user to press Enter before continuing.
*
* Clears the remaining character from the input buffer and waits
* for the user to press Enter.
*/
void wait() {
    string _wait;
    cin.ignore();
    getline(cin, _wait);
}

/**
* @brief Gets and validates a menu selection entered by the user.
*
* Reads the user's menu selection and checks whether the entered value
* is a valid integer within the specified range. If the input is invalid,
* an error message is displayed and the user is asked to enter a value again.
*
* @param[in] _select Initial variable used to store the user's selection.
* @param[in] _quantity Maximum allowed menu selection value.
* @param[in] _notNULL Minimum allowed menu selection value.
* @return Valid menu selection entered by the user.
*/
int menuSelect(int _select, int _quantity, int _notNULL) { //start _notNULL
    CFormation format(50);

    while (true) {
        while (!(cin >> _select) || _select < 0) {

            cin.clear();
            cin.ignore(INT_MAX, '\n');

            announceMessage(">> Pasirinkimas ne tinkamas, rinkites iš menių <<", "Pakartokite įvedimą", true);
        }

        if (_select >= _notNULL && _select <= _quantity) {
            return _select;
        }

        announceMessage(">> Pasirinkimas ne tinkamas, rinkites iš menių <<", "Pakartokite įvedimą", true);
    }
}

/**
* @brief Calculatesthe number of characters in a UTF-8 encoded string.
* 
* Counts UTF-8 characters by ignoring continuation bytes. This allows
* Lithuanian characters encoded using multiple byts to be counted as a single character.
* 
* @param[in] _text UTF-8 encoded text to processed.
* @return Number of characters in the text
*/
int lithuanianLetters(const string& _text) {
    int _lenght = 0;

    for (int i = 0; i < _text.length(); i++) {
        unsigned char c = _text[i];
        // Counts only the first byte of each UTF-8 characters.
        if ((c & 0b11000000) != 0b10000000) {
            _lenght++;
        }
    }
    return _lenght;
}

/**
* @brief Displays a formatted announcement message in the console.
*
* Displays the primary message and, if provided, an additional message
* centered between separator lines. The function can optionally wait
* for user input before continuing.
*
* @param[in] _text1 Primary message to be displayed.
* @param[in] _text2 Additional message to be displayed. If empty,
*                   the message is not displayed.
* @param[in] _wait If true, waits for user input before continuing.
*/

void announceMessage(const string& _text1, const string& _text2, bool _wait) {
    CFormation format(50);

    format.commonLine("", ELineType::Separator, 0);

    format.commonLine(_text1, ELineType::CenteredText, 0);

    if (!_text2.empty()) {
        format.commonLine(_text2, ELineType::CenteredText, 0);
    }
    format.commonLine("", ELineType::Separator, 0);

    if (_wait) {
        wait();
    }
}

/**
* @brief Gets login credentials from the user.
*
* Prompts the user to enter a username and password and stores
* the entered values in the provided variables.
*
* @param[in] format Reference to the CFormation object used to format
*                   the input messages.
* @param[out] _filledName Entered username.
* @param[out] _filledPassword Entered password.
*/
void enterData(CFormation& format, std::string& _filledName, std::string& _filledPassword)
{
    format.commonLine("", ELineType::Separator, 0);
    format.commonLine("Įveskite prisijungimo varda: ", ELineType::Input, 0);

    getline(cin, _filledName);

    format.commonLine("", ELineType::Separator, 0);
    format.commonLine("Įveskite slaptažodį: ", ELineType::Input, 0);

    getline(cin, _filledPassword);
}