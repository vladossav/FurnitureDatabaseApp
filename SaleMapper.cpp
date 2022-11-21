#include "SaleMapper.h"
#include "Database.h"

void SaleMapper::insert(Sale& obj) {
	char request[512];
	snprintf(request, 512, "insert into sale values (%ld, %ld, %ld, %ld);",
		obj.getId(), obj.getContractNum(), obj.getFurnitureId(), obj.getAmount());

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

void SaleMapper::removeById(long id) {
	char request[64];
	snprintf(request, 64, "delete from sale where id = '%ld';", id);
	try {
		Database::getInstance()->execute(request);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			std::cout << "Ошибка удаления БД";
			return;
		}
		return;
	}
}

void SaleMapper::update(Sale& obj) {
	char request[512];
	snprintf(request, 512, "update sale set contract_num=%ld, furniture_id=%ld, amount=%ld where id = '%ld';",
		obj.getContractNum(), obj.getFurnitureId(), obj.getAmount(),obj.getId());

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

std::vector<Sale> SaleMapper::selectAll() {
	std::vector<Sale> sale;

	try {
		SQLHSTMT statement = Database::getInstance()->
			execute("select s.id,s.contract_num, f.id, f.name, f.model, s.amount from sale s, furniture f where furniture_id =f.id;");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_LONG, &contract_num, CONTRACT_NUM_SIZE, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_LONG, &furniture_id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &name, NAME_MODEL_SIZE, nullptr);
		retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &model, NAME_MODEL_SIZE, nullptr);
		retcode = SQLBindCol(statement, 6, SQL_C_LONG, &amount, AMOUNT_SIZE, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Sale obj(id, contract_num, furniture_id, reinterpret_cast<char*>(name), 
					reinterpret_cast<char*>(model), amount);
				sale.push_back(obj);
			}
			else {
				if (retcode != SQL_NO_DATA) {
					std::cout << "Не удалось загрузить продажи из БД!\n";
				}
				break;
			}
		}
		SQLFreeStmt(statement, SQL_CLOSE);
	}
	catch (SQLRETURN sqlRet) {
		Database::getInstance()->sqlRetToStr(sqlRet);
	}

	return sale;
}