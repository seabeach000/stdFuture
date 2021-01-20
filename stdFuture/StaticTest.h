#pragma once

class MediaData;

class CStaticTest
{
public:
	CStaticTest();
	virtual ~CStaticTest();
	void localStatic(void);
	void mapTest();
	void vectorfuzhi();
	void vectortest(MediaData &media_data);
public:
	static int x;
};

