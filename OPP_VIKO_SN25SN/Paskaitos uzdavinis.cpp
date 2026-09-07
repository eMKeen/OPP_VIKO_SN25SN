#include <iostream>
#include <string>
#include <windows.h>

using namespace std;


int task1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string toDay[] = {
        "Laurynas",
        "Erdenis",
        "Dingailė",
        "Justina",
        "Stanislav",
        "Stase"
    };
    string nextDay[] = {
        "Beata",
        "Faustas",
        "Vaistautas",
        "Tautene",
        "Klodoaldas",
        "Pulcherija",
        "Regina",
        "Bartas",
        "Barte",
        "Palmira",
        "Adrijonas",
        "Marija",
        "Liaugauda",
        "Daumantė",
        "Klementina",
        "Klodas",
        "Pamyra",
        "Falmira"
    };

    cout << "++++++++++++++++++++++++" << endl;
    cout << "Šiandienos vardaniai yra" << endl;
    for (int i = 0; i < size(toDay); i++) {
        cout << i + 1 << " " << toDay[i] << endl;
    }

    cout << "++++++++++++++++++++++++" << endl;
    cout << "Artimiausi vardaniai yra" << endl;

    for (int i = 0; i < size(nextDay); i++) {
        cout << i + 1 << " " << nextDay[i] << endl;
    }

    string wait;
    cin.ignore();
    getline(cin, wait);

    return 0;
}