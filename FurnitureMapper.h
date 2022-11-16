#pragma once
#include "AbstractMapper.h"
#include "Furniture.h"

#define ID_SIZE sizeof(long)
#define NAME_SIZE 64
#define MODEL_SIZE 32
#define COST_SIZE sizeof(float)
#define COLOR_SIZE 32
#define DIMENSION_SIZE sizeof(short)
#define WEIGHT_SIZE sizeof(int)

class FurnitureMapper : public AbstractMapper<Furniture> {
public:
	FurnitureMapper() {}
	~FurnitureMapper() {}
	
	void insert(Furniture& obj) override;
	void removeById(long id) override;
	void update(Furniture& obj) override;
	std::vector<Furniture> selectAll() override;

private:
	SQLINTEGER id;
	SQLCHAR name[NAME_SIZE];
	SQLCHAR model[MODEL_SIZE];
	SQLFLOAT cost;

	SQLCHAR color[COLOR_SIZE];
	SQLSMALLINT length;
	SQLSMALLINT width;
	SQLSMALLINT height;
	SQLINTEGER weight;
};
