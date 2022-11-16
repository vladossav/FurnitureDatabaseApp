#include "FurnitureRepository.h"

FurnitureRepository::FurnitureRepository() {
	repo = std::vector<Furniture>();
	mapper = FurnitureMapper();
}

void FurnitureRepository::addFurniture(Furniture one) {
	one.setId(genId());
	repo.push_back(one);
	mapper.insert(one);
}

void FurnitureRepository::updateFurniture(long id, Furniture one) {
	repo[id] = one;
	mapper.update(one);
}

void FurnitureRepository::removeFurnitureById(long id) {
	mapper.removeById(repo[id].getId());
	repo.erase(repo.begin() + id);
}

long FurnitureRepository::genId() {
	bool flag = false;
	long num;
	do {
		num = rand();
		for (Furniture one : repo) {
			if (one.getId() == num) {
				flag = true;
				break;
			}
		}
	} while (flag);
	return num;
}

std::vector<Furniture> FurnitureRepository::getAllFurniture() {
	return repo = mapper.selectAll();
}

Furniture& FurnitureRepository::getByNum(long id) {
	return repo[id];
}

long FurnitureRepository::getSize() {
	return repo.size();
}