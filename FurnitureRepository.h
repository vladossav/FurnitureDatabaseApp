#pragma once
#include <iostream>
#include "Furniture.h"
#include "FurnitureMapper.h"


class FurnitureRepository {
public:
	FurnitureRepository();
	~FurnitureRepository() {
		repo.clear();
		mapper.~FurnitureMapper();
	}

	std::vector<Furniture> getAllFurniture();
	Furniture& getByNum(long id);
	long getSize();

	void addFurniture(Furniture one);
	void updateFurniture(long id, Furniture one);
	void removeFurnitureById(long id);
private:
	std::vector<Furniture> repo;
	FurnitureMapper mapper;
	long genId();
};