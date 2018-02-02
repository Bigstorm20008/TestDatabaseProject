#include "ImageTemplate.h"


ImageTemplate::ImageTemplate(int imageXPos, int imageYPos, int imageWidth, int imageHeight, HWND parent, TCHAR* imageLocation)
{
	m_editForImageLocation = nullptr;
	createWindowForImage(imageXPos, imageYPos, imageWidth, imageHeight, parent, imageLocation);
}


ImageTemplate::~ImageTemplate()
{
	if (m_editForImageLocation)
	{
		delete m_editForImageLocation;
		m_editForImageLocation = nullptr;
	}
	DestroyWindow(m_imagehWnd);
}

void ImageTemplate::createWindowForImage(int imageXPos, int imageYPos, int imageWidth, int imageHeight, HWND parent, TCHAR* imageLocation)
{
	
	m_imageWidth = imageWidth;
	m_imageHeight = imageHeight;
	m_parentOfImage = parent;
	m_imagehWnd = CreateWindow(TEXT("STATIC"),
		                       NULL,
		                       WS_CHILD | SS_NOTIFY | SS_BITMAP | WS_VISIBLE,
							   imageXPos, imageYPos,
							   imageWidth, imageHeight,
		                       parent,
		                       (HMENU)NULL,
		                       (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                       NULL);
	SetWindowLongPtr(m_imagehWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	m_oldImageProc = (LONG_PTR)SetWindowLongPtr(m_imagehWnd, GWLP_WNDPROC, (LONG_PTR)(ImageProc));
	m_hBitmap = (HBITMAP)LoadImage(NULL, imageLocation, IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
	SendMessage(m_imagehWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
}
void ImageTemplate::loadDefaultImage()
{
	m_hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\defaultImage.bmp"), IMAGE_BITMAP, m_imageWidth, m_imageHeight, LR_LOADFROMFILE);
	SendMessage(m_imagehWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
}
void ImageTemplate::createButtonForImage(TCHAR* buttonText, UINT buttonIdentifier)
{
	RECT imageRC;
	GetWindowRect(m_imagehWnd, &imageRC);
	POINT tmp;
	tmp.x = imageRC.right;
	tmp.y = imageRC.bottom;
	ScreenToClient(m_parentOfImage, &tmp);

	int buttonWidth = 150;
	int buttonHeight = 20;
	int buttonXPos = tmp.x - buttonWidth;
	int buttonYPos = tmp.y;

	m_buttonForImage = CreateWindow(TEXT("BUTTON"),
		                            buttonText,
		                            WS_CHILD | WS_VISIBLE |BS_DEFPUSHBUTTON,
				                    buttonXPos, buttonYPos,
				                    buttonWidth, buttonHeight,
				                    m_parentOfImage,
		                            (HMENU)buttonIdentifier,
		                            (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                            NULL);
	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		L"Time New Romans");
	SendMessage(m_buttonForImage, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

	tmp.x = imageRC.left;
	tmp.y = imageRC.bottom;
	ScreenToClient(m_parentOfImage, &tmp);

	int editXPos = tmp.x;
	int editYPos = tmp.y;
	int editWidth = buttonXPos - tmp.x;
	int editHeight = buttonHeight;
	m_editForImageLocation = new EditControlTemplate;
	m_editForImageLocation->createEditControl(m_parentOfImage, editXPos, editYPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | ES_MULTILINE | ES_AUTOHSCROLL);
}

TCHAR* ImageTemplate::getImageLocation()
{
	TCHAR* imageLocation = m_editForImageLocation->getTextFromEdit();
	return imageLocation;
}

void ImageTemplate::setNewImageLocationAndLoadIt(TCHAR* imageLocation)
{

	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, imageLocation, IMAGE_BITMAP, imageWidthForApplication, imageHeightForApplication, LR_LOADFROMFILE);
	if (hBitmap)
	{
		m_hBitmap = hBitmap;
		SendMessage(m_imagehWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
		if (m_editForImageLocation)
		{
			m_editForImageLocation->setNewTextForEdit(imageLocation);
		}
	}
	else
	{
		MessageBox(m_parentOfImage, TEXT("Не удалось загрузить изображение. Выберите изображение в формате *.bmp"), TEXT("Ошибка загрузки изображения"), MB_OK);
	}	
}

LRESULT CALLBACK ImageTemplate::ImageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImageTemplate* imageTemplate = NULL;
	imageTemplate = (ImageTemplate*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (imageTemplate != NULL)
	{
		return imageTemplate->RealImageProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

LRESULT ImageTemplate::RealImageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT     ps;
			HDC             hdc;
			BITMAP          bitmap;
			HDC             hdcMem;
			HGDIOBJ         oldBitmap;

			hdc = BeginPaint(m_imagehWnd, &ps);
			hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, m_hBitmap);
			GetObject(m_hBitmap, sizeof(bitmap), &bitmap);
			BitBlt(hdc, 0, 0, m_imageWidth, m_imageHeight, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
			EndPaint(m_imagehWnd, &ps);
			break;
		}
		default:
		{
			return CallWindowProc((WNDPROC)m_oldImageProc, m_imagehWnd, msg, wParam, lParam);
		}

	}
	return 0;
}
