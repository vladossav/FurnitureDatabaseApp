#define _CRT_SECURE_NO_WARNINGS
#include "Database.h"

void Database::connect() {
	try {
		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) == SQL_ERROR)
			throw std::exception("Error: Unable to allocate an environment handle");
		if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) == SQL_ERROR)
			throw std::exception("Error: Unable to set an environment variable");
		if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hConn) == SQL_ERROR)
			throw std::exception("Error: Unable to allocate an connection handle");
		if (SQLConnect(hConn, (SQLWCHAR*)L"PostgreSQL35W", SQL_NTS,
			(SQLWCHAR*)L"vlad", SQL_NTS, (SQLWCHAR*)L"123", SQL_NTS) == SQL_ERROR)
			throw std::exception("Error: Unable to connect to database");
		if (SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStat) == SQL_ERROR)
			throw std::exception("Error: Unable to allocate stmt handle");
		createTables();
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		exit(1);
	}
}

Database::Database() {
	connect();
}

Database* Database::instance = nullptr;

Database::~Database() {
	if (hStat != SQL_NULL_HSTMT)
		SQLFreeHandle(SQL_HANDLE_STMT, hStat);
	if (hConn != SQL_NULL_HDBC) {
		SQLDisconnect(this->hConn);
		SQLFreeHandle(SQL_HANDLE_DBC, hConn);
	}
	if (hEnv != SQL_NULL_HENV)
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}


const wchar_t* str2wchar(const std::string& str) {
	const char* pstr = str.c_str();
	int bufLen = sizeof(char) * str.length() + 1;
	wchar_t* pRes = new wchar_t[bufLen];
	mbstowcs(pRes, pstr, bufLen);
	return pRes;
}

std::string Database::sqlRetToStr(SQLRETURN status) {
	switch (status)
	{
	case SQL_SUCCESS_WITH_INFO:
		return "SQL_SUCCESS_WITH_INFO";
		break;
	case SQL_NEED_DATA:
		return "SQL_NEED_DATA";
		break;
	case SQL_STILL_EXECUTING:
		return "SQL_STILL_EXECUTING";
		break;
	case SQL_ERROR:
		return "SQL_ERROR";
		break;
	case SQL_NO_DATA:
		return "SQL_NO_DATA";
		break;
	case SQL_INVALID_HANDLE:
		return "SQL_INVALID_HANDLE";
		break;
	case SQL_SUCCESS:
		return "SQL_SUCCESS";
		break;
	default:
		return "return value not found";
		break;
	}
}

Database* Database::getInstance()
{
	if (instance == nullptr) {
		instance = new Database();
	}
	return instance;
}

void Database::createTables() {
	SQLRETURN status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS address (\
			id integer,\
			city character varying,\
			street character varying,\
			n_build smallint,\
			CONSTRAINT address_pkey PRIMARY KEY(id)\
			); ",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS customer (\
			code integer,\
			name character varying,\
			address_id integer,\
			phone_num character varying,\
			CONSTRAINT customer_pkey PRIMARY KEY(code),\
			CONSTRAINT customer_address_id_fkey FOREIGN KEY(address_id)\
			REFERENCES address(id) MATCH SIMPLE\
			ON UPDATE NO ACTION\
			ON DELETE CASCADE\
			NOT VALID\
		);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS contract (\
			number integer,\
			customer_code integer,\
			reg_date character varying,\
			done_date character varying,\
			CONSTRAINT contract_pkey PRIMARY KEY(number),\
			CONSTRAINT contract_customer_code_fkey FOREIGN KEY(customer_code)\
			REFERENCES customer(code) MATCH SIMPLE\
			ON UPDATE NO ACTION\
			ON DELETE CASCADE\
			NOT VALID\
			);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS furniture(\
			id integer,\
			name character varying,\
			model character varying,\
			cost double precision,\
			color character varying,\
			length smallint,\
			width smallint,\
			height smallint,\
			weight integer,\
			CONSTRAINT furniture_pkey PRIMARY KEY(id)\
			);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS sale(\
			id integer,\
			contract_num integer,\
			furniture_id integer,\
			amount integer,\
			CONSTRAINT sale_pkey PRIMARY KEY(id),\
			CONSTRAINT sale_contract_num_fkey FOREIGN KEY(contract_num)\
			REFERENCES contract(number) MATCH SIMPLE\
			ON UPDATE NO ACTION\
			ON DELETE CASCADE\
			NOT VALID,\
			CONSTRAINT sale_furniture_id_fkey FOREIGN KEY(furniture_id)\
			REFERENCES furniture(id) MATCH SIMPLE\
			ON UPDATE NO ACTION\
			ON DELETE CASCADE\
			NOT VALID\
			);",
		SQL_NTS);
}

const SQLHSTMT& Database::execute(std::string sqlStr) {
	SQLRETURN status = SQLExecDirect(hStat, (SQLWCHAR*)str2wchar(sqlStr),
		SQL_NTS);
	if (status == SQL_SUCCESS) {
		//std::cout << sqlRetToStr(status) << std::endl;
		return hStat;
	}
	else {
		std::cout << sqlRetToStr(status) << std::endl;
		throw status;
	}
	return nullptr;
}