#include "InputHelper.h"
#include "Furniture.h"
#include "FurnitureRepository.h"
#include "Customer.h"
#include "CustomerRepository.h"
#include "Contract.h"
#include "ContractRepository.h"
#include "TablePrinter.h"

using namespace std;
void menu();
void furnitureEditMenu(FurnitureRepository& furnRepo);
void furnitureAddMenu(FurnitureRepository& furnRepo);
void furnitureRemoveMenu(FurnitureRepository& furnRepo);
void customerAddMenu(CustomerRepository& custRepo);
void customerEditMenu(CustomerRepository& custRepo);
void customerRemoveMenu(CustomerRepository& custRepo);
void contractAddMenu(ContractRepository& contractRepo, CustomerRepository& custRepo);
void contractEditMenu(ContractRepository& contractRepo, CustomerRepository& custRepo);
void contractRemoveMenu(ContractRepository& contractRepo);

int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	
	FurnitureRepository furnRepo;
	CustomerRepository customerRepo;
	ContractRepository contractRepo;
	
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
		case 11: { //показать заказчика
			show(customerRepo.getAllCustomers());
			break;
		}
		case 12: { //добавить заказчика
			customerAddMenu(customerRepo);
			break;
		}
		case 13: {//редактировать заказчика
			customerEditMenu(customerRepo);
			break;
		}
		case 14: { //удалить заказчика
			customerRemoveMenu(customerRepo);
			break;
		}
		case 21: { //показать договоры
			show(contractRepo.getAllContracts());
			break;
		}
		case 22: { //добавить договор
			contractAddMenu(contractRepo, customerRepo);
			break;
		}
		case 23: { //редактировать
			contractEditMenu(contractRepo, customerRepo);
			break;
		}
		case 24: { //удалить
			contractRemoveMenu(contractRepo);
			break;
		}
		default: {
			cout << "Введен некорректный пункт меню!";
		}
		}
	}
	return 0;
}



void contractAddMenu(ContractRepository& contractRepo, CustomerRepository& custRepo) {
	cout << "\nДобавление договора" << endl;
	bool flag = true;
	long num, code;
	string regDate, doneDate;
	do {
		cout << "Введите номер договора: ";
		num = getAndCheckInputInteger();
		if (!contractRepo.hasContractNumberCollision(num)) flag = false;
		else cout << "Договор с таким номером уже существует!\n";
	} while (flag); 

	flag = true;
	do {
		cout << "Введите код заказчика: ";
		code = getAndCheckInputInteger();
		if (custRepo.hasCodeCollision(code)) flag = false;
		else cout << "Заказчика с таким кодом не существует!\n";
	} while (flag); 

	cout << "Дата регистрации заказа\n";
	regDate = getInputDate();
	cout << "Дата выполнения заказа\n";
	doneDate = getInputDate();

	Contract contract(num, code, regDate, doneDate);
	show(contract);
	contractRepo.addContract(contract);
}

void contractEditMenu(ContractRepository& contractRepo, CustomerRepository& custRepo) {
	show(contractRepo.getAllContracts());
	cout << "\nВведите номер строки для редактирования: ";
	long num = getAndCheckInputInteger(contractRepo.getSize());
	Contract contract = contractRepo.getByNum(num);

	bool menuFlag = true;
	while (menuFlag) {
		show(contract);
		cout << "\tВыберите поле для редактирования таблицы ДОГОВОРЫ: " << endl;
		cout << "1. Код заказчика" << endl;
		cout << "2. Дата регистрации заказа" << endl;
		cout << "3. Дата выполнения заказа" << endl;
		cout << "4. Сохранить изменения и выйти" << endl;
		cout << "0. Выйти без сохранения" << endl;

		switch (getAndCheckInputInteger()) {
		case 0: {
			cout << "\nИзменения не сохранены!" << endl;
			menuFlag = false;
			break;
		}
		case 1: {
			bool flag = true;
			long code;
			do {
				cout << "Введите код заказчика: ";
				code = getAndCheckInputInteger();
				if (custRepo.hasCodeCollision(code)) flag = false;
				else cout << "Заказчика с таким кодом не существует!\n";
			} while (flag);
			contract.setCustomerCode(code);
			break;
		}
		case 2: {
			cout << "Дата регистрации заказа\n";
			string regDate = getInputDate();
			contract.setRegDate(regDate);
			break;
		}
		case 3: {
			cout << "Дата выполнения заказа\n";
			string doneDate = getInputDate();
			contract.setDoneDate(doneDate);
			break;
		}
		case 4: {
			contractRepo.updateContract(num, contract);
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

void contractRemoveMenu(ContractRepository& contractRepo) {
	show(contractRepo.getAllContracts());
	cout << "\nВведите номер строки для удаления: ";
	long num = getAndCheckInputInteger(contractRepo.getSize());
	contractRepo.removeContractById(num);
	cout << "\nОбъект под номером " << num << " был удалён";
}

void customerAddMenu(CustomerRepository& custRepo) {
	cout << "\nДобавление заказчика" << endl;
	bool flag = true;
	long code;
	do {
		cout << "Введите код заказчика: ";
		code = getAndCheckInputInteger();
		if (!custRepo.hasCodeCollision(code)) flag = false;
	} while (flag); //код заказчика
	 
	string name = getInputString(NAME_CUSTOMER); //название
	cout << "Введите номер телефона: ";
	string phone = std::to_string(getAndCheckInputInteger(89999999999)); //телефон

	string city, street;
	short building;
	makeInputCustomerAddress(city, street, building); //адрес
	
	Customer customer(code, name, phone, custRepo.genAddressId(), city, street, building);
	show(customer);
	custRepo.addCustomer(customer);
	cout << "\nОбъект добавлен!";
}

void customerEditMenu(CustomerRepository& custRepo) {
	show(custRepo.getAllCustomers());
	cout << "\nВведите номер строки для редактирования: ";
	long num = getAndCheckInputInteger(custRepo.getSize());
	Customer customer = custRepo.getByNum(num);

	bool menuFlag = true;
	while (menuFlag) {
		show(customer);
		cout << "\tВыберите поле для редактирования таблицы ЗАКАЗЧИКИ: " << endl;
		cout << "1. Наименование заказчика" << endl;
		cout << "2. Адрес заказчика" << endl;
		cout << "3. Номер телефона заказчика" << endl;
		cout << "4. Сохранить изменения и выйти" << endl;
		cout << "0. Выйти без сохранения" << endl;

		switch (getAndCheckInputInteger()) {
		case 0: {
			cout << "\nИзменения не сохранены!" << endl;
			menuFlag = false;
			break;
		}
		case 1: {
			string name = getInputString(NAME_CUSTOMER);
			customer.setName(name);
			break;
		}
		case 2: {
			string city, street;
			short building;
			makeInputCustomerAddress(city, street, building); 
			customer.setAddress(customer.getAddressId(), city, street, building);
			break;
		}
		case 3: {
			cout << "Введите номер телефона: ";
			string phone = std::to_string(getAndCheckInputInteger(89999999999)); //телефон
			customer.setPhoneNum(phone);
			break;
		}
		case 4: {
			custRepo.updateCustomer(num, customer);
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

void customerRemoveMenu(CustomerRepository& custRepo) {
	show(custRepo.getAllCustomers());
	cout << "\nВведите номер строки для удаления: ";
	long num = getAndCheckInputInteger(custRepo.getSize());
	custRepo.removeCustomerById(num);
	cout << "\nОбъект под номером " << num << " был удалён";
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
			string model = getInputString(MODEL_FURNITURE);
			fur.setModel(model);
			break;
		}
		case 3: {
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
	cout << "\n         База данных офисной мебели" << endl;
	cout << "=================== Меню ======================" << endl;
	cout << "МЕБЕЛЬ\t\tЗАКАЗЧИК\tДОГОВОР\t\tПРОДАЖА" << endl;
	cout << "1. Показать\t11. Показать\t21. Показать\t31. Показать\t0. Выход" << endl;
	cout << "2. Добавить\t12. Добавить\t22. Добавить\t32. Добавить" << endl;
	cout << "3. Править\t13. Править\t23. Править\t33. Править" << endl;
	cout << "4. Удалить\t14. Удалить\t24. Удалить\t34. Удалить" << endl;

	/*cout << "\n                   Мебель" << endl;
	cout << "=================== Меню ======================" << endl;
	cout << "0. Выход" << endl;
	cout << "                   МЕБЕЛЬ" << endl;
	cout << "1. Показать" << endl;
	cout << "2. Добавить" << endl;
	cout << "3. Редактировать" << endl;
	cout << "4. Удалить" << endl;
	cout << "                  ЗАКАЗЧИК" << endl;
	cout << "11. Показать" << endl;
	cout << "12. Добавить" << endl;
	cout << "13. Редактировать" << endl;
	cout << "14. Удалить" << endl;
	cout << "                  ДОГОВОР" << endl;
	cout << "21. Показать" << endl;
	cout << "22. Добавить" << endl;
	cout << "23. Редактировать" << endl;
	cout << "24. Удалить" << endl;
	cout << "                  ПРОДАЖА" << endl;
	cout << "31. Показать" << endl;
	cout << "32. Добавить" << endl;
	cout << "33. Редактировать" << endl;
	cout << "34. Удалить" << endl;*/
}


