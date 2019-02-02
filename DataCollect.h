#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "pch.h"
#include <iostream>
#include <string>
#include "msgdef.h"
#include <Windows.h>

using namespace cv;
using namespace std;

class Data_Collector
{
	private:
		string filename;

		int win_width;
		int win_height;
		int win_src_width;
		int win_src_height;

		HDC win_hdc, win_hwcdc;
		HBITMAP hbwindow;

		BITMAPFILEHEADER BMFH;
		BITMAPINFOHEADER BMIH;

		Mat src;

	public:
		Data_Collector(window_size *pstruct);
		~Data_Collector();

		Mat Capture(string filename);
};

