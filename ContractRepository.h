#pragma once
#include <iostream>
#include "Contract.h"
#include "ContractMapper.h"

class ContractRepository {
public:
	ContractRepository();
	~ContractRepository() {
		repo.clear();
		mapper.~ContractMapper();
	}

	std::vector<Contract> getAllContracts();
	Contract& getByNum(long id);
	long getSize();

	void addContract(Contract one);
	void updateContract(long id, Contract one);
	void removeContractById(long id);
	bool hasContractNumberCollision(long id);
private:
	std::vector<Contract> repo;
	ContractMapper mapper;
};