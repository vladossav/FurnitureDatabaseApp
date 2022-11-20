#include "Contract.h"
#include <string>

const std::string Contract::TABLE_NAME = "Договор";
const std::vector<std::string> Contract::TABLE_COLUMNS = { "№", "Код заказчика", "Дата оформления", "Дата исполнения" };
const std::vector<int> Contract::TABLE_COLUMN_SIZE = { 8, 15, 20, 20 };

Contract::Contract(long num, long customerCode, std::string regDate, std::string doneDate) {
	number = num;
	customer_code = customerCode;
	reg_date = regDate;
	done_date = doneDate;
}

std::vector<std::string> Contract::getStringLine() {
	std::vector<std::string> arr;
	arr.push_back(std::to_string(number));
	arr.push_back(std::to_string(customer_code));
	arr.push_back(reg_date);
	arr.push_back(done_date);
	return arr;
}

long Contract::getNumber() { return number; }
long Contract::getCustomerCode() { return customer_code; }
std::string Contract::getRegDate() { return reg_date; }
std::string Contract::getDoneDate() { return done_date; }

void Contract::setNumber(long num) { number = num; }
void Contract::setCustomerCode(long code) { customer_code = code; }
void Contract::setRegDate(std::string regDate) { reg_date = regDate; }
void Contract::setDoneDate(std::string doneDate) { done_date = doneDate; }
