//#include <sstream>
//#include <iostream>
//#include "Database.h"
#include "InputHelper.h"
#include "Furniture.h"
#include "FurnitureRepository.h"
#include "Customer.h"
#include "CustomerRepository.h"
#include "TablePrinter.h"

using namespace std;
void menu();
void furnitureEditMenu(FurnitureRepository& furnRepo);
void furnitureAddMenu(FurnitureRepository& furnRepo);
void furnitureRemoveMenu(FurnitureRepository& furnRepo);
void customerAddMenu(CustomerRepository& custRepo);


int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	
	FurnitureRepository furnRepo;
	CustomerRepository customerRepo;
	
	bool menuFlag = true;
	while (menuFlag) {
		menu();
		
		switch (getAndCheckInputInteger()) {
		case 0: {
			menuFlag = false;
			break;
		}
		case 1: { //�������� ������
			show(furnRepo.getAllFurniture());
			break;
		}
		case 2: { //�������� ������
			furnitureAddMenu(furnRepo);
			break;
		}
		case 3: { //������������� ������
			furnitureEditMenu(furnRepo);
			break;
		}
		case 4: { //������� ������
			furnitureRemoveMenu(furnRepo);
			break;
		}
		case 11: { //�������� ���������
			//show(customerRepo.getAllCustomers());
			
			break;
		}
		case 12: { //�������� ���������
			customerAddMenu(customerRepo);
			break;
		}
		case 13: {//������������� ���������
			break;
		}
		case 14: { //������� ���������
			break;
		}
		}



	}
	
	return 0;
}

void customerAddMenu(CustomerRepository& custRepo) {
	cout << "\n��������� ������� ���������" << endl;
	cout << "������� ��� ���������: ";
	bool flag = true;
	long code;
	do {
		code = getAndCheckInputInteger();
		if (!custRepo.checkCodeCollision(code)) flag = false;
	} while (flag);
	 //��� ���������
	 
	string name = getInputString(NAME_CUSTOMER); //��������
	cout << "������� ����� ��������: ";
	long long phone = getAndCheckInputInteger(89999999999); //�������

	string city, street;
	short building;
	makeInputCustomerAddress(city, street, building); //�����

	Customer customer(code, name, phone, -1, city, street, building);
	show(customer);
	custRepo.addCustomer(customer);
	cout << "\n������ ��������!";
}

void furnitureAddMenu(FurnitureRepository& furnRepo) {
	cout << "\n��������� ������� ������" << endl;
	string name = getInputString(NAME_FURNITURE); //��������
	string model = getInputString(MODEL_FURNITURE); //������
	float cost = getInputCostFurniture(); //���������

	cout << "\n������� �������������� ������" << endl;
	string color = getInputString(COLOR_FURNITURE); //����

	short length, width, height;
	int weight;
	makeInputFurnitureProperties(length, width, height, weight); //��������, ���

	Furniture fur(-1, name, model, cost, color, length, width, height, weight);
	show(fur);

	furnRepo.addFurniture(fur);
	cout << "������ ��������!";
}

void furnitureEditMenu(FurnitureRepository& furnRepo) {
	show(furnRepo.getAllFurniture());
	cout << "\n������� ����� ������ ��� ��������������: ";
	long num = getAndCheckInputInteger(furnRepo.getSize());
	Furniture fur = furnRepo.getByNum(num);

	bool menuFlag = true;
	while (menuFlag) {
		show(fur);
		cout << "\t�������� ���� ��� �������������� ������� ������: " << endl;
		cout << "1. �������� ������" << endl;
		cout << "2. ������ ������" << endl;
		cout << "3. ��������� ������" << endl;
		cout << "4. �������������� ������" << endl;
		cout << "5. ��������� ��������� � �����" << endl;
		cout << "0. ����� ��� ����������" << endl;
		
		switch (getAndCheckInputInteger()) {
		case 0: {
			cout << "\n��������� �� ���������!" << endl;
			menuFlag = false;
			break;
		}
		case 1: {
			string name = getInputString(NAME_FURNITURE);
			fur.setName(name);
			break;
		}
		case 2: {
			//������
			string model = getInputString(MODEL_FURNITURE);
			fur.setModel(model);
			break;
		}
		case 3: {
			//���������
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
			cout << "��������� �������!";
			break;
		}
		default: {
			cout << "������� ���������� ����� ����!";
		}
		}
	}
}

void furnitureRemoveMenu(FurnitureRepository& furnRepo) {
	show(furnRepo.getAllFurniture());
	cout << "\n������� ����� ������ ��� ��������: ";
	long num = getAndCheckInputInteger(furnRepo.getSize());
	furnRepo.removeFurnitureById(num);
	cout << "\n������ ��� ������� " << num << " ��� �����";
}


void menu() {
	cout << "\n                   ������" << endl;
	cout << "=================== ���� ======================" << endl;
	cout << "0. �����" << endl;
	cout << "                   ������" << endl;
	cout << "1. ��������" << endl;
	cout << "2. ��������" << endl;
	cout << "3. �������������" << endl;
	cout << "4. �������" << endl;
	cout << "                  ��������" << endl;
	cout << "11. ��������" << endl;
	cout << "12. ��������" << endl;
	cout << "13. �������������" << endl;
	cout << "14. �������" << endl;
	cout << "                  �������" << endl;
	cout << "21. ��������" << endl;
	cout << "22. ��������" << endl;
	cout << "23. �������������" << endl;
	cout << "24. �������" << endl;
	cout << "                  �������" << endl;
	cout << "31. ��������" << endl;
	cout << "32. ��������" << endl;
	cout << "33. �������������" << endl;
	cout << "34. �������" << endl;
}


