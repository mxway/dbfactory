#include "db.h"

int main()
{
	DBUtil *myConn = DBFactory<SQLiteUtil>::getDBInstance();
	myConn->conn();
	myConn->open("","","mytest");
	myConn->executeQuery();
	myConn->executeUpdate();
	//myConn->closeConn();
	return 0;
}