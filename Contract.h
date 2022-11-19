#pragma once
#include <iostream>
#include <vector>

class Contract {
public:
	static const std::string TABLE_NAME;
	static const std::vector<std::string> TABLE_COLUMNS;
	static const std::vector<int> TABLE_COLUMN_SIZE;

	Contract() {}
	Contract(long num, long customerCode, std::string regDate, std::string doneDate);
	~Contract() {}

	long getNumber();
	long getCustomerCode();
	std::string getRegDate();
	std::string getDoneDate();

	void setNumber(long num);
	void setCustomerCode(long code);
	void setRegDate(std::string regDate);
	void setDoneDate(std::string doneDate);

	std::vector<std::string> getStringLine();

private:
	long number;
	long customer_code;
	std::string reg_date;
	std::string done_date;
};