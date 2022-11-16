//#include <sstream>
//#include <iostream>
//#include "Database.h"
#include "InputHelper.h"
#include "Furniture.h"
#include "FurnitureRepository.h"


using namespace std;
void menu();
void furnitureEditMenu(FurnitureRepository& furnRepo);
void furnitureAddMenu(FurnitureRepository& furnRepo);
void furnitureRemoveMenu(FurnitureRepository& furnRepo);

int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	
	FurnitureRepository furnRepo;
	
	bool menuFlag = true;
	while (menuFlag) {
		menu();
		
		switch (getAndCheckInputInteger()) {
		case 0: {
			menuFlag = false;
			break;
		}
		case 1: { //показать мебель
			show(furnRepo.getAllFurniture());
			break;
		}
		case 2: { //добавить мебель
			furnitureAddMenu(furnRepo);
			break;
		}
		case 3: { //редактировать мебель
			furnitureEditMenu(furnRepo);
			break;
		}
		case 4: { //удалить мебель
			furnitureRemoveMenu(furnRepo);
			break;
		}
			  
		}



	}
	
	return 0;
}

void furnitureAddMenu(FurnitureRepository& furnRepo) {
	cout << "\nДобавляем позицию мебели" << endl;
	string name = getInputString(NAME_FURNITURE); //название
	string model = getInputString(MODEL_FURNITURE); //модель
	float cost = getInputCostFurniture(); //стоимость

	cout << "\nВведите характеристики мебели" << endl;
	string color = getInputString(COLOR_FURNITURE); //цвет

	short length, width, height;
	int weight;
	makeInputFurnitureProperties(length, width, height, weight); //габариты, вес

	Furniture fur(-1, name, model, cost, color, length, width, height, weight);
	show(fur);
	furnRepo.addFurniture(fur);
	cout << "Объект добавлен!";
}

void furnitureEditMenu(FurnitureRepository& furnRepo) {
	show(furnRepo.getAllFurniture());
	cout << "\nВведите номер строки для редактирования: ";
	long num = getAndCheckInputInteger(furnRepo.getSize());
	Furniture fur = furnRepo.getByNum(num);

	bool menuFlag = true;
	while (menuFlag) {
		show(fur);
		cout << "\tВыберите поле для редактирования таблицы МЕБЕЛЬ: " << endl;
		cout << "1. Название мебели" << endl;
		cout << "2. Модель мебели" << endl;
		cout << "3. Стоимость мебели" << endl;
		cout << "4. Характеристики мебели" << endl;
		cout << "5. Сохранить изменения и выйти" << endl;
		cout << "0. Выйти без сохранения" << endl;
		
		switch (getAndCheckInputInteger()) {
		case 0: {
			cout << "\nИзменения не сохранены!" << endl;
			menuFlag = false;
			break;
		}
		case 1: {
			string name = getInputString(NAME_FURNITURE);
			fur.setName(name);
			break;
		}
		case 2: {
			//модель
			string model = getInputString(MODEL_FURNITURE);
			fur.setModel(model);
			break;
		}
		case 3: {
			//стоимость
			float cost = getInputCostFurniture();
			fur.setCost(cost);
			break;
		}
		case 4: {
			string color = getInputString(COLOR_FURNITURE);
			fur.setColor(color);
			short length, width, height;
			int weight;
			makeInputFurnitureProperties(length, width, height, weight);
			fur.setProperties(color, length, width, height, weight);
			break;
		}
		case 5: {
			furnRepo.updateFurniture(num, fur);
			menuFlag = false;
			cout << "Изменения внесены!";
			break;
		}
		default: {
			cout << "Введите корректный пункт меню!";
		}
		}
	}
}

void furnitureRemoveMenu(FurnitureRepository& furnRepo) {
	show(furnRepo.getAllFurniture());
	cout << "\nВведите номер строки для удаления: ";
	long num = getAndCheckInputInteger(furnRepo.getSize());
	furnRepo.removeFurnitureById(num);
	cout << "\nОбъект под номером " << num << " был удалён";
}


void menu() {
	cout << "\n                   Мебель" << endl;
	cout << "=================== Меню ======================" << endl;
	cout << "0. Выход" << endl;
	cout << "                   МЕБЕЛЬ" << endl;
	cout << "1. Показать" << endl;
	cout << "2. Добавить" << endl;
	cout << "3. Редактировать" << endl;
	cout << "4. Удалить" << endl;
	cout << "                  ЗАКАЗЧИК" << endl;
	cout << "21. Показать" << endl;
	cout << "22. Добавить" << endl;
	cout << "23. Редактировать" << endl;
	cout << "24. Удалить" << endl;
	cout << "                  ДОГОВОР" << endl;
	cout << "31. Показать" << endl;
	cout << "32. Добавить" << endl;
	cout << "33. Редактировать" << endl;
	cout << "34. Удалить" << endl;
	cout << "                  ПРОДАЖА" << endl;
	cout << "41. Показать" << endl;
	cout << "42. Добавить" << endl;
	cout << "43. Редактировать" << endl;
	cout << "44. Удалить" << endl;
}