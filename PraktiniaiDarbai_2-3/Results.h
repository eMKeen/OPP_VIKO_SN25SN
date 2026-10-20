#pragma once

#include <string>
#include <vector>
#include "Utils.h"

using namespace std;

//>-------------------Player information------------------
/**
* @class CPlayer
* @brief Stores the name used to identify the player.
*
* _userName - Validated player name displayed in the result table.
*/
class CPlayer {
private:
    string _userName;

public:
    /**
    * @brief Validates and assigns the player name.
    *
    * Accepts a non-empty name of up to 24 UTF-8 characters that is not only spaces.
    * Rejects semicolons and control characters.
    *
    * @param[in] _value Player name to assign.
    * @return true if the name is stored; false if it is invalid.
    *
    * @note Invalid input leaves the previous name unchanged.
    */
    bool setUserName(const string& _value);
    /**
    * @brief Gets the player name.
    *
    * @return Stored player name.
    */
    string getUserName() const;
};

//>-------------------Score calculation------------------
/**
* @class CScore
* @brief Calculates and stores the points earned during a game.
*
* _points - Accumulated points, limited to the maximum game score of 10000.
*/
class CScore {
private:
    int _points{ 0 };

public:
    /**
    * @brief Adds earned points to the accumulated score.
    *
    * Accepts a non-negative increment only when the resulting score does not exceed 10000.
    * Other values leave the score unchanged.
    *
    * @param[in] _addedPoints Number of points to add.
    * @return Reference to this score object, allowing chained additions.
    */
    CScore& operator+=(int _addedPoints);
    /**
    * @brief Gets the accumulated score.
    *
    * @return Total number of points earned.
    */
    int getPoints() const;
    /**
    * @brief Calculates points for one answer.
    *
    * For a correct answer, awards 10 times the weight plus a speed bonus
    * of 90 times the weight divided by the answering time. The bonus is truncated
    * to an integer and times below one second are treated as one second.
    *
    * @param[in] _correct Whether the answer is correct.
    * @param[in] _weight Operation weight: 1 or 2.
    * @param[in] _seconds Finite, non-negative answering time in seconds.
    * @return Calculated points, or zero for an incorrect answer or invalid arguments.
    */
    int calculatePoints(bool _correct, int _weight, double _seconds) const;
};

//>-------------------Completed game result------------------
/**
* @struct CResult
* @brief Stores the result of one completed game.
*
* _userName - Player name.
* _correct - Number of correct answers.
* _total - Number of questions in the session.
* _seconds - Sum of question answering times, excluding result-screen pauses.
* _points - Total points earned during the session.
*/
struct CResult {
    string _userName;
    int _correct{ 0 };
    int _total{ 0 };
    double _seconds{ 0 };
    int _points{ 0 };
};

//>-------------------Text file storage------------------
/**
* @class CFileStorage
* @brief Reads and appends lines in a text file.
*
* _path - Path of the file used for storing game results.
*
* @note Relative paths are resolved from the program working directory.
*/
class CFileStorage {
private:
    string _path;

public:
    /**
    * @brief Creates storage for the specified text file.
    *
    * @param[in] _filePath File path used for reading and appending results.
    */
    explicit CFileStorage(const string& _filePath);
    /**
    * @brief Appends a line to the file.
    *
    * Opens the file in append mode, writes the text and a newline, and flushes the stream.
    * Creates the file if it does not exist and its parent directory is available.
    *
    * @param[in] _line Text line to append.
    * @return true if the stream reports a successful write; otherwise false.
    */
    bool appendLine(const string& _line) const;
    /**
    * @brief Reads all available lines from the file.
    *
    * Clears the output collection before reading. A missing file is treated
    * as an empty result history.
    *
    * @param[out] _lines Lines read from the file.
    * @return true if reading succeeds or the file does not exist; false on an access or read error.
    *
    * @note The output collection may contain partial data if reading fails.
    */
    bool readLines(vector<string>& _lines) const;
};

//>-------------------Scoreboard------------------
/**
* @class CScoreBoard
* @brief Validates, stores and displays completed game results.
*
* Uses private inheritance to keep the file operations inside the scoreboard.
* Valid results are sorted by points before they are returned to the caller.
*/
class CScoreBoard : private CFileStorage {
private:
    /**
    * @brief Checks whether a completed result can be stored.
    *
    * Validates the player name, question count, correct-answer count, elapsed time
    * and score. Accepts 10 to 50 questions in steps of 10 and at most 200 points
    * per correct answer.
    *
    * @param[in] _result Completed result to validate.
    * @return true if all fields satisfy the storage rules; otherwise false.
    */
    bool isValid(const CResult& _result) const;
    /**
    * @brief Compares the points of two results.
    *
    * @param[in] _first First result to compare.
    * @param[in] _second Second result to compare.
    * @return true if the first result has more points than the second.
    */
    static bool hasHigherScore(const CResult& _first, const CResult& _second);

public:
    /**
    * @brief Creates a scoreboard connected to a text file.
    *
    * @param[in] _path Result file path; scoreboard.txt by default.
    */
    explicit CScoreBoard(const string& _path = "scoreboard.txt");
    /**
    * @brief Validates and appends a completed result.
    *
    * Writes the name, correct-answer count, question count, answering time and points
    * as a semicolon-separated line. Time is stored with three decimal places.
    *
    * @param[in] _result Completed game result to save.
    * @return true if the result is valid and the line is written; otherwise false.
    */
    bool saveResult(const CResult& _result) const;
    /**
    * @brief Reads and sorts valid game results.
    *
    * Clears the outputs, skips malformed or invalid lines and sorts valid results
    * by points in descending order. Equal scores retain their file order.
    *
    * @param[out] _results Valid results sorted by points.
    * @param[out] _skipped Number of malformed or invalid lines skipped.
    * @return true if the file is read or does not exist; false if reading fails.
    */
    bool getResults(vector<CResult>& _results, int& _skipped) const;
    /**
    * @brief Displays the supplied results in a formatted table.
    *
    * Shows the player name, correct answers, question count, time and points.
    * Displays an empty-history message if no results are supplied.
    *
    * @param[in] _results Results to display in their supplied order.
    * @param[in] _format Console formatter used for UTF-8 column alignment and table borders.
    *
    * @note This method does not sort, save or wait; the caller controls those operations.
    */
    void displayResults(const vector<CResult>& _results, const CFormation& _format) const;
};
