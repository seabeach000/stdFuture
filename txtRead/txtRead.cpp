// txtRead.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include <locale>
#include <codecvt>

#include <chrono>
#include <sstream>

#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/thread/thread.hpp>
using namespace std;
using namespace boost::interprocess;

#define  CLIPNUMS 1000
int main(int argc, char *argv[])
{
	int64_t clipNums = CLIPNUMS;
	std::string targetClip = "100";
	if (argc >= 2)
		clipNums = stoi(argv[1]);
	if (argc >= 3)
		targetClip = argv[2];

	std::string fileName = "clipInfo.txt";
	///*
	wofstream file;
	file.open(fileName);
	if (file.fail())
	{
		cout << L"file open failed!" << endl;
		system("pause");
		return 0;
	}

	for (int i = 0; i < clipNums;i++)
	{
		std::wstring clipInfo = L"\"" + to_wstring(i+1) + L"\""
			+ L" " + L"MOVIE"
			+ L" " + L"93222996"
			+ L" " + L"20180813074419"
			+ L" " + L"508"
			+ L" " + L"1/25";
		file << clipInfo.c_str() << "\n";
	}

	file.close();
	file.clear();
	//*/
	
//以读方式打开文件
	auto tp_current01 = std::chrono::high_resolution_clock::now();

	///*
	std::ostringstream buffer;
	ifstream fileR;
	fileR.open(fileName/*,fstream::in|fstream::out|ios::app*/);
	if (fileR.fail())
		return 0;
	//fileR << "abcde " << endl;
	std::string text;
	//auto tp_current01 = std::chrono::high_resolution_clock::now();
	while (fileR.good())
	{
		//std::streampos smpos = fileR.tellg();
		getline(fileR, text, '\n');
		//cout << text << endl;
		int pos = text.find_last_of('\"');
		if (pos != std::string::npos)
		{
			string clipID = text.substr(1, pos-1);
			if (clipID == targetClip)
			{
				cout << text << endl;
				break;
				{
					//fileR.seekg(smpos);
					//std::string clipInfo1 = "\"" + to_string(999) + "\""
						//+ " " + "MOVIE"
						//+ " " + "93222996"
						//+ " " + "20180813074419"
						//+ " " + "508"
						//+ " " + "1/25";
					//fileR << clipInfo1 << endl;
					//和原来长度不一致时，不能完全覆盖。所以还得是删除掉。
					//break;
				}
			}
			else
				buffer << text << "\n";
		}
	}
	buffer << fileR.rdbuf(); //返回底层未处理的字符串设备对象
	fileR.close();
	//*/

	std::ofstream out(fileName);
	out << buffer.str();
	out.close();

	auto tp_current02 = std::chrono::high_resolution_clock::now();
	auto elapsedTime = tp_current02 - tp_current01;

	std::cout << "elapsedTime " << to_string(elapsedTime.count()) << endl;

	auto tp_current03 = std::chrono::high_resolution_clock::now();
	

	int loopcont = 0;
	do
	{
		wofstream fileW;
		fileW.open(fileName, std::ios::binary | std::ios::app);		
		if (1/*f_lock.try_lock()*/)  //加上锁之后，不能继续写入了
		{
			//boost::interprocess::file_lock f_lock(fileName.c_str());
			named_mutex Name_mutex(open_or_create, fileName.c_str());
			
			
			//f_lock.lock();
			//wofstream fileW;
			//fileW.open(fileName, ios::app);
			std::wstring clipInfo = L"\"" + to_wstring(999999) + L"\""
				+ L" " + L"MOVIE"
				+ L" " + L"93222996"
				+ L" " + L"20180813074419"
				+ L" " + L"508"
				+ L" " + L"1/25";

			//std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> conv(new std::codecvt<wchar_t, char, std::mbstate_t>("CHS"));
			//std::string strTmp2 = conv.to_bytes(clipInfo);

			//fileRW << strTmp2.c_str() << "\n";
			boost::interprocess::scoped_lock<named_mutex> e_lock(Name_mutex);
			wcout << L"begin write!" << endl;
			if (fileW.good())
			{
				fileW << clipInfo.c_str() << "\n";
				//fileW.write(clipInfo.c_str(), clipInfo.size());
			}
			//system("pause");
			fileW.flush();
			//f_lock.unlock();
			auto tp_current04 = std::chrono::high_resolution_clock::now();
			std::cout << "lock elapsedTime " << to_string((tp_current04 - tp_current03).count()) << endl;
			wcout << L"end write!" << endl;

			//boost::this_thread::sleep(boost::posix_time::seconds(20));
		}
		else
		{
			std::cout << L"file is locked by other process!";
		}

		fileW.close();

	} while (loopcont-- > 0);



	system("pause");

    return 0;
}

