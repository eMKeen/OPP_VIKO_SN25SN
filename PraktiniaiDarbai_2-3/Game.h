#pragma once

#include "MathTask.h"
#include "Results.h"
#include "Utils.h"

using namespace std;

//>------------------Game control------------------
/**
* @class CGame
* @brief Combines settings, questions and result handling.
*
* The class reads the player name, processes menu selections and runs game sessions.
* It owns the objects used for console output, task selection, timing and storage.
*
* _player - Player information.
* _format - Console formatting and input handling.
* _scoreBoard - Completed game result storage.
* _tasks - Available and selected mathematical operations.
* _timer - Timer used for each question.
*/
class CGame {
private:
    CPlayer _player;
    CFormation _format;
    CScoreBoard _scoreBoard;
    CMixedTask _tasks;
    CTimer _timer;

    /**
    * @brief Reads and validates the player name.
    *
    * Requests the name again after an invalid value and waits after the error message.
    *
    * @return true if a valid name is stored; false if input ends.
    */
    bool readPlayer();
    /**
    * @brief Sets the operations used in the game.
    *
    * For mixed mode, asks whether each operation should be included.
    * An empty selection is requested again.
    *
    * @param[in] _mode Game mode: 1 to 4 for one operation, or 5 for mixed operations.
    * @return true if the selection is accepted; false if input ends or a single mode is invalid.
    */
    bool selectOperations(int _mode);
    /**
    * @brief Runs one session and attempts to save its result.
    *
    * Reads the question count and operand limit, generates questions and checks answers.
    * Accumulates answering time and points, displays the summary and attempts to append it
    * to the result file before the final wait.
    *
    * @param[in] _mode Selected game mode from 1 to 5.
    * @return true if the session and final wait complete; false if input ends or selection fails.
    *
    * @note A completed result may already be saved if input ends at the final wait.
    *       A storage failure is displayed but does not itself cause a false return.
    */
    bool playGame(int _mode);
    /**
    * @brief Displays stored game results.
    *
    * Reads the result file, displays valid rows and reports the number of skipped rows.
    * Displays an error message if reading fails and waits before returning.
    *
    * @return true if the wait completes; false if input ends during the wait.
    */
    bool showScoreBoard();

public:
    /**
    * @brief Starts the game and processes the main menu.
    *
    * Reads the player name and handles game or scoreboard selections until the player
    * chooses to exit or an input operation ends.
    */
    void run();
};
