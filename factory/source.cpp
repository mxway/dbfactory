#include "db.h"

int main()
{
	DBUtil *myConn = DBFactory<MySQLUtil>::getDBInstance();
	myConn->conn();
	myConn->open("root","","mytest");
	myConn->executeQuery();
	myConn->executeUpdate();
	//myConn->closeConn();
	return 0;
}