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
	Furniture* getById(long id);
	Furniture& getByNum(long id);
	long getSize();

	void addFurniture(Furniture one);
	void updateFurniture(long id, Furniture one);
	void removeFurnitureById(long id);

	void editName(std::string newName);
	void editModel(std::string newModel);
	void editCost(float newCost);
	void editProperties(std::string color, short length, short width, short height, int weight);

	void remove(long id);
	

private:
	std::vector<Furniture> repo;
	FurnitureMapper mapper;

	long genId();
	
};