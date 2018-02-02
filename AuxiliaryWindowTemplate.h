#pragma once

#include <Windows.h>
#include "Constatnts.h"


class AuxiliaryWindowTemplate
{
public:
	AuxiliaryWindowTemplate(HWND windowToDisable, HWND parent, int auxiliaryWidth, int auxiliaryHeight, TCHAR* captionText);
	~AuxiliaryWindowTemplate();

	
	virtual void createControlsForWindow() = 0;
private:
	static LRESULT CALLBACK AuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void createModalAuxiliaryWindow(HWND windowToDisable, HWND parent, int auxiliaryWidth, int auxiliaryHeight, TCHAR* captionText);
protected:
	virtual LRESULT RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND m_auxiliaryWnd;
	HWND m_WndToDisable;
	HWND m_auxiliaryParent;
	HWND m_captionWnd;

};

