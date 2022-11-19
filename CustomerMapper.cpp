#include "CustomerMapper.h"
#include "Database.h"
#include <sstream>

void CustomerMapper::insert(Customer& obj) {
	char request1[512];
	snprintf(request1, 512, "insert into address values (%ld, '%s', '%s', %hd);",
		obj.getAddressId(), obj.getCity().c_str(), obj.getStreet().c_str(), obj.getNumBuilding());
	char request2[512];
	snprintf(request2, 512, "insert into customer values (%ld, '%s', %ld, '%s');",
		obj.getCode(), obj.getName().c_str(), obj.getAddressId(), obj.getPhoneNum().c_str());
	std::cout << request2;

	try {
		Database::getInstance()->execute(request1);
		Database::getInstance()->execute(request2);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			std::cout << "Ошибка вставки БД";
			return;
		}
	}
}

void CustomerMapper::removeById(long id) {
	char request[256];
	snprintf(request, 256, "delete from address using customer where code = '%ld' and id = address_id;", id);
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

void CustomerMapper::update(Customer& obj) {
	char request1[512];
	snprintf(request1, 512, "update address set city='%s', street='%s', n_build=%hd where id = %ld;",
		obj.getCity().c_str(), obj.getStreet().c_str(), obj.getNumBuilding(), obj.getAddressId());
	char request2[512];
	snprintf(request2, 512, "update customer set name='%s', phone_num='%s' where code = %ld;",
		obj.getName().c_str(), obj.getPhoneNum().c_str(), obj.getCode());
	try {
		Database::getInstance()->execute(request1);
		Database::getInstance()->execute(request2);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			std::cout << "Данные не обновлены! Ошибка БД";
			return;
		}
	}
}

std::vector<Customer> CustomerMapper::selectAll() {
	std::vector<Customer> customer;

	try {
		SQLHSTMT statement = Database::getInstance()->execute("select * from customer, address where address_id = id;");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &code, CODE_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_SIZE, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_LONG, &address_id, ADDRESS_ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &phone, PHONE_SIZE, nullptr);
		retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &city, CITY_SIZE, nullptr);
		retcode = SQLBindCol(statement, 7, SQL_C_CHAR, &street, STREET_SIZE, nullptr);
		retcode = SQLBindCol(statement, 8, SQL_C_SHORT, &num_building, BUILDING_SIZE, nullptr);
		
		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Customer obj;
				obj.setCode(code);
				obj.setName(reinterpret_cast<char*>(name));
				obj.setPhoneNum(reinterpret_cast<char*>(phone));
				obj.setAddress(address_id, reinterpret_cast<char*>(city), reinterpret_cast<char*>(street), num_building);
				customer.push_back(obj);
			}
			else {
				if (retcode != SQL_NO_DATA) {
					std::cout << "Не удалось загрузить заказчиков из БД!\n";
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