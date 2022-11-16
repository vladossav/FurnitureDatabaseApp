#include "InputHelper.h"


long getAndCheckInputInteger(long maxInteger) {
	string menuNum;
	long num;
	while (1) {
		getline(cin, menuNum);
		if (!int_sign(menuNum) || menuNum.length() == 0) {
			cout << "Требуется ввести число! Попробуйте снова:" << endl;
		}
		else {
			num = atoi(menuNum.c_str());
			if (maxInteger != 0 && (num >= maxInteger) || num < 0) {
				cout << "Некорректный ввод! Попробуйте снова: " << endl;
				continue;
			}
			break;
		}
	}
	
	return atoi(menuNum.c_str());
}

bool int_sign(const string& s) {
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

string getInputString(typeInputString type) {
	string out;
	switch (type) {
	case NAME_FURNITURE:
		out = "новое название мебели: ";
		break;
	case MODEL_FURNITURE:
		out = "новую модель мебели: ";
		break;
	case COLOR_FURNITURE:
		out = "новый цвет мебели: ";
		break;
	case NAME_CUSTOMER:
		out = "наименование заказчика: ";
		break;
	case STREET:
		break;
	case CITY:
		break;
	default:
		break;
	}
	string name;
	bool flag = true;
	while (flag) {
		cout << "Введите " << out;
		getline(cin, name);
		if (!name.length() || int_sign(name))
			cout << "Введенные данные некорректны. Попробуйте снова" << endl;
		else flag = false;
	}
	return name;
}

float getInputCostFurniture() {
	string costStr;
	float cost;
	bool flag = true;
	while (flag) {
		cout << "Введите стоимость мебели: ";
		getline(cin, costStr);
		char* ending;
		cost = strtof(costStr.c_str(), &ending);
		if (!costStr.length() || *ending != 0)
			cout << "Введенные данные некорректны. Ожидается число. Дробная часть отделяется знаком \",\". Попробуйте снова" << endl;
		else if (cost < 0) 
			cout << "Ожидается положительное число. Попробуйте снова" << endl;
		else flag = false;
	}
	cost = round(cost * 100) / 100;
	return cost;
}

void makeInputFurnitureProperties(short& length, short& width, short& height, int &weight) {
	bool flag = true;
	string propertiesStr;
	while (flag) {
		cout << "Введите параметры длины(мм), ширины(мм), высоты(мм), веса(г) через пробел: ";
		getline(cin, propertiesStr);
		std::stringstream stream(propertiesStr);

		stream >> length >> width >> height;
		stream >> weight;

		if (!stream) 
			cout << "Введенные данные некорректны. Попробуйте снова" << endl;
		else if (length < 0 || width < 0 || height < 0 || weight < 0) 
			cout << "Введенные данные некорректны. Попробуйте снова" << endl;
		else flag = false;
	}
}


void show(vector<Furniture> fur) {
	TablePrinter ct(Furniture::TABLE_NAME, 1, Furniture::TABLE_COLUMNS.size());
	ct.EnableExtendedAsciiChar(false);
	ct.SetHaveLineNumber(true);
	ct.SetHaveLineDiv(true);
	ct.SetHaveColDiv(true);

	for (int i = 0; i < Furniture::TABLE_COLUMNS.size(); i++) {
		ct.SetColHeader(i, Furniture::TABLE_COLUMNS[i])
			.SetColWidth(Furniture::TABLE_COLUMN_SIZE[i], i);
	}

	for (int k = 0; k < fur.size(); k++) {
		vector<string> str = fur[k].getStringLine();
		for (int i = 0; i < str.size(); i++) {
			ct.Print(str[i]);
		}
	}
}

void show(Furniture& fur) {
	TablePrinter ct(Furniture::TABLE_NAME, 1, Furniture::TABLE_COLUMNS.size());
	ct.EnableExtendedAsciiChar(false);
	ct.SetHaveLineNumber(false);
	ct.SetHaveLineDiv(true);
	ct.SetHaveColDiv(true);

	for (int i = 0; i < Furniture::TABLE_COLUMNS.size(); i++) {
		ct.SetColHeader(i, Furniture::TABLE_COLUMNS[i])
			.SetColWidth(Furniture::TABLE_COLUMN_SIZE[i], i);
	}

	vector<string> str = fur.getStringLine();
	for (int i = 0; i < str.size(); i++) {
		ct.Print(str[i]);
	}
}

