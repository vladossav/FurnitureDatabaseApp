#pragma once
#include <windows.h> 
#include <odbcinst.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <iostream>

class Database {
public:
	const SQLHSTMT& execute(std::string sqlStr);
	std::string sqlRetToStr(SQLRETURN status);

	Database(Database& other) = delete;
	void operator=(const Database&) = delete;

	static Database* getInstance();
private:
	Database();
	~Database();
	static Database* instance;
	SQLHENV hEnv = SQL_NULL_HENV;
	SQLHDBC hConn = SQL_NULL_HDBC;
	SQLHSTMT hStat = SQL_NULL_HSTMT;
	void connect();
	void createTables();
};