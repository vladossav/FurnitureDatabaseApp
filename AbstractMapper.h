#pragma once
#include "Database.h"
#include <vector>

template <class T>
class AbstractMapper {
public:
	virtual void insert(T& obj) = 0;
	virtual void removeById(long id) = 0;
	virtual void update(T& obj) = 0;
	virtual std::vector<T> selectAll() = 0;
protected:
	Database* db = Database::getInstance();
};