#include "db.h"
#include "sqlite3.h"

SQLiteUtil::~SQLiteUtil()
{
	if(m_pDB != NULL)
	{
		sqlite3_close(m_pDB);
	}
}

void SQLiteUtil::conn()
{

}

void SQLiteUtil::open(string userName,string pass,string database)
{
	//sqlite3 *pDB;
	int res = sqlite3_open("D:/git/mytest.db",&m_pDB);
	if(res != SQLITE_OK)
	{
		return;
	}
}

void SQLiteUtil::executeUpdate()
{
	char *errMsg;
	char temp[] = "INSERT INTO userinfo(name) values('mxl');";
	int res = sqlite3_exec(m_pDB,temp,NULL,0, &errMsg);
	if(res != SQLITE_OK)
	{
		return;
	}
}

int SQLiteUtil::callback(void *notUsed, int argc, char **argv, char **szColName)
{
	for(int i=0; i<argc; i++)
	{
		printf("%s\t\t",argv[i]);
	}
	printf("\n");
	return 0;
}

void SQLiteUtil::closeConn()
{

}

void SQLiteUtil::executeQuery()
{
	char *errMsg;
	char temp[] = "select * from userinfo;";
	int res = sqlite3_exec(m_pDB, temp, &SQLiteUtil::callback,0, &errMsg);
	if(res != SQLITE_OK)
	{
		return;
	}
}