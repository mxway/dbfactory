#include "db.h"
#include "sqlite3.h"

#ifdef USE_SQLITE3_DATABASE

SQLiteUtil::~SQLiteUtil()
{
	if(m_pDB != NULL)
	{
		sqlite3_close(m_pDB);
	}
}

int SQLiteUtil::conn()
{
	return 0;
}

int SQLiteUtil::open(string database,string host,string userName,string pass)
{
	//sqlite3 *pDB;
	int res = sqlite3_open(database.c_str(),&m_pDB);
	if(res != SQLITE_OK)
	{
		return 1;
	}
	return 0;
}

void SQLiteUtil::executeUpdate(string sql)
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

SmartPtr<CQuerySet> SQLiteUtil::executeQuery(string sql)
{
	char *errMsg;
	char temp[] = "select * from userinfo;";
	int res = sqlite3_exec(m_pDB, temp, &SQLiteUtil::callback,0, &errMsg);
	if(res != SQLITE_OK)
	{
		return NULL;
	}
	return NULL;
}

CSqliteQuerySet::CSqliteQuerySet():m_row(0),m_col(0),
						m_cur(0),m_total(0),m_dbResult(NULL)
{

}

CSqliteQuerySet::~CSqliteQuerySet()
{
	sqlite3_free_table(m_dbResult);
}

bool CSqliteQuerySet::hasNext()
{
	return m_cur < m_row;
}

void CSqliteQuerySet::setResult(char **dbResult,int nRow,int nCol)
{
	m_dbResult = dbResult;
	m_row = nRow;
	m_col = nCol;
}

void CSqliteQuerySet::moveNext()
{
	if(m_cur < m_row)
	{
		++m_cur;
	}
}

void CSqliteQuerySet::moveFirst()
{
	m_cur = 1;
}

void CSqliteQuerySet::movePrev()
{
	if(m_cur > 0)
	{
		m_cur--;
	}
}

void CSqliteQuerySet::moveLast()
{
	m_cur = m_row;
}

int CSqliteQuerySet::getInt(unsigned int index)
{
	if(index<0 || index>=m_col)
	{
		return 0;
	}
	int temp = m_cur*m_col+index;
	return atoi(m_dbResult[temp]);
}

string CSqliteQuerySet::getString(unsigned int index)
{
	if(index<0 || index>=m_col)
	{
		return "";
	}
	int temp = m_cur*m_col+index;
	return m_dbResult[temp];
}

double CSqliteQuerySet::getDouble(unsigned int index)
{
	if(index<0 || index>=m_col)
	{
		return 0;
	}
	int temp = m_cur*m_col+index;
	return atof(m_dbResult[temp]);
}

int CSqliteQuerySet::getInt(string colName)
{
	return this->getInt(this->getIndex(colName));
}

string CSqliteQuerySet::getString(string colName)
{
	return this->getString(this->getIndex(colName));
}

double CSqliteQuerySet::getDouble(string colName)
{
	return this->getDouble(this->getIndex(colName));
}

unsigned int CSqliteQuerySet::getIndex(string colName)
{
	unsigned int index = 0;
	for(index=0; index<m_col;index++)
	{
		if(StringUtil::strCmpNoCase(colName.c_str(),m_dbResult[index])==0)
		{
			break;
		}
	}
	return index;
}

#endif