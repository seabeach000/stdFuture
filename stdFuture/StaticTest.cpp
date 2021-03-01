#include "stdafx.h"
#include "StaticTest.h"
#include <iostream>
#include <map>

struct MediaData {

	bool isInterlaced = false;

	// video related parameters
	uint16_t              fps;
	uint16_t              w;
	uint16_t              h;
	int					 tp_mode;
	uint16_t              video_payload_type;
	int                   video_sample_rate;
	// audio related parameters
	uint32_t              audio_ptime_us;
	int                   channels_num;
	uint16_t              bit_depth;
	int                   audio_sample_rate;
	uint16_t              audio_payload_type;
	// ancillary related parameters
	uint16_t              ancillary_payload_type;
	uint16_t              did;
	uint16_t              sdid;

	std::string src_ip, mc_ip, mc_src_ip;
	uint16_t src_port;
	int sample;
	int videobitdepth;
	int colorimetry;

	std::string		src_ip_a;
	std::string		mc_ip_a;
	uint16_t		src_port_a;

	std::string		src_ip_vanc;
	std::string		mc_ip_vanc;
	uint16_t		src_port_vanc;
	int vpid_code = 133;
};

int CStaticTest::x = 100;

CStaticTest::CStaticTest()
{
}


CStaticTest::~CStaticTest()
{
	std::cout << "~CStaticTest()" << std::endl;
}

void CStaticTest::localStatic(void)
{
	static int i = 0;
	std::cout << "i:" << i << '\n';
	i++;
	x++;
	std::cout << "x:" << x << '\n';
}

void CStaticTest::mapTest()
{
	std::wstring strRet = L"8145";
	int mode = 3;//实现时获取相应值
	wchar_t buf[3] = { 0 };
	swprintf(buf, 3, L"%02x", mode);
	strRet += buf;

	std::map<int, std::wstring> student;
	student.insert(std::make_pair(1, _T("zhangsan")));
	student.insert(std::make_pair(2, _T("lisi")));
	student.insert(std::make_pair(3, _T("wanger")));
	student.insert(std::make_pair(4, _T("zhaowu")));
	//还可以这样
	student[5] = L"liuliu";

	auto stu = student.begin();  //迭代器像一个指针一样
	std::wstring ddd = stu->second;
	student.erase(3);
	for (auto &ss:student)
	{
		std::wcout << ss.first << L" " << ss.second.c_str();
	}
}


struct MediaDataAA {

	bool isInterlaced = false;

	// video related parameters
	uint16_t              fps;
	//int					 tp_mode;
	//uint16_t              video_payload_type;
	//int                   video_sample_rate;

	//std::string src_ip;
	uint16_t src_port;
	int sample;

};
void CStaticTest::vectorfuzhi()
{
	MediaDataAA media_data0;
	MediaData media_data = {};
	int a = sizeof(MediaData);
	int b = sizeof(media_data);
	int c = sizeof(std::string);
	int d = sizeof(bool);
	int e = sizeof(MediaDataAA);
	memset(&media_data, 0, sizeof(media_data)); //linux 下面加上这句话 不让负值，奇怪
	media_data.src_ip = "1122";
	media_data.mc_ip = "2255";
	vectortest(media_data);
}

void CStaticTest::vectortest(MediaData &media_data)
{
	media_data.src_ip = "1122";
	media_data.mc_ip = "2255";
}
