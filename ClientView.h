#pragma once

#include "ClientList.h"
#include "ClientImageWnd.h"
#include "Client.h"
#include "ClientViewButtons.h"
#include "AuxiliaryWindows.h"

class ClientView
{
private:
	Client* currentClient;
	ClientList* allClient;
	ClientImageWnd* photoForCurrentClient;
	ClientViewButtons* buttons;
	AuxiliaryWindows* auxiliaryWindows;
	//ClientMainInfoWnd* currentClientInfoWnd;
	//ClientExtendedInfo* extendedInfoForCurrClient;
public:
	void destroyAuxiliaryWindows(void);
	void showAllWndForClientView(void);
	void hideWndForClientView();
	void InitAddClientWnd(void);
	void CreateClientViewWindows();
	void DestroyAllClientViewWindow();
	BOOL getInfoAboutSelectedClient();
	ClientView();
	~ClientView();
};

