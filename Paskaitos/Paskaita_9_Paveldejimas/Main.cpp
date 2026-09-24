#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

class CBaseAccount {
//private: ///< Changing to -> protected
protected: ///< Got access from outher classes
	string name;
	string acountNumber;
	double balance;
public:
	void setName(string _name) {
		name = _name;
	}

};

class CCardAccount : private CBaseAccount {
	string cardNumber;
};

//class CVIPAccount : public CBaseAccount {
//class CVIPAccount : private CBaseAccount { ///<changed from public, fields become private to this class
	class CVIPAccount : protected CBaseAccount { ///< Public field become protected
	double extraAmount;
public:
	CVIPAccount() {
		this->extraAmount = 300.50;
		this->balance = 500.0; ///< Imposible ir private without setter
		//this->setName("VIP ACCOUNT 1"); ///< before protected
		this->acountNumber = "10001";
		this->acountNumber = "VIP account 1";

		this->setName("VIP account 1");

	}
};

	class CExtraVIPAccount : protected CVIPAccount {
		CExtraVIPAccount() {
			this->setName("VIP account 1");
		}
	};

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	CVIPAccount vipAccount1;
	//vipAccount1.extraAmount = 500.30; ///< Imposible (private or protected field)
	//vipAccount1.setName("VIP Account 1"); ///< Using setter ///< class CVIPAccount : private CBaseAccount -- Imposible

	//CExtraVIPAccount extraVIPAccount; //Protected not accesible

}