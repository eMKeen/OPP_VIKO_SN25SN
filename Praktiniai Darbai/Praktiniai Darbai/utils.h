#pragma once
#include <string>
#include <format>
#include <iostream>

using namespace std;

string toLower(string text);

void wait();

int menuSelect(int _select, int _quantity, int _notNULL);

int lithuanianLetters(const string& txt);

/**
* @enum ELineType
* @brief Defines the available line formatting types.
*
* Specifies how a line of text is formatted and displayed
* by the CFormation class.
*
* Separator - Displays a separator line and is used as the default line type.
* Text - Displays plain text.
* CenteredText - Displays centered text.
* MenuText - Displays text with a menu selection number.
* Input - Displays text followed by an input indicator.
*/
enum class ELineType {
    Separator,
    Text,
    CenteredText,
    MenuText,
    Input
};
/**
* @class CFormation
* @brief Provides methods for formatting and displaying text in the console.
*
* The class defines the line length and provides methods for displaying
* text using different formatting options, such as plain text, centered
* text, separator lines, and menu elements.
*/

class CFormation {
private:
    int _lineLength;

public:
    CFormation(int lineLength) : _lineLength(lineLength) {};

    void commonLine(string _text, ELineType _lineType, int _menuSelect) {
        int _textLength = _text.length();
        int _lineCorection = _text.length() - lithuanianLetters(_text);
        switch (_lineType) {
        default: {
            cout << format("{:-<{}}", _text, _lineLength) << endl;
        } break;
        case ELineType::Text: {
            cout << format("{:<{}}", _text, _lineLength) << endl;
        }break;
        case ELineType::CenteredText: {
            cout << format("{:<{}}{:<{}}", "", (_lineLength - _textLength) / 2, _text, _textLength) << endl;
        }break;
        case ELineType::MenuText: {
            string _menuText = " - " + to_string(_menuSelect);
            cout << format("{:<{}}{:>5}", _text, _lineLength + _lineCorection - 5, _menuText) << endl;
        }break;
        case ELineType::Input: {
            cout << format("{:<{}}{:>3}", _text, _lineLength + _lineCorection - 3, " - ");
        }break;

        }
    }
};