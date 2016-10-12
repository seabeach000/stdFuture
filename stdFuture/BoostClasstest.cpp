#include "stdafx.h"
#include "BoostClasstest.h"
#include <boost/thread/thread.hpp>
#include <boost/function/function0.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>

#include <boost/lexical_cast.hpp>
#include "../utility/utf8conv.h"

//using namespace boost;

CBoostClasstest::CBoostClasstest()
{
}


CBoostClasstest::~CBoostClasstest()
{
}

void CBoostClasstest::hello()
{
	std::cout << "Hello world, I'm a thread !" << std::endl;
}

void CBoostClasstest::helloWorld(std::string& str)
{
	std::cout << str << std::endl;
}

int CBoostClasstest::simpleThread()
{
	boost::thread thrd(&CBoostClasstest::hello,this);  //这就有个问题，怎么绑定hello的重载函数呢？
	thrd.join();

	thrd = boost::thread(&CBoostClasstest::hello,this);
	thrd.join();

	boost::function0<void> f = boost::bind(&CBoostClasstest::hello, this);
	boost::thread thrd0(f);
	thrd0.join();
	thrd0.join();  //验证多次join会不会有问题

	boost::thread testThread;
	testThread.join();  //验证现场没有启动会不会等待

	return 0;
}

void CBoostClasstest::FileParser(const std::wstring& strFileName)
{
	namespace fs = boost::filesystem;
	using namespace boost::property_tree;
	boost::property_tree::wptree pt;
	std::wstring strFileNameTem = _T("FamousServer.config");	
	try
	{
		auto initialPath = fs::initial_path<fs::path>().wstring();
		std::wifstream file(initialPath + _T("\\") + strFileNameTem);
		//boost::property_tree::read_xml(file, pt, boost::property_tree::xml_parser::trim_whitespace | boost::property_tree::xml_parser::no_comments);
		boost::property_tree::read_xml(file, pt, boost::property_tree::xml_parser::trim_whitespace);
		auto paths = pt.get_child(L"configuration.paths");
		std::wstring mediaPath = paths.get<std::wstring>(L"media-path", L"F:\\clips");
		std::wcout << mediaPath << std::endl;

		paths.put(L"media-path", L"M:\\clips");
		std::wstring mediaPath01 = paths.get<std::wstring>(L"media-path", L"F:\\clips");
		std::wcout << mediaPath01 << std::endl;
		xml_parser::xml_writer_settings<std::wstring> settings(' ', 3 , _T("utf-8"));
		//std::wstringstream fileName(initialPath + _T("\\") + strFileNameTem);
		std::string fileName = utf8util::UTF8FromUTF16(initialPath + _T("\\") + strFileNameTem);
		//std::wcout << fileName.str().c_str() << std::endl;
		pt.put_child(L"configuration.paths",paths);
		boost::property_tree::xml_parser::write_xml(fileName, pt,std::locale(),settings);

	}
	catch (...)
	{
		std::wcout << L" ### Invalid configuration file. ###";
		throw;
	}

}

template <typename ElemT>
struct HexTo {
	ElemT value;
	operator ElemT() const { return value; }
	friend std::wistream& operator >> (std::wistream& in, HexTo& out) {
		in >> std::hex >> out.value;
		return in;
	}
};
void CBoostClasstest::Convert16StringTodata()
{
	int x = boost::lexical_cast<HexTo<int>>(L"10");
	int a = 0;
}
