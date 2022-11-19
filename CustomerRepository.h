#pragma once
#include <iostream>
#include "Customer.h"
#include "CustomerMapper.h"

class CustomerRepository {
public:
	CustomerRepository();
	~CustomerRepository() {
		repo.clear();
		mapper.~CustomerMapper();
	}

	std::vector<Customer> getAllCustomers();
	Customer* getById(long id);
	Customer& getByNum(long id);
	long getSize();

	void addCustomer(Customer one);
	void updateCustomer(long id, Customer one);
	void removeCustomerById(long id);
	bool hasCodeCollision(long id);
	long genAddressId();
private:
	std::vector<Customer> repo;
	CustomerMapper mapper;
};