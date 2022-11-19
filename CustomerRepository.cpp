#include "CustomerRepository.h"

CustomerRepository::CustomerRepository() {
	repo = std::vector<Customer>();
	mapper = CustomerMapper();
}

void CustomerRepository::addCustomer(Customer one) {
	repo.push_back(one);
	mapper.insert(one);
}

void CustomerRepository::updateCustomer(long id, Customer one) {
	repo[id] = one;
	mapper.update(one);
}

void CustomerRepository::removeCustomerById(long id) {
	mapper.removeById(repo[id].getCode());
	repo.erase(repo.begin() + id);
}

long CustomerRepository::genAddressId() {
	bool flag = false;
	long num;
	do {
		num = (long)rand();
		for (Customer one : repo) {
			if (one.getAddressId() == num) {
				flag = true;
				break;
			}
		}
	} while (flag);
	return num;
}

bool CustomerRepository::checkCodeCollision(long id) {
	bool flag = false;
	for (Customer one : repo) {
		if (one.getCode() == id) {
			flag = true;
			break;
		}
	}
	return flag;
}

std::vector<Customer> CustomerRepository::getAllCustomers() {
	return repo = mapper.selectAll();
}

Customer& CustomerRepository::getByNum(long id) {
	return repo[id];
}

long CustomerRepository::getSize() {
	return repo.size();
}