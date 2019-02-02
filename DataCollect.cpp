#include "DataCollect.h"




Data_Collector::Data_Collector(window_size *pstruct) // get the screen size
{
	win_hdc = pstruct->hdc;
	win_hwcdc = pstruct->hwcdc;

	win_width = pstruct->width;
	win_height = pstruct->height;

	win_src_width = pstruct->src_width;
	win_src_height = pstruct->src_height;

};

Mat Data_Collector::Capture(string filename)
{

	src.create(win_height, win_width, CV_8UC4);
	
	hbwindow = CreateCompatibleBitmap(win_hdc, win_width, win_height);

	//create a bitmap
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

	/* save file
	stringstream ss;
	string basePath("C:\\ImgData");
	string str(filename);
	
	ss << basePath << "\\" << str << ".bmp";
	*/
	/*
	DeleteObject(hbwindow);
	DeleteDC(win_hwcdc);
	ReleaseDC(win_hwnd);
	*/

	return src;
}

