#include "db.h"
#include <string.h>
#pragma warning(disable:4996)

void StringUtil::trimString(char *str1)
{
	char *p1 = str1;
	char *p2 = str1+strlen(str1)-1;
	while(isspace(*p1)){p1++;}
	while(isspace(*p2))
	{
		*p2='\0';
	}
	strcpy(str1,p1);
}

int StringUtil::strCmpNoCase(const char *str1,const char *str2)
{
	char temp1[1024] = {0};
	char temp2[1024] = {0};
	strncpy(temp1,str1,1023);
	strncpy(temp2,str2,1023);
	StringUtil::trimString(temp1);
	StringUtil::trimString(temp2);
	if(strlen(temp1) != strlen(temp2))
	{
		return 1;
	}
	char *p1 = temp1;
	char *p2 = temp2;
	while( *p1 && *p2 && tolower(*p1++)==tolower(*p2++));
	if(*p1=='\0')return 0;
	return 1;
}