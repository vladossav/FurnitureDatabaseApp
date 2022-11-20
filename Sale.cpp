#include "Sale.h"
#include <string>

const std::string Sale::TABLE_NAME = "Продажи";
const std::vector<std::string> Sale::TABLE_COLUMNS = { "№ контракта", "Название", "Модель", "Кол-во" };
const std::vector<int> Sale::TABLE_COLUMN_SIZE = { 12, 25, 25, 8 };

Sale::Sale(long _id, long _contractNum, long furn_id, std::string _name, std::string _model, int _amount) {
	id = _id;
	contractNum = _contractNum;
	name = _name;
	model = _model;
	amount = _amount;
	furniture_id = furn_id;
}

std::vector<std::string> Sale::getStringLine() {
	std::vector<std::string> arr;
	arr.push_back(std::to_string(contractNum));
	arr.push_back(name);
	arr.push_back(model);
	arr.push_back(std::to_string(amount));
	return arr;
}

long Sale::getId() { return id; }
long Sale::getFurnitureId() { return furniture_id; }
long Sale::getContractNum() { return contractNum; }
std::string Sale::getName() { return name; }
std::string Sale::getModel() { return model; }
int Sale::getAmount() { return amount; }

void Sale::setId(long _id) { id = _id; }
void Sale::setFurnitureId(long _id) { furniture_id = _id; }
void Sale::setContractNum(long num) { contractNum = num; }
void Sale::setName(std::string _name) { name = _name; }
void Sale::setModel(std::string _model) { model = _model; }
void Sale::setAmount(int _amount) { amount = _amount; }

void Sale::setFurniture(long _id, std::string _name, std::string _model) {
	furniture_id = _id;
	name = _name;
	model = _model;
}