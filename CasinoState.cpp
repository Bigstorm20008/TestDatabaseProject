#include "CasinoState.h"


CasinoState::CasinoState(CSqlFramework* sqlConnection)
{
	m_sqlConnection = sqlConnection;
	m_casinoState = FALSE;

	getDateInCasinoFromDatabase();
	if (!m_dateInCasino)
	{
		m_casinoState = FALSE;
	}
	else
	{
		m_casinoState = TRUE;
	}
}


CasinoState::~CasinoState()
{
	if (m_dateInCasino)
	{
		delete[]m_dateInCasino;
		m_dateInCasino = nullptr;
	}
}

void CasinoState::openCasino()
{
	TCHAR* sqlCommand = TEXT("INSERT INTO [dbo].[CasinoStatus] ([CasinoState]) VALUES ('True')");
	SQLHANDLE statementHandle = m_sqlConnection->SendQueryToDatabase(sqlCommand);
	m_sqlConnection->FreeBinding(statementHandle);
	m_casinoState = TRUE;

	getDateInCasinoFromDatabase();
}

void CasinoState::closeCasino()
{
	TCHAR* sqlCommand = TEXT("UPDATE [dbo].[CasinoStatus] SET [CasinoState] = 'False' WHERE DateInCasino = ?");
	SQLTCHAR* parameterArray[] = { m_dateInCasino };
	SQLHANDLE statementHandle = m_sqlConnection->ExecutePrepearedQuery(sqlCommand, parameterArray);
	m_sqlConnection->FreeBinding(statementHandle);
}

void CasinoState::getDateInCasinoFromDatabase()
{
	TCHAR* sqlCommand = TEXT("SELECT [DateInCasino] FROM [dbo].[CasinoStatus] WHERE CasinoState = 'True'");
	SQLHANDLE statementHandle = m_sqlConnection->SendQueryToDatabase(sqlCommand);
	
	Binding* pBinding = m_sqlConnection->GetBinding();
	SQLFetch(statementHandle);
	size_t len = _tcslen(pBinding->GetDescription()) + 1;
	if (!pBinding->getStrLenOrInd())
	{
		m_sqlConnection->FreeBinding(statementHandle);
		return;
	}
	else
	{
		m_dateInCasino = new TCHAR[len];
		memset(m_dateInCasino, 0, len*sizeof(TCHAR));
		_tcscpy_s(m_dateInCasino, len, pBinding->GetDescription());
		m_sqlConnection->FreeBinding(statementHandle);
	}
	
}
void CasinoState::getCasinoStateFromDatabase()
{

}

TCHAR* CasinoState::getDateInCasino() const
{
	return m_dateInCasino;
}
BOOL CasinoState::getCasinoState() const
{
	return m_casinoState;
}
