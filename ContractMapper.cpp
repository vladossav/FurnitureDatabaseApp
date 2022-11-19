#include "ContractMapper.h"
#include "Database.h"
#include <sstream>

void ContractMapper::insert(Contract& obj) {
	char request[512];
	snprintf(request, 512, "insert into contract values (%ld, %ld, '%s', '%s');",
		obj.getNumber(), obj.getCustomerCode(), obj.getRegDate().c_str(), obj.getDoneDate().c_str());
	
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

void ContractMapper::removeById(long id) {
	char request[256];
	snprintf(request, 256, "delete from contract where number = '%ld';", id);
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

void ContractMapper::update(Contract& obj) {
	char request[512];
	snprintf(request, 512, "update contract set customer_code=%ld, reg_date='%s', done_date='%s';",
		obj.getCustomerCode(), obj.getRegDate().c_str(), obj.getDoneDate().c_str());

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

std::vector<Contract> ContractMapper::selectAll() {
	std::vector<Contract> customer;

	try {
		SQLHSTMT statement = Database::getInstance()->execute("select * from contract;");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &num, CONTRACT_NUM_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_LONG, &customer_code, CODE_SIZE, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &reg_date, DATE_SIZE, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &done_date, DATE_SIZE, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Contract obj(num, customer_code, reinterpret_cast<char*>(reg_date), reinterpret_cast<char*>(done_date));
				customer.push_back(obj);
			}
			else {
				if (retcode != SQL_NO_DATA) {
					std::cout << "Не удалось загрузить договоры из БД!\n";
				}
				break;
			}
		}
		SQLFreeStmt(statement, SQL_CLOSE);
	}
	catch (SQLRETURN sqlRet) {
		Database::getInstance()->sqlRetToStr(sqlRet);
	}

	return customer;
}