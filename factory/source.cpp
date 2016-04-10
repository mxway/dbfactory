#include "db.h"

int main()
{
	SmartPtr<DBUtil> myConn = DBFactory<MsSQLUtil>::getDBInstance();
	myConn->conn();
	myConn->open("student","localhost","sa","123");
	SmartPtr<CQuerySet> qs = myConn->executeQuery("select * from userinfo");
	//qs->moveFirst();
	//qs->movePrev();
	while(qs->hasNext())
	{
		cout<<qs->getString("id")<<" ";
		cout<<qs->getString("name")<<" ";
		cout<<qs->getString("demo")<<endl;
		qs->moveNext();
	}
	//myConn->executeUpdate();
	//myConn->closeConn();
	return 0;
}