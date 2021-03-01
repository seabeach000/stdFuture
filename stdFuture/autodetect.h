#pragma once
typedef struct _STVideoDetectDetails
{
	double dCount;
	double dCountMin;
	int	   nDetectBlackValue;
	double dColorSceneRatio;
	double dTellThisBlack;
	double dBini;
}STVideoDetectDetails;

class autodetect
{
	bool Detect_Hist_UYVY(unsigned char* pBuffer, int nBufferLen, int nWidth, int nHeight, long* result, STVideoDetectDetails& stVideoDetectDetails, bool bCheckStill);
};

