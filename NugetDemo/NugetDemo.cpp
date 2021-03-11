// NugetDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <json/json.h>
#include <fstream>
#include <cassert>

#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

std::string ConstructJsonString()
{
	Json::Value rootValue = Json::objectValue;
	rootValue["encoding"] = "UTF-8";
	rootValue["plug-ins"] = Json::arrayValue;
	rootValue["plug-ins"].append("python");
	rootValue["plug-ins"].append("c++");
	rootValue["plug-ins"].append("ruby");
	rootValue["indent"] = Json::objectValue;
	rootValue["indent"]["length"] = 3;
	rootValue["indent"]["use_space"] = true;

	return Json::FastWriter().write(rootValue);
}


std::string createJson(void)
{
	std::string jsonStr;
	Json::Value root, language, mail;
	Json::StreamWriterBuilder  writeBuilder;
	std::ostringstream os;

	//设置默认无格式化输出
	writeBuilder.settings_["indentation"] = "";
	root["Name"] = "Zhangsan";
	root["Age"] = 25;

	language[0] = "C";
	language[1] = "C++";
	root["Language"] = language;

	mail["QQ"] = "zhangsan@qq.com";
	mail["Google"] = "san.zhang@qq.com";
	root["E-mail"] = mail;

	root["Industry"] = "IT";


	// jsonWriter是智能指针, 当jsonWriter被析构时, 它所指向的对象(内存)也被自动释放
	std::unique_ptr<Json::StreamWriter> josnWriter(writeBuilder.newStreamWriter());
	josnWriter->write(root, &os);
	jsonStr = os.str();

	// 无格式化的输出
	std::cout << "Json-none:\n" << jsonStr << std::endl;
	// 格式化的输出
	std::cout << "Json-formatted:\n" << root.toStyledString() << std::endl;

	return jsonStr;
}

void saveJsonStringToFile(const char* file, std::string& jsonStr)
{
	std::ofstream ofs;
	ofs.open(file);
	assert(ofs.is_open());
	ofs << jsonStr;
	ofs.close();
}

bool parseJsonFromString(const std::string& josnStr)
{
	if (josnStr.empty())
	{
		return false;
	}

	bool res;
	JSONCPP_STRING errs;
	Json::Value root, language, mail;
	Json::CharReaderBuilder readerBuilder;

	std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
	res = jsonReader->parse(josnStr.c_str(), josnStr.c_str() + josnStr.length(), &root, &errs);
	if (!res | !errs.empty())
	{
		std::cout << "parseJsonFromString error! " << errs << std::endl;
		return false;
	}

	std::cout << "root.size() = " << root.size() << std::endl;

	std::cout << "Name: " << root["Name"].asString() << std::endl;
	std::cout << "Age: " << root["Age"].asInt() << std::endl;


	language = root["Language"];
	std::cout << "Language: ";
	for (int i = 0; i < language.size(); ++i)
	{
		std::cout << language[i].asString() << " ";
	}
	std::cout << std::endl;

	mail = root["E-mail"];
	std::cout << "E-mail: " << std::endl;
	std::cout << "QQ: " << mail["QQ"].asString() << std::endl;
	std::cout << "Google: " << mail["Google"].asString() << std::endl;

	std::cout << "Industry: " << root["Industry"].asString() << std::endl;

	return true;
}

std::string createJsonArray(void)
{
	std::string jsonStr;
	Json::Value root, person,language, mail;
	Json::StreamWriterBuilder  writeBuilder;
	std::ostringstream os;

	//设置默认无格式化输出
	writeBuilder.settings_["indentation"] = "";

	person["Name"] = "Zhangsan";
	person["Age"] = 25;

	language[0] = "C";
	language[1] = "C++";
	person["Language"] = language;

	mail["QQ"] = "zhangsan@qq.com";
	mail["Google"] = "san.zhang@gmail.com";
	person["E-mail"] = mail;

	person["Industry"] = "IT";

	root.append(person);


	person["Name"] = "Lisi";
	person["Age"] = 28;

	language[0] = "Chinese";
	language[1] = "English";
	person["Language"] = language;

	mail["QQ"] = "lisi@163.com";
	mail["Google"] = "si.li@gmail.com";
	person["E-mail"] = mail;

	person["Industry"] = "Finance";

	root.append(person);

	// jsonWriter是智能指针, 当jsonWriter被析构时, 它所指向的对象(内存)也被自动释放
	std::unique_ptr<Json::StreamWriter> josnWriter(writeBuilder.newStreamWriter());
	josnWriter->write(root, &os);
	jsonStr = os.str();

	// 无格式化的输出
	std::cout << "Json-array-none:\n" << jsonStr << std::endl;
	// 格式化的输出
	std::cout << "Json-array-formatted:\n" << root.toStyledString() << std::endl;

	return jsonStr;
}

bool parseJsonArrayFromString(const std::string &jsonStr)
{
	if (jsonStr.empty())
	{
		return false;
	}

	bool res;
	JSONCPP_STRING errs;
	Json::Value root, person,language, mail;
	Json::CharReaderBuilder readerBuilder;

	std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
	res = jsonReader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.length(), &root, &errs);
	if (!res | !errs.empty())
	{
		std::cout << "parseJsonArrayFromString error! " << errs << std::endl;
		return false;
	}
	   	 
	std::cout << "root.size() = " << root.size() << std::endl;

	for (int i = 0; i < root.size(); i++)
	{
		person = root[i];
		std::cout << "Name: " << person["Name"].asString() << std::endl;
		std::cout << "Age: " << person["Age"].asInt() << std::endl;

		language = person["Language"];
		std::cout << "Language";
		for (int i = 0;i<language.size();++i)
		{
			std::cout << language[i].asString() << " ";
		}
		std::cout << std::endl;

		mail = person["E-mail"];
		std::cout << "E-mail: " << std::endl;
		std::cout << "QQ: " << mail["QQ"].asString() << std::endl;
		std::cout << "Google: " << mail["Google"].asString() << std::endl;

		std::cout << "Industry: " << person["Industry"].asString() << std::endl;

	}

	return true;
}

void parseJsonArrayFromFile(const char* file)
{
	std::string line, jsonStr;
	std::ifstream ifs(file);

	assert(ifs.is_open());

	while (getline(ifs,line))
	{
		jsonStr.append(line);
	}
	ifs.close();

	parseJsonArrayFromString(jsonStr);
}
int main()
{
	std::string jsonStr;
	jsonStr = createJson();
	saveJsonStringToFile("json-none.json", jsonStr);


	std::cout << "**********************************" << std::endl;
	parseJsonFromString(jsonStr);
	std::cout << "**********************************" << std::endl;

	std::string jsonStrArray = createJsonArray();
	saveJsonStringToFile("json-none-array.json", jsonStrArray);
	std::cout << "**********************************" << std::endl;

	parseJsonArrayFromString(jsonStrArray);
	std::cout << "**********************************" << std::endl;

	parseJsonArrayFromFile("json-none-array.json");

	if (true)
	{
		Json::Value root,person;
		//std::ifstream ifs;
		//ifs.open("testjson.json"/*, std::ifstream::binary*/);
		//assert(ifs.is_open());
		std::ifstream ifs("testjson.json");
		ifs >> root;

		std::string name;

		name = root.get("name", "wangsi").asString();
		person = root["person"];

		int age;
		int size = person.size();
		for (int i = 0; i < size; ++i)
		{
			name = person[i]["name"].asString();
			age = person[i]["age"].asInt();
			std::cout << name << " " << age << std::endl;
		}
	}

	if (false)
	{
		//std::string strJson = "{\"name\" : \"xiaoy\",\"age\" :17}";
		//const char* s = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";

		std::string document = ConstructJsonString();
	}

    std::cout << "Hello World!\n";
	//system("pause");
 }

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
