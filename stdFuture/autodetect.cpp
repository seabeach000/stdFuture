#include "stdafx.h"
#include "autodetect.h"

#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;

static Mat sPreHistMat;
static int snFrames = 0;
static int scountMin = 7;
static int scountMax = 12;
static double sColorStripRatio = 0.5;
static double sColorSceneRatio = 0.99;
static double sStaticFrameRatio = 0.999999999;
static int sTellThisBlack = 30;

bool Analysis_hist_Ver2(Mat SrcImgG1, bool bCheckStill, long* result, unsigned char* pbuffer, STVideoDetectDetails& stVideoDetectDetails)
{
	*result = 0;
	//计算直方图
	double sumPixle = SrcImgG1.rows * SrcImgG1.cols;
	int histSize = 256;
	float range[] = { 0, 255 };
	const float* histRange[] = { range };
	Mat mathist, mathist_bak;
	int channels[] = { 1 }; //UYVY，用Y通道计算
	//----------------------------------------------------------
	//计算原灰度图的直方图
	//-----------------------------------------------------
	calcHist(&SrcImgG1, 1, channels, Mat(), mathist, 1, &histSize, histRange);
	//if (bCheckStill)
	mathist_bak = mathist.clone();
	//-----------------------------------------------------

	//新的规整算法，求最大的8个值，然后将其左右两边的数字归整到这个最大值上
	//-------------------------------------
	int nstep = 1;
	double nMax[10] = { 0 };
	int nMaxIndx[10] = { 0 };
	double dbini[10][2] = { 0 };
	for (int i = 0; i < 8; i++)
	{
		minMaxIdx(mathist, 0, &nMax[i], 0, &nMaxIndx[i]);
		mathist.at<float>(nMaxIndx[i]) = 0;
		if (nMaxIndx[i] == 0)
		{
			nMax[i] = nMax[i] + mathist.at<float>(nMaxIndx[i] + 1) + mathist.at<float>(nMaxIndx[i] + 2)
				+ mathist.at<float>(nMaxIndx[i] + 3) + mathist.at<float>(nMaxIndx[i] + 4);
			mathist.at<float>(nMaxIndx[i] + 1) = 0;
			mathist.at<float>(nMaxIndx[i] + 2) = 0;
			mathist.at<float>(nMaxIndx[i] + 3) = 0;
			mathist.at<float>(nMaxIndx[i] + 4) = 0;
			dbini[i][1] = mathist.at<float>(nMaxIndx[i] + 5) / nMax[i];
		}
		else if (nMaxIndx[i] == 1)
		{
			nMax[i] = nMax[i] + mathist.at<float>(nMaxIndx[i] - 1) + mathist.at<float>(nMaxIndx[i] + 1)
				+ mathist.at<float>(nMaxIndx[i] + 2) + mathist.at<float>(nMaxIndx[i] + 3);
			mathist.at<float>(nMaxIndx[i] - 1) = 0;
			mathist.at<float>(nMaxIndx[i] + 1) = 0;
			mathist.at<float>(nMaxIndx[i] + 2) = 0;
			mathist.at<float>(nMaxIndx[i] + 3) = 0;
			dbini[i][1] = mathist.at<float>(nMaxIndx[i] + 4) / nMax[i];
		}
		else if (nMaxIndx[i] == 2)
		{
			nMax[i] = nMax[i] + mathist.at<float>(nMaxIndx[i] - 2) + mathist.at<float>(nMaxIndx[i] - 1)
				+ mathist.at<float>(nMaxIndx[i] + 1) + mathist.at<float>(nMaxIndx[i] + 2);
			mathist.at<float>(nMaxIndx[i] - 2) = 0;
			mathist.at<float>(nMaxIndx[i] - 1) = 0;
			mathist.at<float>(nMaxIndx[i] + 1) = 0;
			mathist.at<float>(nMaxIndx[i] + 2) = 0;
			dbini[i][1] = mathist.at<float>(nMaxIndx[i] + 3) / nMax[i];
		}
		else if (nMaxIndx[i] == 255)
		{
			nMax[i] = nMax[i] + mathist.at<float>(nMaxIndx[i] - 1) + mathist.at<float>(nMaxIndx[i] - 2)
				+ mathist.at<float>(nMaxIndx[i] - 3) + mathist.at<float>(nMaxIndx[i] - 4);
			mathist.at<float>(nMaxIndx[i] - 1) = 0;
			mathist.at<float>(nMaxIndx[i] - 2) = 0;
			mathist.at<float>(nMaxIndx[i] - 3) = 0;
			mathist.at<float>(nMaxIndx[i] - 4) = 0;
			dbini[i][0] = mathist.at<float>(nMaxIndx[i] - 5) / nMax[i];
		}
		else if (nMaxIndx[i] == 254)
		{
			nMax[i] = nMax[i] + mathist.at<float>(nMaxIndx[i] + 1) + mathist.at<float>(nMaxIndx[i] - 1)
				+ mathist.at<float>(nMaxIndx[i] - 2) + mathist.at<float>(nMaxIndx[i] - 3);
			mathist.at<float>(nMaxIndx[i] + 1) = 0;
			mathist.at<float>(nMaxIndx[i] - 1) = 0;
			mathist.at<float>(nMaxIndx[i] - 2) = 0;
			mathist.at<float>(nMaxIndx[i] - 3) = 0;
			dbini[i][0] = mathist.at<float>(nMaxIndx[i] - 4) / nMax[i];
		}
		else if (nMaxIndx[i] == 253)
		{
			nMax[i] = nMax[i] + mathist.at<float>(nMaxIndx[i] + 1) + mathist.at<float>(nMaxIndx[i] + 2)
				+ mathist.at<float>(nMaxIndx[i] - 1) + mathist.at<float>(nMaxIndx[i] - 2);
			mathist.at<float>(nMaxIndx[i] + 1) = 0;
			mathist.at<float>(nMaxIndx[i] + 2) = 0;
			mathist.at<float>(nMaxIndx[i] - 1) = 0;
			mathist.at<float>(nMaxIndx[i] - 2) = 0;
			dbini[i][0] = mathist.at<float>(nMaxIndx[i] - 3) / nMax[i];
		}
		else
		{
			nMax[i] = nMax[i] + mathist.at<float>(nMaxIndx[i] - 2) + mathist.at<float>(nMaxIndx[i] - 1)
				+ mathist.at<float>(nMaxIndx[i] + 1) + mathist.at<float>(nMaxIndx[i] + 2);
			mathist.at<float>(nMaxIndx[i] - 2) = 0;
			mathist.at<float>(nMaxIndx[i] - 1) = 0;
			mathist.at<float>(nMaxIndx[i] + 1) = 0;
			mathist.at<float>(nMaxIndx[i] + 2) = 0;
			dbini[i][0] = mathist.at<float>(nMaxIndx[i] - 3) / nMax[i];
			dbini[i][1] = mathist.at<float>(nMaxIndx[i] + 3) / nMax[i];
		}
	}
	int nCount = 0;
	double MaxValue = 0;
	int MaxHist = 0;
	double SearchValue = sumPixle / 8 * sColorStripRatio;
	for (int i = 0; i < 8; i++)
	{
		mathist.at<float>(nMaxIndx[i]) = nMax[i];
		if (MaxValue < nMax[i])
		{
			MaxValue = nMax[i];
			MaxHist = nMaxIndx[i];
		}
		if (nMax[i] < SearchValue)
		{
			continue;
		}
		if (nMaxIndx[i] == 0 || nMaxIndx[i] == 1 || nMaxIndx[i] == 2)
		{
			if (dbini[i][1] < 0.2)
			{
				nCount++;
			}
		}
		else if (nMaxIndx[i] == 255 || nMaxIndx[i] == 254 || nMaxIndx[i] == 253)
		{
			if (dbini[i][0] < 0.2)
			{
				nCount++;
			}
		}
		else
		{
			if (dbini[i][0] < 0.2 && dbini[i][1] < 0.2)
			{
				nCount++;
			}
		}

	}

	if (MaxHist == 0)
	{
		MaxValue += mathist.at<float>(1) + mathist.at<float>(2) + mathist.at<float>(3) + mathist.at<float>(4) + mathist.at<float>(5) + mathist.at<float>(6);
	}
	else if (MaxHist == 1)
	{
		MaxValue += mathist.at<float>(0) + mathist.at<float>(2) + mathist.at<float>(3) + mathist.at<float>(4) + mathist.at<float>(5) + mathist.at<float>(6);
	}
	else if (MaxHist == 2)
	{
		MaxValue += mathist.at<float>(0) + mathist.at<float>(1) + mathist.at<float>(3) + mathist.at<float>(4) + mathist.at<float>(5) + mathist.at<float>(6);
	}
	else if (MaxHist == 3)
	{
		MaxValue += mathist.at<float>(0) + mathist.at<float>(1) + mathist.at<float>(2) + mathist.at<float>(4) + mathist.at<float>(5) + mathist.at<float>(6);
	}
	else if (MaxHist == 255)
	{
		MaxValue += mathist.at<float>(254) + mathist.at<float>(253) + mathist.at<float>(252) + mathist.at<float>(251) + mathist.at<float>(250) + mathist.at<float>(249);
	}
	else if (MaxHist == 254)
	{
		MaxValue += mathist.at<float>(255) + mathist.at<float>(253) + mathist.at<float>(252) + mathist.at<float>(251) + mathist.at<float>(250) + mathist.at<float>(249);
	}
	else if (MaxHist == 253)
	{
		MaxValue += mathist.at<float>(255) + mathist.at<float>(254) + mathist.at<float>(252) + mathist.at<float>(251) + mathist.at<float>(250) + mathist.at<float>(249);
	}
	else if (MaxHist == 252)
	{
		MaxValue += mathist.at<float>(255) + mathist.at<float>(254) + mathist.at<float>(253) + mathist.at<float>(251) + mathist.at<float>(250) + mathist.at<float>(249);
	}
	else
	{
		MaxValue += mathist.at<float>(MaxHist - 1) + mathist.at<float>(MaxHist - 2) + mathist.at<float>(MaxHist - 3) + mathist.at<float>(MaxHist + 1) + mathist.at<float>(MaxHist + 2) + mathist.at<float>(MaxHist + 3);
	}
	double bini = bini = MaxValue / sumPixle;
	int blackI = 999;
	int tempI = 999;

	if (nCount >= scountMin)
	{
		*result = 1;
	}
	else if (nCount == 1 && bini > sColorSceneRatio)
	{
		*result = 2;
		float tempF = -1;
		/*int tempI =999;*/
		static int imageheight = SrcImgG1.size().height;
		static int imagewidth = SrcImgG1.size().width;
		for (int i = 0; i < 256; i++)
		{
			if (tempF < mathist_bak.at<float>(i))
			{
				tempF = mathist_bak.at<float>(i);
				tempI = i;
			}
		}
		blackI = tempI;

		if (tempI < sTellThisBlack)
		{
			*result = 4;
		}


	}
	else if (bCheckStill && snFrames > 0)
	{
		double dresult = compareHist(mathist_bak, sPreHistMat, HISTCMP_CORREL);
		if (dresult > sStaticFrameRatio)
		{
			*result = 3;
		}
	}
	if (bCheckStill)
	{
		sPreHistMat = mathist_bak.clone();
	}

	if (((*result) | 0x00) > 0)
	{
		{


			stVideoDetectDetails.dCount = nCount;
			stVideoDetectDetails.dCountMin = scountMin;
			stVideoDetectDetails.nDetectBlackValue = tempI;
			stVideoDetectDetails.dBini = bini;
			stVideoDetectDetails.dColorSceneRatio = sColorSceneRatio;
			stVideoDetectDetails.dTellThisBlack = sTellThisBlack;
		}
	}

	snFrames++;
	return true;
}


int RawUYVY2Y(const unsigned char* pSrc, unsigned char* pDst, int rows, int cols, int channels)
{
	const unsigned char * pend = pSrc + rows * cols * channels;

	while (pSrc < pend)
	{
		*pDst = *(pSrc + 1);
		pDst++;
		pSrc += 2;
	}

	return *(pend - 1);
}

bool autodetect::Detect_Hist_UYVY(unsigned char* pBuffer, int nBufferLen, int nWidth, int nHeight, long* result, STVideoDetectDetails& stVideoDetectDetails, bool bCheckStill)
{
	//unsigned char* pBufferY = new unsigned char[nWidth * nHeight];
//注释掉，转换过程太慢了
//RawUYVY2Y(pBuffer, pBufferY, nHeight, nWidth, 2);

//一个像素2通道
	Mat SrcImgMat(nHeight, nWidth, CV_8UC2, pBuffer);
	bool bRet = Analysis_hist_Ver2(SrcImgMat, bCheckStill, result, pBuffer, stVideoDetectDetails);
	//delete[]pBufferY;
	//pBufferY = NULL;
	return bRet;
}
