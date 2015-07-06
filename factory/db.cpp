#include <iostream>
#include <string>
#include "db.h"
using namespace std;
/*
void MYSQLDBUtil::conn()
{
	cout<<"MySQL连接数据库"<<endl;
}

void MYSQLDBUtil::executeSQL()
{
	cout<<"MySQL执行SQL语句"<<endl;
}

void MYSQLDBUtil::closeConn()
{
	cout<<"MySQL断开数据库连接"<<endl;
}*/

void MsSQLUtil::conn()
{
	cout<<"SQL Server连接数据库"<<endl;
}

void MsSQLUtil::executeQuery()
{
	cout<<"SQL Server执行SQL语句"<<endl;
}

void MsSQLUtil::executeUpdate()
{

}

void MsSQLUtil::closeConn()
{
	cout<<"SQL Server断开数据库连接"<<endl;
}

void OracleUtil::conn()
{
	cout<<"Oracle连接数据库"<<endl;
}

void OracleUtil::executeQuery()
{
	cout<<"Oracle执行SQL语句"<<endl;
}

void OracleUtil::executeUpdate()
{

}

void OracleUtil::closeConn()
{
	cout<<"Oracle断开数据库连接"<<endl;
}
