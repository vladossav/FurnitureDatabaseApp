#include "Customer.h"
#include <string>
#include <sstream>

const std::string Customer::TABLE_NAME = "Заказчик";
const std::vector<std::string> Customer::TABLE_COLUMNS = { "Код", "Наименование", "Адрес", "Телефон" };
const std::vector<int> Customer::TABLE_COLUMN_SIZE = { 8, 20, 40, 12 };

;

Customer::Customer(long _code, std::string _name, long long phoneNum, 
	long addr_id, std::string _city, std::string _street, short _num_build) {
	code = _code;
	name = _name;
	address_id = addr_id;
	city = _city;
	street = _street;
	numBuilding = _num_build;
	phone_num = phoneNum;
}

std::vector<std::string> Customer::getStringLine() {
	std::vector<std::string> arr;
	arr.push_back(std::to_string(code));
	arr.push_back(name);
	arr.push_back("г. " + city+", ул. "+ street +" " + std::to_string(numBuilding));
	arr.push_back(std::to_string(phone_num));
	return arr;
}

long Customer::getCode() { return code; }
std::string Customer::getName() { return name; }
long long Customer::getPhoneNum() { return phone_num; }
long Customer::getAddressId() { return address_id; }
std::string Customer::getCity() { return city; }
std::string Customer::getStreet() { return street; }
short Customer::getNumBuilding() { return numBuilding; }

void Customer::setCode(long id) { code = id; }
void Customer::setName(std::string _name) { name = _name; }
void Customer::setPhoneNum(long long _phone) { phone_num = _phone; }
void Customer::setAddress(long addr_id, std::string _city, std::string _street, short num_build) {
	address_id = addr_id;
	city = _city;
	street = _street;
	numBuilding = num_build;
}
