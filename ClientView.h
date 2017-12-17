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
	void loadStandartImage(void);
	void disableBtnIfNotSelectedClient(void);
	void showBtnForSelectedClient(void);
	void destroyAuxiliaryWindows(void);
	void showAllWndForClientView(void);
	void hideWndForClientView(void);
	void InitAddClientWnd(void);
	void CreateClientViewWindows(void);
	void DestroyAllClientViewWindow(void);
	BOOL getInfoAboutSelectedClient(void);
	ClientView();
	~ClientView();
};

