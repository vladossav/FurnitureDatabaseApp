#pragma once
#include <iostream>
#include <vector>


class Customer {
public:
	static const std::string TABLE_NAME;
	static const std::vector<std::string> TABLE_COLUMNS;
	static const std::vector<int> TABLE_COLUMN_SIZE;

	Customer() {}
	Customer(long _code, std::string _name, std::string phoneNum, long addr_id, std::string _city, std::string _street, short _num_build);
	~Customer() {}

	long getCode();
	std::string getName();
	std::string getPhoneNum();
	long getAddressId();
	std::string getCity();
	std::string getStreet();
	short getNumBuilding();

	void setCode(long id);
	void setName(std::string name);
	void setAddress(long address_id, std::string _city, std::string _street, short _num_build);
	void setPhoneNum(std::string phone);

	std::vector<std::string> getStringLine();

private:
	long code;
	std::string name;
	long address_id;
	std::string city;
	std::string street;
	short numBuilding;
	std::string phone_num;
};