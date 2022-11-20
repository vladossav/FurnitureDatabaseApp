#include "SaleRepository.h"

SaleRepository::SaleRepository() {
	getAllSales();
}

void SaleRepository::addSale(Sale one) {
	repo.push_back(one);
	mapper.insert(one);
}

void SaleRepository::updateSale(long id, Sale one) {
	repo[id] = one;
	mapper.update(one);
}

void SaleRepository::removeSaleById(long id) {
	mapper.removeById(repo[id].getId());
	repo.erase(repo.begin() + id);
}

long SaleRepository::genId() {
	bool flag = false;
	long num;
	do {
		num = (long)rand();
		for (Sale one : repo) {
			if (one.getId() == num) {
				flag = true;
				break;
			}
		}
	} while (flag);
	return num;
}

std::vector<Sale> SaleRepository::getAllSales() {
	return repo = mapper.selectAll();
}

Sale& SaleRepository::getByNum(long id) {
	return repo[id];
}

long SaleRepository::getSize() {
	return repo.size();
}