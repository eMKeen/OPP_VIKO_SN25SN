/**
* @file MathTask.cpp
* @brief Implements the shared task interface and mathematical operations.
*
* Contains operand generation, operation-specific preparation and calculation,
* and selection of a concrete task through the base class interface.
*/
#include <algorithm>
#include "MathTask.h"

using namespace std;

//>-------------------Random number generator------------------
int CRandomGenerator::getNumber(int _minValue, int _maxValue) {
    uniform_int_distribution<int> _range(_minValue, _maxValue);
    return _range(_engine);
}

//>-------------------Common mathematical task------------------
CMathTask::CMathTask(const string& _taskName, char _taskSymbol, int _taskWeight)
    : _name(_taskName), _symbol(_taskSymbol), _weight(_taskWeight) {
}

int CMathTask::randomNumber(int _minValue, int _maxValue) {
    return _random.getNumber(_minValue, _maxValue);
}

bool CMathTask::generate(int _limit) {
    if (_limit < 1 || _limit > 1000)
        return false;

    // All operations use this shared generation method.
    _number1 = randomNumber(0, _limit);
    _number2 = randomNumber(0, _limit);
    prepareNumbers(_limit);
    return true;
}

void CMathTask::prepareNumbers(int) {
    // Addition and multiplication need no changes to the generated operands.
}

bool CMathTask::checkAnswer(int _answer) const {
    return _answer == calculate();
}

string CMathTask::getExpression() const {
    return to_string(_number1) + " " + _symbol + " " + to_string(_number2);
}

string CMathTask::getName() const {
    return _name;
}

char CMathTask::getSymbol() const {
    return _symbol;
}

int CMathTask::getWeight() const {
    return _weight;
}

int CMathTask::getFirstNumber() const {
    return _number1;
}

int CMathTask::getSecondNumber() const {
    return _number2;
}

string CMathTask::showInfo() const {
    return "Matematikos užduotis";
}

//>-------------------Addition------------------
CAddition::CAddition() : CMathTask("Sudėtis", '+', 1) {
}

int CAddition::calculate() const {
    return _number1 + _number2;
}

string CAddition::showInfo() const {
    return "Sudėties užduotis";
}

//>-------------------Subtraction------------------
CSubtraction::CSubtraction() : CMathTask("Atimtis", '-', 1) {
}

void CSubtraction::prepareNumbers(int) {
    if (_number1 < _number2)
        swap(_number1, _number2);
}

int CSubtraction::calculate() const {
    return _number1 - _number2;
}

//>-------------------Multiplication------------------
CMultiplication::CMultiplication() : CMathTask("Daugyba", '*', 2) {
}

int CMultiplication::calculate() const {
    return _number1 * _number2;
}

//>-------------------Integer division------------------
CDivision::CDivision() : CMathTask("Dalyba", '/', 2) {
    _number2 = 1;
}

void CDivision::prepareNumbers(int _limit) {
    _number2 = randomNumber(1, _limit);
    int _quotient = randomNumber(0, _limit / _number2);
    _number1 = _quotient * _number2;
}

int CDivision::calculate() const {
    return _number1 / _number2;
}

//>-------------------Selected and mixed operations------------------
CMixedTask::CMixedTask() : CMathTask("Sudėtis", '+', 1) {
}

CMathTask* CMixedTask::selectTask(int _operation) {
    switch (_operation) {
    case 1:
        return &_addition;
    case 2:
        return &_subtraction;
    case 3:
        return &_multiplication;
    case 4:
        return &_division;
    default:
        return nullptr;
    }
}

bool CMixedTask::setOperations(const vector<int>& _selectedOperations) {
    if (_selectedOperations.empty())
        return false;

    vector<int> _validOperations;
    for (int _operation : _selectedOperations) {
        if (_operation < 1 || _operation > 4)
            return false;

        if (find(_validOperations.begin(), _validOperations.end(), _operation) == _validOperations.end())
            _validOperations.push_back(_operation);
    }

    _operations = _validOperations;
    return true;
}

string CMixedTask::getOperationName(int _operation) {
    CMathTask* _task = selectTask(_operation);
    if (_task == nullptr)
        return "Nežinomas veiksmas";

    return _task->getName();
}

bool CMixedTask::generate(int _limit) {
    if (_limit < 1 || _limit > 1000)
        return false;

    int _index = getNumber(0, static_cast<int>(_operations.size()) - 1);
    _current = selectTask(_operations[_index]);
    _current->generate(_limit);

    // The common interface always describes the currently selected operation.
    _number1 = _current->getFirstNumber();
    _number2 = _current->getSecondNumber();
    _name = _current->getName();
    _symbol = _current->getSymbol();
    _weight = _current->getWeight();
    return true;
}

int CMixedTask::calculate() const {
    return _current->calculate();
}
