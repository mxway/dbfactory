#ifndef DB_INCLUDE_H
#define DB_INCLUDE_H
#include <iostream>
#include <string>

#ifdef MXL_MYSQL
	#define USE_MYSQL_DATABASE
#elif defined MXL_MSSQL
	#define USE_MSSQL_DATABASE
#elif defined MXL_ORACLE
	#define USE_ORACLE_DATABASE
#else
	#define USE_SQLITE3_DATABASE
#endif

#ifdef USE_MYSQL_DATABASE
#include <mysql.h>
#elif defined USE_SQLITE3_DATABASE
#include "sqlite3.h"
#endif

#include "smartptr.h"
using namespace std;
using namespace commutil;

class CQuerySet;

class StringUtil
{
public:
	static int   strCmpNoCase(const char *str1,const char *str2);
	static void  trimString(char *str1);
};

class DBUtil
{
public:
	//初始化数据库连接，成功返回0，否则返回1
	virtual int conn()=0;
	//打开数据库连接，执行成功返回0，否则返回1
	virtual int open(string database,string host="",string userName="",string pass="")=0;
	//执行SQL查询语句
	virtual SmartPtr<CQuerySet> executeQuery(string sql)=0;
	//执行insert,update,delete更新数据库的语句
	virtual void executeUpdate(string sql) = 0;
	//关闭数据库连接，是否有必要
	virtual void closeConn()=0;
	virtual ~DBUtil(){}
	//先去除两个字符串的前缀和后缀的空格，再进行不区分大小写的比较
	//相等返回0，否则返回1
};

/****
*
* 查询结果集
*
****/
class CQuerySet
{
public:
	virtual ~CQuerySet(){}
	//是否还有记录
	virtual bool hasNext()		= 0;
	//当前游标下移一条记录
	virtual void moveNext()		= 0;
	//当前游标上移一条记录
	virtual void movePrev()		= 0;
	//移动到第一条记录
	virtual void moveFirst()	= 0;
	//移动到最后一条记录
	virtual void moveLast()		= 0;

	//通过列下标获取整型值
	virtual int getInt(unsigned int index) = 0;
	//通过列下标获取字符串值
	virtual string getString(unsigned int index) = 0;
	//通过列下标获取浮点值
	virtual double getDouble(unsigned int index) = 0;
	//通过列名获取整型值
	virtual int getInt(string colName) = 0;
	//通过列名获取字符串
	virtual string getString(string colName) = 0;
	//通过列名获取浮点型
	virtual double getDouble(string colName) = 0;
};

#ifdef USE_MYSQL_DATABASE
/****
*
* 操作mysql数据库的类
*
****/
class MySQLUtil:public DBUtil
{
public:
	virtual int conn();
	virtual int open(string database,string host="",string userName="",string pass="");
	virtual SmartPtr<CQuerySet> executeQuery(string sql);
	virtual void executeUpdate(string sql);
	virtual void closeConn();
	~MySQLUtil();
private:
	MYSQL	*m_conn;
};

class CMySQLQuerySet:public CQuerySet
{
public:
	CMySQLQuerySet();
	~CMySQLQuerySet();
	virtual	bool	hasNext();
	virtual	void	moveNext();
	virtual	void	movePrev();
	virtual	void	moveFirst();
	virtual	void	moveLast();

	virtual	int		getInt(unsigned int index);
	virtual	string	getString(unsigned int index);
	virtual	double  getDouble(unsigned int index);
	virtual	int		getInt(string colName);
	virtual	string  getString(string colName);
	virtual	double	getDouble(string colName);

	void			setRes(MYSQL_RES *res);
	unsigned int    getIndex(string colName);

private:
	MYSQL_RES		*m_res;
	MYSQL_ROW       m_row;
	int				m_cur;
	int				m_totalNum;
};
#endif

#ifdef USE_MSSQL_DATABASE
//操作mssql
class MsSQLUtil:public DBUtil
{
public:
	virtual int conn();
	virtual int open(string database,string host="",string userName="",string pass="");
	virtual SmartPtr<CQuerySet> executeQuery(string sql);
	virtual void executeUpdate(string sql);
	virtual void closeConn();
};
#endif

#ifdef USE_ORACLE_DATABASE
//操作oracle
class OracleUtil:public DBUtil
{
public:
	virtual int conn();
	virtual int open(string database,string host="",string userName="",string pass="");
	virtual SmartPtr<CQuerySet> executeQuery(string sql);
	virtual void executeUpdate(string sql);
	virtual void closeConn();
};
#endif

#ifdef USE_SQLITE3_DATABASE
//操作sqlite
class SQLiteUtil:public DBUtil
{
public:
	~SQLiteUtil();
	virtual int conn();
	virtual int open(string database,string host="",string userName="",string pass="");
	virtual SmartPtr<CQuerySet> executeQuery(string sql);
	virtual void executeUpdate(string sql);
	virtual void closeConn();
	static int	callback(void *notUsed, int argc, char **argv, char **szColName);
private:
	sqlite3 *m_pDB;
};

/****
*
* sqlite数据库
*
***/
class CSqliteQuerySet:public CQuerySet
{
	CSqliteQuerySet();
	~CSqliteQuerySet();
	virtual bool hasNext();
	virtual void moveNext();
	virtual void movePrev();
	virtual void moveFirst();
	virtual void moveLast();

	virtual int		getInt(unsigned int index);
	virtual string	getString(unsigned int index);
	virtual double  getDouble(unsigned int index);
	virtual int		getInt(string colName);
	virtual string  getString(string colName);
	virtual double  getDouble(string colName);

	void			setResult(char **dbResult,int nRow,int nCol);
	unsigned int	getIndex(string colName);
private:
	char			**m_dbResult;
	int				m_row;
	int				m_col;
	int				m_cur;
	int				m_total;
};
#endif


/***

	获取数据库实例的工厂
	使用traits，不需要在工厂的getDBInstance中进行大量的if判断(类似java的反射)

***/
template<class T>
class DBFactory
{
public:
	static SmartPtr<DBUtil> getDBInstance();
};

template<class T>
SmartPtr<DBUtil> DBFactory<T>::getDBInstance()
{
	SmartPtr<DBUtil> db(new T());
	return db;
	//return new T();
}
#endif