#pragma once
#include <sstream>
#include <iostream>
#include "TablePrinter.h"
#include "Furniture.h"
using namespace std;


enum typeInputString {
	NAME_FURNITURE, MODEL_FURNITURE, COLOR_FURNITURE, 
	NAME_CUSTOMER, 
	STREET, CITY
};

long getAndCheckInputInteger(long maxInteger = 0);
bool int_sign(const string& s);
string getInputString(typeInputString type);
float getInputCostFurniture();
void makeInputFurnitureProperties(short& length, short& width, short& depth, int &weight);

void show(vector<Furniture> f);
void show(Furniture& fur);