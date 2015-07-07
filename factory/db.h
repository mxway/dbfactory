#ifndef DB_INCLUDE_H
#define DB_INCLUDE_H
#include <iostream>
#include <string>
#include <mysql.h>
#include "sqlite3.h"
#include "smartptr.h"
using namespace std;
using namespace commutil;

class DBUtil
{
public:
	//初始化数据库连接
	virtual void conn()=0;
	//打开数据库连接
	virtual void open(string userName,string pass,string database)=0;
	//执行SQL查询语句
	virtual void executeQuery()=0;
	//执行insert,update,delete更新数据库的语句
	virtual void executeUpdate() = 0;
	//关闭数据库连接，是否有必要
	virtual void closeConn()=0;
	virtual ~DBUtil(){}
};

/****
*
* 操作mysql数据库的类
*
****/
class MySQLUtil:public DBUtil
{
public:
	virtual void conn();
	virtual void open(string userName,string pass,string database);
	virtual void executeQuery();
	virtual void executeUpdate();
	virtual void closeConn();
	~MySQLUtil();
private:
	MYSQL	*m_conn;
};

//操作mssql
class MsSQLUtil:public DBUtil
{
public:
	virtual void conn();
	virtual void open(string userName,string pass,string database);
	virtual void executeQuery();
	virtual void executeUpdate();
	virtual void closeConn();
};

//操作oracle
class OracleUtil:public DBUtil
{
public:
	virtual void conn();
	virtual void open(string userName,string pass,string database);
	virtual void executeQuery();
	virtual void executeUpdate();
	virtual void closeConn();
};

//操作sqlite
class SQLiteUtil:public DBUtil
{
public:
	~SQLiteUtil();
	virtual void conn();
	virtual void open(string userName,string pass,string database);
	virtual void executeQuery();
	virtual void executeUpdate();
	virtual void closeConn();
	static int	callback(void *notUsed, int argc, char **argv, char **szColName);
private:
	sqlite3 *m_pDB;
};

/***

	获取数据库实例的工厂
	使用traits，不需要在工厂的getDBInstance中进行大量的if判断(类似java的反射)

***/
template<class T>
class DBFactory
{
public:
	static SmartPtr<DBUtil> *getDBInstance();
};

template<class T>
SmartPtr<DBUtil> DBFactory<T>::getDBInstance()
{
	SmartPtr<DBUtil> db(new T());
	return db;
	//return new T();
}
#endif