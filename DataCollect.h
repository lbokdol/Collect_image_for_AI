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
#include "CThread.h"
#include <time.h>

using namespace cv;
using namespace std;

class Data_Collector:public CThread
{
	private:
		string filename;

		HWND target_screen;

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
		Data_Collector();
		~Data_Collector();

		void Search();
		Mat Capture();
		void Save(Mat img, string img_name, bool gray);

		virtual void run();
};

