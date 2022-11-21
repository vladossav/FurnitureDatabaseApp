#pragma once
#include <iostream>
#include "Sale.h"
#include "SaleMapper.h"

class SaleRepository {
public:
	SaleRepository();
	~SaleRepository() {
		repo.clear();
		mapper.~SaleMapper();
	}

	std::vector<Sale> getAllSales();
	Sale& getByNum(long id);
	long getSize();
	long genId();

	void addSale(Sale one);
	void updateSale(long id, Sale one);
	void removeSaleById(long id);
	
private:
	std::vector<Sale> repo;
	SaleMapper mapper;
};