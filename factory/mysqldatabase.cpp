#include "db.h"
#include "mysql.h"
#include <iostream>
#pragma comment(lib,"libmysql.lib")
#pragma warning(disable:4996)
using namespace std;

#ifdef USE_MYSQL_DATABASE

int MySQLUtil::conn()
{
	m_conn = mysql_init((MYSQL*)0);
	if(m_conn != NULL)
	{
		return 0;
	}else
	{
		return 1;
	}
	
}

int MySQLUtil::open(string database,string host,string userName,string pass)
{
	char tempHost[128] = {0};
	char tempUserName[128] = {0};
	char tempPass[128] = {0};
	if(host.length()>0)
	{
		strncpy(tempHost,host.c_str(),127);
	}else
	{
		strncpy(tempHost,"127.0.0.1",127);
	}
	if(userName.length()>0)
	{
		strncpy(tempUserName,userName.c_str(),127);
	}
	if(pass.length()>0)
	{
		strncpy(tempPass,pass.c_str(),127);
	}
	if(database.length()<=0)
	{
		return 1;
	}
	if(mysql_real_connect(m_conn,tempHost,tempUserName,tempPass,database.c_str(),3306,NULL,0))
	{
		return 1;
	}
	return 0;
}

SmartPtr<CQuerySet> MySQLUtil::executeQuery(string sql)
{
	mysql_query(m_conn,sql.c_str());
	MYSQL_RES *mysqlRes = mysql_store_result(m_conn);
	CMySQLQuerySet *rs = new CMySQLQuerySet();
	rs->setRes(mysqlRes);
	return rs;
	/*char temp[] = "select * from userinfo";
	mysql_real_query(m_conn,temp, strlen(temp));
	MYSQL_RES *res = mysql_store_result(m_conn);
	MYSQL_ROW row;
	while(row = mysql_fetch_row(res))
	{
		for(int i=0; i<mysql_num_fields(res); i++)
		{
			printf("%s   ",row[i]);
		}
	}
	mysql_free_result(res);*/
}

void MySQLUtil::executeUpdate(string sql)
{
	size_t result = mysql_real_query(m_conn, sql.c_str(), sql.length());	
}

void MySQLUtil::closeConn()
{
	
}

MySQLUtil::~MySQLUtil()
{
	if(m_conn != NULL)
	{
		mysql_close(m_conn);
	}
}

CMySQLQuerySet::CMySQLQuerySet():m_res(NULL),m_cur(0),m_totalNum(0),m_row(NULL)
{

}

CMySQLQuerySet::~CMySQLQuerySet()
{
	if(m_res != NULL)
	{
		mysql_free_result(m_res);
	}
}

bool CMySQLQuerySet::hasNext()
{
	return m_cur<m_totalNum;
}

void CMySQLQuerySet::setRes(MYSQL_RES *res)
{
	this->m_res = res;
	m_totalNum = mysql_num_rows(res);
}

void CMySQLQuerySet::moveFirst()
{
	if(m_totalNum != 0)
	{
		m_cur = 0;
		mysql_data_seek(m_res,m_cur);
		m_row = mysql_fetch_row(m_res);
	}
}

void CMySQLQuerySet::moveNext()
{
	if( m_cur < m_totalNum)
	{
		++m_cur;
		m_row = mysql_fetch_row(m_res);
		//mysql_data_seek(m_res,++m_cur);
	}
}

void CMySQLQuerySet::movePrev()
{
	if(m_cur > 0)
	{
		mysql_data_seek(m_res,--m_cur);
		m_row = mysql_fetch_row(m_res);
	}
}

void CMySQLQuerySet::moveLast()
{
	if(m_totalNum != 0)
	{
		m_cur = m_totalNum-1;
		mysql_data_seek(m_res,m_cur);
		m_row = mysql_fetch_row(m_res);
	}
}

int CMySQLQuerySet::getInt(unsigned int index)
{
	unsigned int cols = mysql_num_fields(m_res);
	if(index<0 || index>=cols)
	{
		return 0;
	}
	return atoi(m_row[index]);
}

int CMySQLQuerySet::getInt(string colName)
{
	return this->getInt(this->getIndex(colName));
}

string CMySQLQuerySet::getString(unsigned int index)
{
	unsigned int cols = mysql_num_fields(m_res);
	if(index<0 || index>=cols)
	{
		return "";
	}
	return m_row[index];
}

string CMySQLQuerySet::getString(string colName)
{
	return this->getString(this->getIndex(colName));
}

double CMySQLQuerySet::getDouble(unsigned int index)
{
	unsigned int cols = mysql_num_fields(m_res);
	if(index<0 || index>=cols)
	{
		return 0;
	}
	return atof(m_row[index]);
}

double CMySQLQuerySet::getDouble(string colName)
{
	return this->getDouble(this->getIndex(colName));
}

unsigned int CMySQLQuerySet::getIndex(string colName)
{
	MYSQL_FIELD *fields = mysql_fetch_fields(m_res);
	unsigned int cols = mysql_num_fields(m_res);
	unsigned int index = 0;
	for(index=0; index<cols; index++)
	{
		if( StringUtil::strCmpNoCase(colName.c_str(),fields[index].name)==0 )
		{
			break;
		}
	}
	return index;
}
#endif