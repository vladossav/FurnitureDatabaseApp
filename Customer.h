#pragma once
#include <iostream>

class Customer {
public:
	Customer();
	~Customer();

	long getCode();
	std::string getName();
	std::string getAddress();
	float getPhoneNum();

	void setId(long id);
	void setName(std::string name);
	void setModel(std::string model);
	void setCost(float cost);



private:
	long code;
	std::string name;
	long address_id;
	unsigned long long phone_num;
};