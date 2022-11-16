#include "FurnitureMapper.h"
#include "Database.h"
#include <sstream>

void FurnitureMapper::insert(Furniture& obj) {
	char request[512];
	std::ostringstream costStr;
	costStr << obj.getCost();
	snprintf(request, 512, "insert into furniture values (%ld, '%s', '%s', '%s', '%s', %hd, %hd, %hd, %d);",
	obj.getId(), obj.getName().c_str(), obj.getModel().c_str(), costStr.str().c_str(),
	obj.getColor().c_str(), obj.getLength(), obj.getWidth(), obj.getHeight(), obj.getWeight());
	
	try {
		Database::getInstance()->execute(request);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			std::cout << "Ошибка вставки БД";
			return;
		}
	}
}

void FurnitureMapper::removeById(long id) {
	char request[64];
	snprintf(request, 64, "delete from furniture where id = %ld", id);
	try {
		Database::getInstance()->execute(request);
		return;
	}
	catch (SQLRETURN sqlRet) {
		return;
	}
}

void FurnitureMapper::update(Furniture& obj) {
	char request[512];
	std::ostringstream costStr;
	costStr << obj.getCost();
	snprintf(request, 512, 
		"update furniture set name='%s', model='%s',cost='%s',color='%s', length='%hd',width='%hd',height='%hd',weight='%d' where id = %ld;",
		obj.getName().c_str(), obj.getModel().c_str(), costStr.str().c_str(),
		obj.getColor().c_str(), obj.getLength(), obj.getWidth(), obj.getHeight(), obj.getWeight(), obj.getId());
	try {
		Database::getInstance()->execute(request);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			std::cout << "Данные не обновлены! Ошибка БД";
			return;
		}
	}
}


std::vector<Furniture> FurnitureMapper::selectAll() {
	std::vector<Furniture> furniture;

	try {
		SQLHSTMT statement = Database::getInstance()->execute("select * from furniture;");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_SIZE, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &model, MODEL_SIZE, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_DOUBLE, &cost, COST_SIZE, nullptr);
		retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &color, COLOR_SIZE, nullptr);
		retcode = SQLBindCol(statement, 6, SQL_C_SHORT, &length, DIMENSION_SIZE, nullptr);
		retcode = SQLBindCol(statement, 7, SQL_C_SHORT, &width, DIMENSION_SIZE, nullptr);
		retcode = SQLBindCol(statement, 8, SQL_C_SHORT, &height, DIMENSION_SIZE, nullptr);
		retcode = SQLBindCol(statement, 9, SQL_INTEGER, &weight, WEIGHT_SIZE, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Furniture obj;
				obj.setMainInfo(id, reinterpret_cast<char*>(name), reinterpret_cast<char*>(model), cost);
				obj.setProperties(reinterpret_cast<char*>(color), length, width, height, weight);
				furniture.push_back(obj);
			}
			else {
				if (retcode != SQL_NO_DATA) {
					std::cout << "Не удалось загрузить мебель из БД!\n";
				}
				break;
			}
		}
		SQLFreeStmt(statement, SQL_CLOSE);
	}
	catch (SQLRETURN sqlRet) {
		Database::getInstance()->sqlRetToStr(sqlRet);
	}

	return furniture;
}