#pragma once


class Table {
private:
	int tableWidth;
	int tableHeight;
public:
	void setTableWidth(int tableWidth) {
		this->tableWidth = tableWidth;
	}
	int getTableWidth() {
		return this->tableWidth;
	}
	void setTableHeight(int tableHeight) {
		this->tableHeight = tableHeight;
	}
	int getTableHeight() {
		return this->tableHeight;
	}
};

extern Table table;

void printTable(int _vert, int _horiz, int _step);

