#include "InputHelper.h"


size_t getAndCheckInputInteger(size_t maxInteger) {
	string menuNum;
	size_t num;
	while (1) {
		getline(cin, menuNum);
		if (!int_sign(menuNum) || menuNum.length() == 0) {
			cout << "Требуется ввести число! Попробуйте снова:" << endl;
		}
		else {
			num = atoll(menuNum.c_str());
			if (maxInteger != 0 && (num >= maxInteger) || num < 0) {
				cout << "Некорректный ввод! Попробуйте снова: " << endl;
				continue;
			}
			break;
		}
	}
	
	return num;
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

void makeInputCustomerAddress(string& city, string& street, short& buildingNum) {
	bool flag = true;
	string propertiesStr;
	while (flag) {
		cout << "Введите город, улицу, номер дома через пробел: ";
		getline(cin, propertiesStr);
		std::stringstream stream(propertiesStr);

		stream >> city >> street;
		stream >> buildingNum;

		if (!stream)
			cout << "Введенные данные некорректны. Попробуйте снова" << endl;
		else if (buildingNum < 0)
			cout << "Введенные данные некорректны. Попробуйте снова" << endl;
		else flag = false;
	}
}






