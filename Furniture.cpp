#include "Furniture.h"
#include <string>
#include <sstream>

const std::string Furniture::TABLE_NAME = "Мебель";
const std::vector<std::string> Furniture::TABLE_COLUMNS = { "Название", "Модель", "Стоимость", "Цвет", "Длина", "Ширина", "Высота", "Вес" };
const std::vector<int> Furniture::TABLE_COLUMN_SIZE = { 22, 15, 10, 20, 7, 7, 7, 10 };

Furniture::Furniture(long _id, std::string _name, std::string _model, float _cost, std::string _color, short _len, short _width, short _height, int _weight)
{
	id = _id;
	name = _name;
	model = _model;
	cost = _cost;
	color = _color;
	length = _len;
	width = _width;
	height = _height;
	weight = _weight;
}

Furniture& Furniture::operator= (Furniture other) {
	this->id = other.getId();
	this->name = other.getName();
	this->model = other.getModel();
	this->cost = other.getCost();
	this->color = other.getColor();
	this->length = other.getLength();
	this->width = other.getWidth();
	this->height = other.getHeight();
	this->weight = other.getWeight();
	return *this;
}

void Furniture::setMainInfo(long _id, std::string _name, std::string _model, float _cost) {
	id = _id;
	name = _name;
	model = _model;
	cost = _cost;
}
void Furniture::setProperties(std::string _color, short _len, short _width, short _height, int _weight) {
	color = _color;
	length = _len;
	width = _width;
	height = _height;
	weight = _weight;
}

void Furniture::setId(long _id) {id = _id;}
void Furniture::setName(std::string _name) {name = _name;}
void Furniture::setModel(std::string _model) { model = _model; }
void Furniture::setCost(float _cost) { cost = _cost; }
void Furniture::setColor(std::string _color) { color = _color; }
void Furniture::setLength(short _len) { length = _len; }
void Furniture::setWidth(short _width) { width = _width; }
void Furniture::setHeight(short _height) { height = _height; }
void Furniture::setWeight(int _weight) { weight = _weight; }


long Furniture::getId() { return id; }
std::string Furniture::getName() {return name;}
std::string Furniture::getModel() {return model;}
float Furniture::getCost() {return cost;}
std::string Furniture::getColor() {return color;}
short Furniture::getLength() {return length;}
short Furniture::getWidth() {return width;}
short Furniture::getHeight() {return height;}
int Furniture::getWeight() {return weight;}


std::vector<std::string> Furniture::getStringLine() {
	std::vector<std::string> arr;
	arr.push_back(name);
	arr.push_back(model);
	std::ostringstream os;
	os << cost;
	arr.push_back(os.str());
	arr.push_back(color);
	arr.push_back(std::to_string(length));
	arr.push_back(std::to_string(width));
	arr.push_back(std::to_string(height));
	arr.push_back(std::to_string(weight));
	return arr;
}

