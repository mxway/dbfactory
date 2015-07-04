#include "db.h"
#include "mysql.h"
#include <iostream>
#pragma comment(lib,"libmysql.lib")
using namespace std;

void MySQLUtil::conn()
{
	m_conn = mysql_init((MYSQL*)0);
	if(m_conn != NULL)
	{
		cout<<"³É¹¦"<<endl;
	}else
	{
		cout<<"Ê§°Ü"<<endl;
	}
	
}

void MySQLUtil::open(string userName,string pass,string database)
{
	
	if(mysql_real_connect(m_conn,"localhost",userName.c_str(),pass.c_str(),database.c_str(),3306,NULL,0))
	{
	}
}

void MySQLUtil::executeQuery()
{
	char temp[] = "select * from userinfo";
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
	mysql_free_result(res);
}

void MySQLUtil::executeUpdate()
{
	char temp[] = "insert into userinfo(name,age) values(\'test\',15);";
	int result = mysql_real_query(m_conn, temp, strlen(temp));

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