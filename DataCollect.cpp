#include "DataCollect.h"




Data_Collector::Data_Collector() 
{
	Search();

};
Data_Collector::~Data_Collector() {}

// get the screen size
void Data_Collector::Search()	
{
	HWND hwnd = GetDesktopWindow();

	win_hdc = GetDC(hwnd);
	win_hwcdc = CreateCompatibleDC(win_hdc);

	RECT win_size;

	GetClientRect(hwnd, &win_size);

	win_width = win_size.right;
	win_height = win_size.bottom;

	win_src_width = win_size.right / 1;
	win_src_height = win_size.bottom / 1;
}


//capture screen
Mat Data_Collector::Capture()	
{
	src.create(win_height, win_width, CV_8UC4);	//@param3 : matrix type(channel)
	
	//create a bitmap
	hbwindow = CreateCompatibleBitmap(win_hdc, win_width, win_height);
	BMIH.biSize = sizeof(BITMAPINFOHEADER);
	BMIH.biWidth = win_width;
	BMIH.biHeight = win_height;
	BMIH.biPlanes = 1;
	BMIH.biBitCount = 24;
	BMIH.biCompression = BI_RGB;
	BMIH.biSizeImage = 0; //grayscale = 1
	BMIH.biXPelsPerMeter = 0;
	BMIH.biYPelsPerMeter = 0;
	BMIH.biClrUsed = 0;
	BMIH.biClrImportant = 0;

	// use the previously created device context with the bitmap
	SelectObject(win_hwcdc, hbwindow);

	//	copy from the window device context to the bitmap device context

	StretchBlt(win_hwcdc, 0, 0, win_width, win_height, win_hdc, 0, 0, win_src_width, win_src_height, SRCCOPY);
	GetDIBits(win_hwcdc, hbwindow, 0, win_height, src.data, (BITMAPINFO *)&BMIH, DIB_RGB_COLORS);
	
	DeleteObject(hbwindow);
	DeleteDC(win_hwcdc);
	ReleaseDC(win_hwnd);
	
	return src;
}

//save image
void Data_Collector::Save(Mat img, string img_name, bool gray)
{
	//grayscale
	if (gray)
	{
		Mat gray_img;
		cvtColor(img, gray_img, CV_BGR2GRAY);
		imwrite(img_name, gray_img)
	}
	else
	{
		imwrite(img_name, img)
	}
}

//capture agent
virtual void Data_Collector::run()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	Save(Capture(),buf,TRUE);
	Sleep(2000);
}
