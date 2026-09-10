#include <iostream>
#include <format>
#include "Source.h"

using namespace std;

Table table;

void printTable(int _vert, int _horiz, int _step) {
    system("cls");

    int _y = table.getTableHeight() * 2;
    int _x = table.getTableWidth();

    cout << format("{:-<{}}", "", table.getTableHeight() * 5 + table.getTableHeight() + 1) << endl;

    for (int i = 1; i <= _y; i++) {

        for (int j = 1; j <= _x; j++) {

            if (j == _horiz && (i + 1) / 2 == _vert) {
                cout << format("|{:#<5}", "");
            }
            else {
                cout << format("|{: <5}", "");
            }
        }

        cout << "|" << endl;

        if (i % 2 == 0) {
            cout << format("{:-<{}}", "", table.getTableHeight() * 5 + table.getTableHeight() + 1) << endl;
        }
    }
    cout << "Step: " << _step << endl;
}

