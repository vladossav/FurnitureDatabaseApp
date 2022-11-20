#include "ContractRepository.h"

ContractRepository::ContractRepository() {
	getAllContracts();
}

void ContractRepository::addContract(Contract one) {
	repo.push_back(one);
	mapper.insert(one);
}

void ContractRepository::updateContract(long id, Contract one) {
	repo[id] = one;
	mapper.update(one);
}

void ContractRepository::removeContractById(long id) {
	mapper.removeById(repo[id].getNumber());
	repo.erase(repo.begin() + id);
}

bool ContractRepository::hasContractNumberCollision(long id) {
	bool flag = false;
	for (Contract one : repo) {
		if (one.getNumber() == id) {
			flag = true;
			break;
		}
	}
	return flag;
}

std::vector<Contract> ContractRepository::getAllContracts() {
	return repo = mapper.selectAll();
}

Contract& ContractRepository::getByNum(long id) {
	return repo[id];
}

long ContractRepository::getSize() {
	return repo.size();
}