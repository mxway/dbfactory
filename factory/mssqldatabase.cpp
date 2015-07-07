#include "db.h"

void MsSQLUtil::conn()
{
	::CoInitialize(NULL);
	m_connPtr.CreateInstance(__uuidof(Connection));
	//m_recordPtr.CreateInstance(__uuidof(Recordset));
}

void MsSQLUtil::open(string userName,string pass,string database)
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
	}
}

void MsSQLUtil::executeQuery()
{
	_bstr_t strSql = "select id,name from userinfo;";
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
	}
}

void MsSQLUtil::executeUpdate()
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