#pragma once
#include "AbstractMapper.h"
#include "Sale.h"

#define ID_SIZE sizeof(long)
#define CONTRACT_NUM_SIZE sizeof(long)
#define AMOUNT_SIZE sizeof(long)
#define NAME_MODEL_SIZE 64

class SaleMapper : public AbstractMapper<Sale> {
public:
	SaleMapper() {}
	~SaleMapper() {}

	void insert(Sale& obj) override;
	void removeById(long id) override;
	void update(Sale& obj) override;
	std::vector<Sale> selectAll() override;
private:
	SQLINTEGER id;
	SQLINTEGER contract_num;
	SQLINTEGER furniture_id;
	SQLCHAR name[NAME_MODEL_SIZE];
	SQLCHAR model[NAME_MODEL_SIZE];
	SQLINTEGER amount;
};