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
	//��ʼ�����ݿ����ӣ��ɹ�����0�����򷵻�1
	virtual int conn()=0;
	//�����ݿ����ӣ�ִ�гɹ�����0�����򷵻�1
	virtual int open(string database,string host="",string userName="",string pass="")=0;
	//ִ��SQL��ѯ���
	virtual SmartPtr<CQuerySet> executeQuery(string sql)=0;
	//ִ��insert,update,delete�������ݿ�����
	virtual void executeUpdate(string sql) = 0;
	//�ر����ݿ����ӣ��Ƿ��б�Ҫ
	virtual void closeConn()=0;
	virtual ~DBUtil(){}
	//��ȥ�������ַ�����ǰ׺�ͺ�׺�Ŀո��ٽ��в����ִ�Сд�ıȽ�
	//��ȷ���0�����򷵻�1
};

/****
*
* ��ѯ�����
*
****/
class CQuerySet
{
public:
	virtual ~CQuerySet(){}
	//�Ƿ��м�¼
	virtual bool hasNext()		= 0;
	//��ǰ�α�����һ����¼
	virtual void moveNext()		= 0;
	//��ǰ�α�����һ����¼
	virtual void movePrev()		= 0;
	//�ƶ�����һ����¼
	virtual void moveFirst()	= 0;
	//�ƶ������һ����¼
	virtual void moveLast()		= 0;

	//ͨ�����±��ȡ����ֵ
	virtual int getInt(unsigned int index) = 0;
	//ͨ�����±��ȡ�ַ���ֵ
	virtual string getString(unsigned int index) = 0;
	//ͨ�����±��ȡ����ֵ
	virtual double getDouble(unsigned int index) = 0;
	//ͨ��������ȡ����ֵ
	virtual int getInt(string colName) = 0;
	//ͨ��������ȡ�ַ���
	virtual string getString(string colName) = 0;
	//ͨ��������ȡ������
	virtual double getDouble(string colName) = 0;
};

#ifdef USE_MYSQL_DATABASE
/****
*
* ����mysql���ݿ����
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
//����mssql
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
//����oracle
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
//����sqlite
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
* sqlite���ݿ�
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

	��ȡ���ݿ�ʵ���Ĺ���
	ʹ��traits������Ҫ�ڹ�����getDBInstance�н��д�����if�ж�(����java�ķ���)

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