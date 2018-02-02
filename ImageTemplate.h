#pragma once

#include<Windows.h>
#include "Constatnts.h"
#include "EditControlTemplate.h"

class ImageTemplate
{
public:
	ImageTemplate(int imageXPos, int imageYPos, int imageWidth, int imageHeight, HWND parent, TCHAR* imageLocation);
	~ImageTemplate();
	void createButtonForImage(TCHAR* buttonText, UINT buttonIdentifier);
	void createEditForImageLocation();
	TCHAR* getImageLocation();
	void setNewImageLocationAndLoadIt(TCHAR* imageLocation);
	void loadDefaultImage();
private:
	HBITMAP m_hBitmap;
	
	LONG_PTR m_oldImageProc;
	static LRESULT CALLBACK ImageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	int m_imageWidth;
	int m_imageHeight;

	void createWindowForImage(int imageXPos, int imageYPos, int imageWidth, int imageHeight, HWND parent, TCHAR* imageLocation);
protected:
	LRESULT RealImageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND m_imagehWnd;
	HWND m_parentOfImage;
	HWND m_buttonForImage;
	EditControlTemplate* m_editForImageLocation;
};

