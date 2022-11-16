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
	std::cout << "Successful connection to database!" << std::endl;
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
	// создание таблиц студентов
	SQLRETURN status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"create table if not exist student (\
		id integer,\
		name varchar(255),\
		faculty varchar(10),\
		stud_group varchar(10),\
		primary key(id)\
		);",
		SQL_NTS);
	// создание таблиц преподавателей
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"create table if not exist mark (\
		create table if not exist teacher (\
		id integer,\
		name varchar(255),\
		degree varchar(64),\
		title varchar(64),\
		department varchar(64),\
		telephone varchar(20),\
		email varchar(64),\
		primary key(id)\
		);",
		SQL_NTS);
	// создание таблиц оценок
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"create table if not exist mark (\
		id_stud integer references student(id) unique,\
		exam_mark integer,\
		grad_mark integer\
		);",
		SQL_NTS);
	// создание таблиц тем
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"create table if not exist theme (\
		id_stud integer references student(id),\
		id_tchr integer references teacher(id),\
		name varchar(256)\
		);",
		SQL_NTS);
}

const SQLHSTMT& Database::execute(std::string sqlStr) {
	SQLRETURN status = SQLExecDirect(hStat, (SQLWCHAR*)str2wchar(sqlStr),
		SQL_NTS);
	if (status == SQL_SUCCESS) {
		std::cout << sqlRetToStr(status) << std::endl;
		return hStat;
	}
	else {
		//std::cout << sqlRetToStr(status) << std::endl;
		throw status;
	}
	return nullptr;
}