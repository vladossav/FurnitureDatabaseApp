#pragma once
#include <iostream>
#include <vector>

class Furniture {
public:
	static const std::string TABLE_NAME;
	static const std::vector<std::string> TABLE_COLUMNS;
	static const std::vector<int> TABLE_COLUMN_SIZE;

	Furniture() {}
	Furniture(long _id, std::string _name, std::string _model, float _cost,
		std::string _color, short _len, short _width, short _height, int _weight);
	~Furniture() {}
	Furniture& operator= (Furniture other);

	long getId();
	std::string getName();
	std::string getModel();
	float getCost();
	std::string getColor();
	short getLength();
	short getWidth();
	short getHeight();
	int getWeight();

	void setId(long _id);
	void setName(std::string _name);
	void setModel(std::string _model);
	void setCost(float _cost);
	void setColor(std::string _color);
	void setLength(short _len);
	void setWidth(short _width);
	void setHeight(short _height);
	void setWeight(int _weight);
	void setMainInfo(long _id, std::string _name, std::string _model, float _cost);
	void setProperties(std::string _color, short _len, short _width, short _height, int _weight);

	std::vector<std::string> getStringLine();
private:
	long id;
	std::string name;
	std::string model;
	float cost;
	std::string color;
	short length;
	short width;
	short height;
	int weight;
};