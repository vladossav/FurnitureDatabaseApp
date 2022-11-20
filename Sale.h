#pragma once
#include <iostream>
#include <vector>

class Sale {
public:
	static const std::string TABLE_NAME;
	static const std::vector<std::string> TABLE_COLUMNS;
	static const std::vector<int> TABLE_COLUMN_SIZE;

	Sale() {}
	Sale(long _id, long _contractNum, long furn_id, std::string _name, std::string _model, int _amount);
	~Sale() {}

	long getId();
	long getFurnitureId();
	long getContractNum();
	std::string getName();
	std::string getModel();
	int getAmount();

	void setId(long _id);
	void setFurnitureId(long _id);
	void setFurniture(long _id, std::string _name, std::string _model);
	void setContractNum(long num);
	void setName(std::string _name);
	void setModel(std::string _model);
	void setAmount(int _amount);

	std::vector<std::string> getStringLine();

private:
	long id;
	long contractNum;
	long furniture_id;
	std::string name;
	std::string model;
	int amount;
};