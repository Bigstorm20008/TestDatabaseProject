#pragma once

#include <Windows.h>
#include "Constants.h"

class ClientViewButtons
{
private:
	HWND parentWndForBtns;
	static int xPos;
	static int yPos;
	static int btnWidth;
	static int btnHeight;
	void createAddClientToDatabaseBtn(void);
	void createEntranceCasinoBtn(void);
	void createEditClientBtn(void);
public:
	void hideAllButtons(void);
	void showAllButtons(void);
	void destroyAllClientViewButtons();
	ClientViewButtons();
	~ClientViewButtons();
	void createButtons();
};

