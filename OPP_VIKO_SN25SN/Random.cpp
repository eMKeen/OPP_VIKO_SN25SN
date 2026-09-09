#include <iostream>
#include <random>
#include <string>

using namespace std;

int main();

int task2() {
	int _randomNumbers[19]{};

	random_device _rn;
	mt19937 _gen(_rn());
	uniform_int_distribution<int> _dist(1, 100);

	for (int i = 0; i < 19; i++) {
		_randomNumbers[i] = _dist(_gen);
	}

	cout << "=====================" << endl;
	cout << "Viso masyvo elementai" << endl;
	cout << endl;
	for (int i = 0; i < 19; i++) {
		cout << i + 1 << " " << _randomNumbers[i] << endl;
	}

	cout << "=====================" << endl;
	cout << "Lyginiai skaičiai" << endl;
	int _eilesNumeris = 0;
	for (int i = 0; i < 19; i++) {
		if (_randomNumbers[i] % 2 == 0)	{
			_eilesNumeris++;
			cout << _eilesNumeris << " " << _randomNumbers[i] << endl;
		}
	}

	cout << "=====================" << endl;
	cout << "Visų skaičių suma" << endl;
	int _summ = 0;
	for (int i = 0; i < 19; i++) {
		_summ += _randomNumbers[i];
	}
	cout << _summ << endl;

	string wait;
	cin.ignore();
	getline(cin, wait);

	return main();
}