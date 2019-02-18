#pragma once
#pragma execution_character_set("utf-8")
// 本文件为utf-8 编码格式
#include "stdafx.h"

#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "qrencode.h"

using namespace std;
using namespace cv;

int _tmain(int argc, char* argv[])
{
	string text("rtmp://pili-live-rtmp.live.detu.com/detulive/test");
	
	QRcode* pQRC = QRcode_encodeString(text.c_str(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);
	if (!pQRC){
		return -1;
	}

	int maskWidth = 8;
	int imgWidth = pQRC->width;
	int actualImgWidth = imgWidth * maskWidth;
	cv::Mat mat(actualImgWidth, actualImgWidth, CV_8UC3, cv::Scalar(255, 255, 255));

	unsigned char* pSourceData = pQRC->data;
	for (int y = 0; y < imgWidth; y++)
	{
		uchar* matPtr = mat.ptr<uchar>(y * maskWidth);
		for (int x = 0; x < imgWidth; x++)
		{
			if (*pSourceData & 1)
			{
				for (int row = 0; row < maskWidth; row++)
				{
					for (int col = 0; col < maskWidth; col++)
					{
						matPtr[3 * actualImgWidth * row + x * maskWidth * 3 + col * 3] = 0;
						matPtr[3 * actualImgWidth * row + x * maskWidth * 3 + col * 3 + 1] = 0;
						matPtr[3 * actualImgWidth * row + x * maskWidth * 3 + col * 3 + 2] = 0;
					}
				}
			}
			pSourceData++;
		}
	}

	cv::imshow("result", mat);
	cv::waitKey(0);

	QRcode_free(pQRC);
	return 0;
}