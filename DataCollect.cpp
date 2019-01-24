#include "DataCollect.h"

using namespace cv;
using namespace std;

Data_Collector::Data_Collector(window_size *pstruct)
{
	win_hdc = pstruct->hdc;
	win_hwcdc = pstruct->hwcdc;

	win_width = pstruct->width;
	win_height = pstruct->height;

	win_src_width = pstruct->src_width;
	win_src_height = pstruct->src_height;

};

Mat Data_Collector::save()
{
	src.create(win_height, win_width, CV_8UC4);

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

	SelectObject(win_hwcdc, hbwindow);
	StretchBlt(win_hwcdc, 0, 0, win_width, win_height, win_hdc, 0, 0, win_src_width, win_src_height, SRCCOPY);
	GetDIBits(win_hwcdc, hbwindow, 0, win_height, src.data, (BITMAPINFO *)&BMIH, DIB_RGB_COLORS);

	/*
	DeleteObject(hbwindow);
	DeleteDC(win_hwcdc);
	ReleaseDC(win_hwnd);
	*/

	return src;
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다