#include "db.h"

int MsSQLUtil::conn()
{
	::CoInitialize(NULL);
	m_connPtr.CreateInstance(__uuidof(Connection));
	return 0;
	//m_recordPtr.CreateInstance(__uuidof(Recordset));
}

int MsSQLUtil::open(string database,string host,string userName,string pass)
{
	_bstr_t	strConnection="Driver={sql server};server=localhost,1434;uid=";
	strConnection += userName.c_str();
	strConnection += ";pwd=";
	strConnection += pass.c_str();
	strConnection += ";Database=";
	strConnection +=database.c_str();
	strConnection +=";";
	try
	{
		m_connPtr->Open(strConnection,"","",adModeUnknown);
	}
	catch(_com_error &e)
	{
		cout<<e.Description()<<endl;
		return -1;
	}
	return 0;
}

SmartPtr<CQuerySet> MsSQLUtil::executeQuery(string sql)
{
	_RecordsetPtr rsp = m_connPtr->Execute(sql.c_str(),NULL,adCmdText);
	CMsSQLQuerySet *qs = new CMsSQLQuerySet(rsp);
	return qs;
	/*_bstr_t strSql = "select id,name from userinfo;";
	m_recordPtr = m_connPtr->Execute(strSql,NULL,adCmdText);
	m_recordPtr->MoveFirst();
	for(int i=0; i<m_recordPtr->GetFields()->GetCount(); i++)
	{
		std::string name = m_recordPtr->GetFields()->GetItem((LONG)i)->GetName();
		cout<<name<<"\t\t";
	}
	cout<<endl;
	m_recordPtr->MoveFirst();
	while(!m_recordPtr->adoEOF)
	{
		int cnt = m_recordPtr->GetFields()->GetCount();
		//string tempname1 = m_recordPtr->GetFields()->GetItem((LONG)0)->GetName();
		for(int i=0; i<m_recordPtr->GetFields()->GetCount(); i++)
		{
			std::string name = (char *)(_bstr_t)m_recordPtr->GetFields()->GetItem((LONG)i)->Value;
			cout<<name<<"\t\t";
		}
		cout<<endl;
		m_recordPtr->MoveNext();
	}*/
	//return NULL;
}

void MsSQLUtil::executeUpdate(string sql)
{

}

void MsSQLUtil::closeConn()
{

}

MsSQLUtil::~MsSQLUtil()
{
	//m_recordPtr->Close();
	m_connPtr->Close();
	::CoUninitialize();

}

CMsSQLQuerySet::CMsSQLQuerySet(_RecordsetPtr p):m_recordPtr(p)
{

}

CMsSQLQuerySet::~CMsSQLQuerySet()
{
	if(m_recordPtr)
	{
		m_recordPtr->Close();
	}
}

bool CMsSQLQuerySet::hasNext()
{
	return !m_recordPtr->adoEOF;
}

void CMsSQLQuerySet::moveFirst()
{
	m_recordPtr->MoveFirst();
}

void CMsSQLQuerySet::movePrev()
{
	m_recordPtr->MovePrevious();
}

void CMsSQLQuerySet::moveNext()
{
	cout<<m_recordPtr->GetAbsolutePosition()<<endl;
	m_recordPtr->MoveNext();
}

void CMsSQLQuerySet::moveLast()
{
	m_recordPtr->MoveLast();
}

int CMsSQLQuerySet::getInt(unsigned int index)
{
	return atoi((char*)(_bstr_t)m_recordPtr->GetCollect((LONG)index));
}

double CMsSQLQuerySet::getDouble(unsigned int index)
{
	return atof((char*)(_bstr_t)m_recordPtr->GetCollect((LONG)index));
}

string CMsSQLQuerySet::getString(unsigned int index)
{
	return (char*)(_bstr_t)m_recordPtr->GetCollect((LONG)index);
}

int CMsSQLQuerySet::getInt(string colName)
{
	return atoi((char*)(_bstr_t)m_recordPtr->GetCollect(colName.c_str()));
}

double CMsSQLQuerySet::getDouble(string colName)
{
	return atof((char*)(_bstr_t)m_recordPtr->GetCollect(colName.c_str()));
}

string CMsSQLQuerySet::getString(string colName)
{
	return (char*)(_bstr_t)m_recordPtr->GetCollect(colName.c_str());
}