#pragma once
#include "AbstractMapper.h"
#include "Contract.h"

#define CODE_SIZE sizeof(long)
#define CONTRACT_NUM_SIZE sizeof(long)
#define DATE_SIZE 32

class ContractMapper : public AbstractMapper<Contract> {
public:
	ContractMapper() {}
	~ContractMapper() {}

	void insert(Contract& obj) override;
	void removeById(long id) override;
	void update(Contract& obj) override;
	std::vector<Contract> selectAll() override;
private:
	SQLINTEGER num;
	SQLINTEGER customer_code;
	SQLCHAR reg_date[DATE_SIZE];
	SQLCHAR done_date[DATE_SIZE];
};