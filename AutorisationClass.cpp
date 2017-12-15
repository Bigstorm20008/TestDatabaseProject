#include "AutorisationClass.h"


AutorisationClass::AutorisationClass()
{	
	GetDBUserName();
	GetRoleOfCurrentUser();
	MyUserInterface interfaceForUser(pRoleMember);
}


AutorisationClass::~AutorisationClass()
{
	//������ ����������, ���������� ��������� new
	delete[]pUserName;
	pUserName = nullptr;
	delete pRoleMember;
	pRoleMember = nullptr;
	
}

void AutorisationClass::GetDBUserName()
{


	extern CSqlFramework* sqlODBC;                                //���������� ��������� ��������� � main.cpp
	TCHAR* sqlCommand = TEXT("SELECT CURRENT_USER");              //������ ��� SQL Server
	SQLHANDLE hStmt = sqlODBC->SendQueryToDatabase(sqlCommand);   //�������� ������ �� ���������� � ������� ���������� hsTmt
	//����������� ������� ������� ����� 1 ������ ������� ������ �������� ������ �� ���������
	SQLFetch(hStmt);
	//������� ���� ������
	Binding* pBinding = sqlODBC->GetBinding();
	//������� �����, ����������� ����� ������������
	size_t len = _tcslen(pBinding->GetDescription());
	//������� ������ ��� ���������� � ������� ��
	pUserName = new TCHAR[len + sizeof(TCHAR)];
	memset(pUserName, 0, len*sizeof(TCHAR));
	//��������� ������ � pUserName
	lstrcat(pUserName, pBinding->GetDescription());
	//��������� ������� ����� �������������
	sqlODBC->FreeBinding(hStmt);
	
	
	
	

	
}

void AutorisationClass::GetRoleOfCurrentUser()
{
	extern CSqlFramework* sqlODBC;                       //���������� ��������� ��������� � main.cpp
	TCHAR* partOfsqlCommand = TEXT("EXEC sp_helpuser");       //SQL ������ ��� ��������� ���������� � ������������(��� ����� ������������)

	//�������� SQL ������ ��� ��......
	//������� ����� ������� � ������� ������ ��� ����
	size_t len = _tcslen(partOfsqlCommand) + _tcslen(pUserName) + _tcslen(TEXT(" '")) + _tcslen(TEXT("'"));
	TCHAR* sqlCommand = new TCHAR[len+1];
	//�������, ���������� ������
	memset(sqlCommand, 0, len);
	//�������� ������ ����� ������������
	lstrcat(sqlCommand, partOfsqlCommand);
	lstrcat(sqlCommand, TEXT(" '"));
	lstrcat(sqlCommand, pUserName);
	lstrcat(sqlCommand, TEXT("'"));
	//�������� ������ �� ���������� � ������� ����������� ���������� hstmt
	SQLHANDLE hStmt = sqlODBC->SendQueryToDatabase(sqlCommand);
	//������� ��������� �� ����� � ����������� �������
	Binding* pBinding = sqlODBC->GetBinding();
	//�������� ���������� ������, ����������� �� ����� �������('RoleName')
	while (SQLFetch(hStmt) != SQL_NO_DATA)
	{
		Binding* thisBinding = pBinding;
		while (thisBinding)
		{
			if (lstrcmp(thisBinding->GetColumnName(),TEXT("RoleName")) == 0)
			{
				size_t len = lstrlen(thisBinding->GetDescription());
				pRoleMember = new TCHAR[len + 1];
				memset(pRoleMember, 0, len);
				lstrcat(pRoleMember, thisBinding->GetDescription());
				break;
			}
			else
			{
				thisBinding = thisBinding->GetNextBinding();
			}
		}
		
	}
	sqlODBC->FreeBinding(hStmt);
	delete sqlCommand;
	sqlCommand = nullptr;

}





