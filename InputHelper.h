#pragma once
#include <sstream>
#include <iostream>

#include "Furniture.h"
#include "Customer.h"
#include "TablePrinter.h"
using namespace std;


enum typeInputString {
	NAME_FURNITURE, MODEL_FURNITURE, COLOR_FURNITURE, 
	NAME_CUSTOMER
};

size_t getAndCheckInputInteger(size_t maxInteger = 0);
bool int_sign(const string& s);
string getInputString(typeInputString type);
float getInputCostFurniture();
void makeInputFurnitureProperties(short& length, short& width, short& depth, int &weight);
void makeInputCustomerAddress(string& city, string& street, short &buildingNum);
std::string getInputDate();

template <class T>
void show(vector<T> table) {
	string tableName = T::TABLE_NAME;
	vector<string> columnNames = T::TABLE_COLUMNS;
	vector<int> columnSize = T::TABLE_COLUMN_SIZE;

	TablePrinter ct(tableName, 1, columnNames.size());
	ct.EnableExtendedAsciiChar(false);
	ct.SetHaveLineNumber(true);
	ct.SetHaveLineDiv(true);
	ct.SetHaveColDiv(true);

	for (int i = 0; i < columnNames.size(); i++) {
		ct.SetColHeader(i, columnNames[i])
			.SetColWidth(columnSize[i], i);
	}

	for (int k = 0; k < table.size(); k++) {
		vector<string> str = table[k].getStringLine();
		for (int i = 0; i < str.size(); i++) {
			ct.Print(str[i]);
		}
	}
}

template <class T>
void show(T& table) {
	string tableName = T::TABLE_NAME;
	vector<string> columnNames = T::TABLE_COLUMNS;
	vector<int> columnSize = T::TABLE_COLUMN_SIZE;

	TablePrinter ct(tableName, 1, (int)columnNames.size());
	ct.EnableExtendedAsciiChar(false);
	ct.SetHaveLineNumber(false);
	ct.SetHaveLineDiv(true);
	ct.SetHaveColDiv(true);

	for (int i = 0; i < columnNames.size(); i++) {
		ct.SetColHeader(i, columnNames[i])
			.SetColWidth(columnSize[i], i);
	}

	vector<string> str = table.getStringLine();
	for (int i = 0; i < str.size(); i++) {
		ct.Print(str[i]);
	}
}