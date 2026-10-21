/**
* @file Game.cpp
* @brief Implements the player setup, main menu and game session.
*
* Handles operation selection, answering time, point calculation and result display
* through the objects owned by CGame.
*/
#include <iomanip>
#include <iostream>
#include <limits>
#include "Game.h"

using namespace std;

//>----------------Player and operation selection------------------
bool CGame::readPlayer() {
    string _userName;
    while (_format.getLine("Įveskite vardą (1–24 simboliai): ", _userName)) {
        if (_player.setUserName(_userName))
            return true;

        if (!_format.announceMessage("Netinkamas vardas.", "Naudokite 1–24 simbolius, be kabliataškių ar tabuliacijos."))
            return false;
    }

    return false;
}

bool CGame::selectOperations(int _mode) {
    if (_mode != 5)
        return _tasks.setOperations({ _mode });

    while (true) {
        vector<int> _operations;

        for (int _operation = 1; _operation <= 4; _operation++) {
            int _selected{ 0 };
            if (!_format.getInteger("Įtraukti " + _tasks.getOperationName(_operation) +
                "? (1 = taip, 0 = ne): ", 0, 1, _selected))
                return false;

            if (_selected == 1)
                _operations.push_back(_operation);
        }

        if (_tasks.setOperations(_operations))
            return true;

        if (!_format.announceMessage("Pasirinkite bent vieną veiksmą."))
            return false;
    }
}

//>-----------------Game session---------------
bool CGame::playGame(int _mode) {
    if (!selectOperations(_mode))
        return false;

    int _total{ 0 };
    int _limit{ 0 };

    while (true) {
        if (!_format.getInteger("Užduočių kiekis (10, 20, 30, 40, 50): ", 10, 50, _total))
            return false;

        if (_total % 10 == 0)
            break;

        if (!_format.announceMessage("Užduočių kiekis turi dalintis iš 10."))
            return false;
    }

    if (!_format.getInteger("Didžiausias variacinis skaičius (1–1000; daugybos lentelei 10): ", 1, 1000, _limit))
        return false;

    CScore _score;
    int _correct{ 0 };
    double _totalSeconds{ 0 };
    CMathTask* _task = &_tasks;

    for (int _question = 1; _question <= _total; _question++) {
        system("cls");

        _task->generate(_limit);
        _format.displayBox({ "Klausimas " + to_string(_question) + " / " + to_string(_total), 
            _task->getName(), _task->getExpression() + " = ?" });

        int _answer{ 0 };
        _timer.reset();
        if (!_format.getInteger("Atsakymas: ", numeric_limits<int>::min(), numeric_limits<int>::max(), _answer))
            return false;

        double _seconds = _timer.getSeconds();
        _totalSeconds += _seconds;
        bool _isCorrect = _task->checkAnswer(_answer);
        if (_isCorrect)
            _correct++;

        int _earned = _score.calculatePoints(_isCorrect, _task->getWeight(), _seconds);
        _score += _earned;

        _format.displayBox({ _isCorrect ? "TEISINGAI!" : "NETEISINGAI!", 
            "Teisingas atsakymas: " + to_string(_task->calculate()) });
        cout << fixed << setprecision(2) << "Laikas: " << _seconds << " s | +" << _earned 
            << " taškų | Iš viso: " << _score.getPoints() << endl;

        // Wait after each question result. This pause does not affect the score.
        if (_question < _total && !_format.wait())
            return false;
    }

    CResult _result{ _player.getUserName(), _correct, _total, _totalSeconds, _score.getPoints() };
    _scoreBoard.displayResults({ _result }, _format);
    cout << "Teisingi: " << _correct << " | Neteisingi: " << _total - _correct
        << " | Tikslumas: " << 100.0 * _correct / _total << "%" << endl;

    if (_scoreBoard.saveResult(_result))
        cout << "Rezultatas įrašytas į scoreboard.txt." << endl;
    else
        cout << "Nepavyko įrašyti rezultato į scoreboard.txt. Patikrinkite prieigą prie failo." << endl;

    // The final question and the game summary share one pause after saving.
    return _format.wait();
}

//>-------------------Scoreboard menu------------------
bool CGame::showScoreBoard() {
    vector<CResult> _results;
    int _skipped{ 0 };

    if (!_scoreBoard.getResults(_results, _skipped))
        return _format.announceMessage("Nepavyko perskaityti scoreboard.txt.");

    _scoreBoard.displayResults(_results, _format);
    if (_skipped > 0)
        cout << "Praleista sugadintų eilučių: " << _skipped << endl;

    return _format.wait();
}

//>-------------------Main menu------------------
void CGame::run() {
    _format.displayBox({ "MATEMATINIS ŽAIDIMAS", "Mokykis, skaičiuok ir gerink savo rezultatą!" });
    if (!readPlayer())
        return;


    while (true) {
        _format.displayBox({ 
            "1. Sudėtis", 
            "2. Atimtis", 
            "3. Daugyba", 
            "4. Dalyba", 
            "5. Mišrūs veiksmai", 
            "6. Rezultatų lentelė", 
            "0. Baigti" 
            });

        int _mode{ 0 };
        if (!_format.getInteger("Pasirinkimas: ", 0, 6, _mode) || _mode == 0)
            return;

        if (_mode == 6) {
            if (!showScoreBoard())
                return;
        }
        else if (!playGame(_mode)) {
            cout << "Įvestis baigta. Nebaigtos sesijos rezultatas nesaugomas." << endl;
            return;
        }
    }
}
