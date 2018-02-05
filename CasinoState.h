#pragma once

#include <Windows.h>
#include "SqlFramework.h"

class CasinoState
{
public:
	CasinoState(CSqlFramework* sqlConnection);
	~CasinoState();
	void openCasino();
	void closeCasino();
	TCHAR* getDateInCasino() const;
	BOOL getCasinoState() const;
private:
	CSqlFramework* m_sqlConnection;
	BOOL m_casinoState;
	TCHAR* m_dateInCasino;

	void getDateInCasinoFromDatabase();
	void getCasinoStateFromDatabase();
};

