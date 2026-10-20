#pragma once

#include <chrono>
#include <string>
#include <vector>

using namespace std;

//>-------------------Console formatting and input----------------
/**
* @class CFormation
* @brief Formats console output and handles user input.
*
* _lineLength - Minimum width of the text area inside a table.
*
* Lithuanian UTF-8 letters count as one character when aligning table columns.
*/
class CFormation {
private:
    int _lineLength{ 60 };

public:
    /**
    * @brief Creates a console formatter with a minimum table width.
    *
    * Keeps the default width of 60 when a non-positive width is supplied.
    *
    * @param[in] _length Minimum number of text characters inside a table.
    */
    explicit CFormation(int _length = 60);
    /**
    * @brief Calculatesthe number of characters in a UTF-8 encoded string.
    *
    * Counts UTF-8 characters by ignoring continuation bytes. This allows
    * Lithuanian characters encoded using multiple byts to be counted as a single character.
    *
    * @param[in] _text UTF-8 encoded text to processed.
    * @return Number of characters in the text
    */
    static int lithuanianLetters(const string& _text);
    /**
    * @brief Pads text to the requested column width.
    *
    * Adds spaces according to the UTF-8 character count. Text that already
    * meets or exceeds the width is returned without truncation.
    *
    * @param[in] _text Text to align.
    * @param[in] _width Requested column width in characters.
    * @return Text followed by any required padding spaces.
    */
    string fitText(const string& _text, int _width) const;
    /**
    * @brief Displays text lines inside an ASCII table.
    *
    * Uses the configured minimum width or the longest supplied line, whichever is larger.
    *
    * @param[in] _lines Text lines to display inside the table.
    */
    void displayBox(const vector<string>& _lines) const;
    /**
    * @brief Displays a prompt and reads one input line.
    *
    * @param[in] _prompt Prompt displayed before input.
    * @param[out] _value Text read from the input stream.
    * @return true if getline succeeds; false if input ends or fails.
    */
    bool getLine(const string& _prompt, string& _value) const;
    /**
    * @brief Reads and validates an integer within a range.
    *
    * Rejects malformed input, integer overflow, trailing non-whitespace characters
    * and values outside the allowed range. Repeats the prompt until input is valid
    * or the input stream ends.
    *
    * @param[in] _prompt Prompt displayed before each attempt.
    * @param[in] _minValue Minimum accepted integer.
    * @param[in] _maxValue Maximum accepted integer.
    * @param[out] _value Accepted integer; unchanged if input ends before a valid value is read.
    * @return true if a valid integer is read; otherwise false.
    */
    bool getInteger(const string& _prompt, int _minValue, int _maxValue, int& _value) const;
    /**
    * @brief Waits for the user to finish an input line by pressing Enter.
    *
    * Displays a continuation message and reads one complete line.
    * No cin.ignore() call is needed because other input also uses getline.
    *
    * @return true if the line is read; false if the input stream ends or fails.
    */
    bool wait() const;
    /**
    * @brief Displays a message and waits before continuing.
    *
    * Displays the primary message and includes a second line when it is not empty.
    *
    * @param[in] _text1 Primary message to display.
    * @param[in] _text2 Optional additional message.
    * @return true if the subsequent wait completes; false if input ends or fails.
    */
    bool announceMessage(const string& _text1, const string& _text2 = "") const;
};

//>---------------Question timer------------------
/**
* @class CTimer
* @brief Measures elapsed time using a monotonic clock.
*
* _start - Time point saved when the timer is created or reset.
*
* The game reads the timer before waiting on a result screen, so those pauses
* are not included in the answering time.
*/
class CTimer {
private:
    chrono::steady_clock::time_point _start{ chrono::steady_clock::now() };

public:
    /**
    * @brief Restarts the elapsed time measurement.
    *
    * Stores the current monotonic clock time as the new starting point.
    */
    void reset();
    /**
    * @brief Gets the elapsed time since creation or the last reset.
    *
    * @return Elapsed time in seconds as a floating-point value.
    */
    double getSeconds() const;
};
