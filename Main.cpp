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
			show(customerRepo.getAllCustomers());
			break;
		}
		case 12: { //�������� ���������
			customerAddMenu(customerRepo);
			break;
		}
		case 13: {//������������� ���������
			customerEditMenu(customerRepo);
			break;
		}
		case 14: { //������� ���������
			customerRemoveMenu(customerRepo);
			break;
		}
		case 21: { //�������� ��������
			show(contractRepo.getAllContracts());
			break;
		}
		case 22: { //�������� �������
			contractAddMenu(contractRepo, customerRepo);
			break;
		}
		case 23: { //�������������
			contractEditMenu(contractRepo, customerRepo);
			break;
		}
		case 24: { //�������
			contractRemoveMenu(contractRepo);
			break;
		}
		default: {
			cout << "������ ������������ ����� ����!";
		}
		}
	}
	return 0;
}



void contractAddMenu(ContractRepository& contractRepo, CustomerRepository& custRepo) {
	cout << "\n���������� ��������" << endl;
	bool flag = true;
	long num, code;
	string regDate, doneDate;
	do {
		cout << "������� ����� ��������: ";
		num = getAndCheckInputInteger();
		if (!contractRepo.hasContractNumberCollision(num)) flag = false;
		else cout << "������� � ����� ������� ��� ����������!\n";
	} while (flag); 

	flag = true;
	do {
		cout << "������� ��� ���������: ";
		code = getAndCheckInputInteger();
		if (custRepo.hasCodeCollision(code)) flag = false;
		else cout << "��������� � ����� ����� �� ����������!\n";
	} while (flag); 

	cout << "���� ����������� ������\n";
	regDate = getInputDate();
	cout << "���� ���������� ������\n";
	doneDate = getInputDate();

	Contract contract(num, code, regDate, doneDate);
	show(contract);
	contractRepo.addContract(contract);
}

void contractEditMenu(ContractRepository& contractRepo, CustomerRepository& custRepo) {
	show(contractRepo.getAllContracts());
	cout << "\n������� ����� ������ ��� ��������������: ";
	long num = getAndCheckInputInteger(contractRepo.getSize());
	Contract contract = contractRepo.getByNum(num);

	bool menuFlag = true;
	while (menuFlag) {
		show(contract);
		cout << "\t�������� ���� ��� �������������� ������� ��������: " << endl;
		cout << "1. ��� ���������" << endl;
		cout << "2. ���� ����������� ������" << endl;
		cout << "3. ���� ���������� ������" << endl;
		cout << "4. ��������� ��������� � �����" << endl;
		cout << "0. ����� ��� ����������" << endl;

		switch (getAndCheckInputInteger()) {
		case 0: {
			cout << "\n��������� �� ���������!" << endl;
			menuFlag = false;
			break;
		}
		case 1: {
			bool flag = true;
			long code;
			do {
				cout << "������� ��� ���������: ";
				code = getAndCheckInputInteger();
				if (custRepo.hasCodeCollision(code)) flag = false;
				else cout << "��������� � ����� ����� �� ����������!\n";
			} while (flag);
			contract.setCustomerCode(code);
			break;
		}
		case 2: {
			cout << "���� ����������� ������\n";
			string regDate = getInputDate();
			contract.setRegDate(regDate);
			break;
		}
		case 3: {
			cout << "���� ���������� ������\n";
			string doneDate = getInputDate();
			contract.setDoneDate(doneDate);
			break;
		}
		case 4: {
			contractRepo.updateContract(num, contract);
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

void contractRemoveMenu(ContractRepository& contractRepo) {
	show(contractRepo.getAllContracts());
	cout << "\n������� ����� ������ ��� ��������: ";
	long num = getAndCheckInputInteger(contractRepo.getSize());
	contractRepo.removeContractById(num);
	cout << "\n������ ��� ������� " << num << " ��� �����";
}

void customerAddMenu(CustomerRepository& custRepo) {
	cout << "\n���������� ���������" << endl;
	bool flag = true;
	long code;
	do {
		cout << "������� ��� ���������: ";
		code = getAndCheckInputInteger();
		if (!custRepo.hasCodeCollision(code)) flag = false;
	} while (flag); //��� ���������
	 
	string name = getInputString(NAME_CUSTOMER); //��������
	cout << "������� ����� ��������: ";
	string phone = std::to_string(getAndCheckInputInteger(89999999999)); //�������

	string city, street;
	short building;
	makeInputCustomerAddress(city, street, building); //�����
	
	Customer customer(code, name, phone, custRepo.genAddressId(), city, street, building);
	show(customer);
	custRepo.addCustomer(customer);
	cout << "\n������ ��������!";
}

void customerEditMenu(CustomerRepository& custRepo) {
	show(custRepo.getAllCustomers());
	cout << "\n������� ����� ������ ��� ��������������: ";
	long num = getAndCheckInputInteger(custRepo.getSize());
	Customer customer = custRepo.getByNum(num);

	bool menuFlag = true;
	while (menuFlag) {
		show(customer);
		cout << "\t�������� ���� ��� �������������� ������� ���������: " << endl;
		cout << "1. ������������ ���������" << endl;
		cout << "2. ����� ���������" << endl;
		cout << "3. ����� �������� ���������" << endl;
		cout << "4. ��������� ��������� � �����" << endl;
		cout << "0. ����� ��� ����������" << endl;

		switch (getAndCheckInputInteger()) {
		case 0: {
			cout << "\n��������� �� ���������!" << endl;
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
			cout << "������� ����� ��������: ";
			string phone = std::to_string(getAndCheckInputInteger(89999999999)); //�������
			customer.setPhoneNum(phone);
			break;
		}
		case 4: {
			custRepo.updateCustomer(num, customer);
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

void customerRemoveMenu(CustomerRepository& custRepo) {
	show(custRepo.getAllCustomers());
	cout << "\n������� ����� ������ ��� ��������: ";
	long num = getAndCheckInputInteger(custRepo.getSize());
	custRepo.removeCustomerById(num);
	cout << "\n������ ��� ������� " << num << " ��� �����";
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
	cout << "\n         ���� ������ ������� ������" << endl;
	cout << "=================== ���� ======================" << endl;
	cout << "������\t\t��������\t�������\t\t�������" << endl;
	cout << "1. ��������\t11. ��������\t21. ��������\t31. ��������\t0. �����" << endl;
	cout << "2. ��������\t12. ��������\t22. ��������\t32. ��������" << endl;
	cout << "3. �������\t13. �������\t23. �������\t33. �������" << endl;
	cout << "4. �������\t14. �������\t24. �������\t34. �������" << endl;

	/*cout << "\n                   ������" << endl;
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
	cout << "34. �������" << endl;*/
}


