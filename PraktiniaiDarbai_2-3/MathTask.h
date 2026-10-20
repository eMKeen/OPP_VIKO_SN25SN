#pragma once

#include <random>
#include <string>
#include <vector>

using namespace std;

//>-------------------Random number generator------------------
/**
* @class CRandomGenerator
* @brief Generates random integer values.
*
* The random engine is initialized once when the object is created.
*
* _engine - Random number engine used for inclusive integer ranges.
*/
class CRandomGenerator {
private:
    mt19937 _engine{ random_device{}() };

public:
    /**
    * @brief Generates a random integer in an inclusive range.
    *
    * @param[in] _minValue Minimum generated value.
    * @param[in] _maxValue Maximum generated value.
    * @return Random integer between the specified bounds.
    *
    * @note The caller must ensure that _minValue is not greater than _maxValue.
    */
    int getNumber(int _minValue, int _maxValue);
};

//>-----------------Common mathematical task-----------------
/**
* @class CMathTask
* @brief Defines the common interface of a mathematical task.
*
* The abstract class shares operand generation, task information and answer checking.
* Derived classes implement calculation and may adjust the generated operands.
*
* _random - Generator used for operand values.
* _number1 - First operand.
* _number2 - Second operand.
* _name - Displayed operation name.
* _symbol - Mathematical operation symbol.
* _weight - Weight used when calculating points.
*/
class CMathTask {
private:
    CRandomGenerator _random;

protected:
    int _number1{ 0 };
    int _number2{ 0 };
    string _name;
    char _symbol{ '?' };
    int _weight{ 1 };

    /**
    * @brief Creates the common task information.
    *
    * @param[in] _taskName Displayed operation name.
    * @param[in] _taskSymbol Mathematical operation symbol.
    * @param[in] _taskWeight Weight used when awarding points.
    */
    CMathTask(const string& _taskName, char _taskSymbol, int _taskWeight);
    /**
    * @brief Generates an operand value using the owned generator.
    *
    * @param[in] _minValue Minimum generated value.
    * @param[in] _maxValue Maximum generated value.
    * @return Random integer in the inclusive range.
    *
    * @note The caller must provide ordered bounds.
    */
    int randomNumber(int _minValue, int _maxValue);
    /**
    * @brief Provides a hook for operation-specific operand preparation.
    *
    * The base implementation leaves the generated operands unchanged.
    *
    * @param[in] _limit Selected operand limit; unused by the base implementation.
    */
    virtual void prepareNumbers(int _limit);

public:
    /**
    * @brief Destroys a task through the common base interface.
    *
    * The virtual destructor allows derived objects to be destroyed correctly.
    */
    virtual ~CMathTask() = default;

    /**
    * @brief Generates and prepares the operands.
    *
    * Generates two values from zero to the limit and calls the virtual prepareNumbers()
    * method so the selected operation can adjust them.
    *
    * @param[in] _limit Maximum operand value, from 1 to 1000.
    * @return true if the operands are generated; false if the limit is invalid.
    */
    virtual bool generate(int _limit);
    /**
    * @brief Calculates the correct answer for the current operands.
    *
    * This pure virtual method is implemented by each concrete operation.
    *
    * @return Correct integer answer.
    */
    virtual int calculate() const = 0;

    /**
    * @brief Checks the answer against the current calculation.
    *
    * @param[in] _answer Answer entered by the player.
    * @return true if the answer is correct; otherwise false.
    */
    bool checkAnswer(int _answer) const;
    /**
    * @brief Builds the mathematical expression.
    *
    * @return First operand, operation symbol and second operand as text.
    */
    string getExpression() const;
    /**
    * @brief Gets the operation name.
    *
    * @return Operation name displayed to the player.
    */
    string getName() const;
    /**
    * @brief Gets the mathematical operation symbol.
    *
    * @return Symbol used in the displayed expression.
    */
    char getSymbol() const;
    /**
    * @brief Gets the operation scoring weight.
    *
    * @return One for addition or subtraction; two for multiplication or division.
    */
    int getWeight() const;
    /**
    * @brief Gets the first operand.
    *
    * @return Current first operand.
    */
    int getFirstNumber() const;
    /**
    * @brief Gets the second operand.
    *
    * @return Current second operand.
    */
    int getSecondNumber() const;
    /**
    * @brief Gets the base task description.
    *
    * @return General mathematical task description.
    */
    string showInfo() const;
};

//>----------------Mathematical operations------------------
/**
* @class CAddition
* @brief Represents an addition task.
*
* Uses the inherited operand generation and adds the two operands.
* Its non-virtual showInfo() method hides the method declared in CMathTask.
*/
class CAddition : public CMathTask {
public:
    /**
    * @brief Creates an addition task.
    *
    * Initializes the operation name, symbol and scoring weight.
    */
    CAddition();
    /**
    * @brief Calculates the addition result.
    *
    * @return Sum of the operands.
    */
    int calculate() const override;
    /**
    * @brief Gets the addition task description.
    *
    * Hides the non-virtual showInfo() method of CMathTask.
    *
    * @return Addition-specific task description.
    */
    string showInfo() const;
};

/**
* @class CSubtraction
* @brief Represents a subtraction task.
*
* Orders the generated operands so that the answer is not negative.
*/
class CSubtraction : public CMathTask {
protected:
    /**
    * @brief Orders the operands to avoid a negative answer.
    *
    * Swaps the operands when the first is smaller than the second.
    *
    * @param[in] _limit Selected operand limit; unused because ordering does not change the range.
    */
    void prepareNumbers(int _limit) override;

public:
    /**
    * @brief Creates a subtraction task.
    *
    * Initializes the operation name, symbol and scoring weight.
    */
    CSubtraction();
    /**
    * @brief Calculates the subtraction result.
    *
    * @return Non-negative difference of the prepared operands.
    */
    int calculate() const override;
};

/**
* @class CMultiplication
* @brief Represents a multiplication task.
*
* Uses the inherited operand generation and multiplies the two operands.
*/
class CMultiplication : public CMathTask {
public:
    /**
    * @brief Creates a multiplication task.
    *
    * Initializes the operation name, symbol and scoring weight.
    */
    CMultiplication();
    /**
    * @brief Calculates the multiplication result.
    *
    * @return Product of the operands.
    */
    int calculate() const override;
};

/**
* @class CDivision
* @brief Represents an integer division task.
*
* Prepares a non-zero divisor and a dividend that is an exact multiple of it.
* Both operands remain within the selected limit.
*/
class CDivision : public CMathTask {
protected:
    /**
    * @brief Prepares operands for division without a remainder.
    *
    * Selects a divisor from 1 to the limit, then generates an integer quotient
    * and uses their product as the dividend.
    *
    * @param[in] _limit Maximum operand value, previously validated by generate().
    */
    void prepareNumbers(int _limit) override;

public:
    /**
    * @brief Creates a division task.
    *
    * Initializes the operation name, symbol and scoring weight.
    * Initializes the divisor to one so the initial calculation is defined.
    */
    CDivision();
    /**
    * @brief Calculates the division result.
    *
    * @return Integer quotient of the prepared operands.
    */
    int calculate() const override;
};

//>-----------------Selected and mixed operations-----------------
/**
* @class CMixedTask
* @brief Manages the operations selected for a game.
*
* Owns four concrete task objects and selects one through the base class interface.
* One selected operation produces a single-operation game; several produce a mixed game.
*
* _addition - Addition task object.
* _subtraction - Subtraction task object.
* _multiplication - Multiplication task object.
* _division - Division task object.
* _operations - Unique operation numbers selected by the player.
* _current - Non-owning pointer to the currently selected member object.
*
* @note Copying is disabled because _current points to a member of this object.
*/
class CMixedTask : public CMathTask, protected CRandomGenerator {
private:
    CAddition _addition;
    CSubtraction _subtraction;
    CMultiplication _multiplication;
    CDivision _division;
    vector<int> _operations{ 1 };
    CMathTask* _current{ &_addition };

    /**
    * @brief Finds the task object for an operation number.
    *
    * @param[in] _operation Operation number: 1 addition, 2 subtraction, 3 multiplication, 4 division.
    * @return Non-owning pointer to the matching member object, or nullptr for an invalid number.
    */
    CMathTask* selectTask(int _operation);

public:
    /**
    * @brief Creates a task selector with addition selected initially.
    *
    * The four concrete task objects are owned directly by this object.
    */
    CMixedTask();
    /**
    * @brief Disables copying of the task selector.
    *
    * Prevents a copied selector from keeping a pointer to another object
    * through its _current member.
    */
    CMixedTask(const CMixedTask&) = delete;
    /**
    * @brief Disables copy assignment of the task selector.
    *
    * Preserves the relationship between the selector and its owned task objects.
    */
    CMixedTask& operator=(const CMixedTask&) = delete;

    /**
    * @brief Validates and stores the selected operations.
    *
    * Rejects an empty selection or numbers outside 1..4. Removes duplicates
    * while preserving the order of the first occurrence.
    *
    * @param[in] _selectedOperations Operation numbers to include in the game.
    * @return true if the selection is stored; otherwise false.
    *
    * @note Invalid input leaves the previous selection unchanged.
    *       The new selection is used when the next task is generated.
    */
    bool setOperations(const vector<int>& _selectedOperations);
    /**
    * @brief Gets the name associated with an operation number.
    *
    * @param[in] _operation Operation number from 1 to 4.
    * @return Operation name, or the unknown-operation message for an invalid number.
    */
    string getOperationName(int _operation);
    /**
    * @brief Selects an operation and generates its operands.
    *
    * Randomly selects one of the configured operations, invokes its generation method
    * and updates the shared task information to match the selected object.
    *
    * @param[in] _limit Maximum operand value, from 1 to 1000.
    * @return true if a task is generated; false if the limit is invalid.
    */
    bool generate(int _limit) override;
    /**
    * @brief Calculates the answer using the currently selected task.
    *
    * @return Answer returned by the selected concrete operation.
    */
    int calculate() const override;
};
