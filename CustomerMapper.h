#pragma once

#include "AbstractMapper.h"
#include "Customer.h"

#define CODE_SIZE sizeof(long)
#define NAME_SIZE 64
#define PHONE_SIZE 16
#define STREET_SIZE 32
#define CITY_SIZE 32
#define BUILDING_SIZE sizeof(short)
#define ADDRESS_ID_SIZE sizeof(long)

class CustomerMapper : public AbstractMapper<Customer> {
public:
	CustomerMapper() {}
	~CustomerMapper() {}

	void insert(Customer& obj) override;
	void removeById(long id) override;
	void update(Customer& obj) override;
	std::vector<Customer> selectAll() override;

private:
	SQLINTEGER code;
	SQLCHAR name[NAME_SIZE];
	SQLCHAR phone[PHONE_SIZE];

	SQLINTEGER address_id;
	SQLCHAR city[CITY_SIZE];
	SQLCHAR street[STREET_SIZE];
	SQLSMALLINT num_building;
};
