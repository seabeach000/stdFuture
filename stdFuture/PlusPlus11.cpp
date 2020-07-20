#include "stdafx.h"
#include "PlusPlus11.h"
#include <iostream>
#include <functional>
#include <list>
#include <string>
#include <vector>
#include <array>
#include <map>

#include <chrono>

#include <cctype>

using namespace std;

class base {
public:
	void func()
	{
		cout << "func1()" << endl;
	}
	void func(int x)
	{
		cout << "func2()" << endl;
	}
	void func10()
	{
		cout << "func10()" << endl;
	}
};

class son : public base {
public:
	using base::func;    //��û�д˾䣬func()��func(int x)���ᱻ����
	void func(int x, int y)
	{
		cout << "func()3" << endl;
	}
};

void CPlusPlus11::overhide()
{
	base a;
	a.func();
	a.func(1);
	son b;
	b.func(1, 1);
	b.func();
	b.func(1);
	b.func10(); //ͬ�����ǣ������ͬ������ֱ�ӵ��û���ĺ���
}

void CPlusPlus11::typeID()
{
	class Base { };
	struct STU { };
		//��ȡһ����ͨ������������Ϣ
		int n = 100;
		const type_info &nInfo = typeid(n);
		cout << nInfo.name() << " | " << nInfo.raw_name() << " | " << nInfo.hash_code() << endl;
		//��ȡһ����������������Ϣ
		const type_info &dInfo = typeid(25.65);
		cout << dInfo.name() << " | " << dInfo.raw_name() << " | " << dInfo.hash_code() << endl;
		//��ȡһ�������������Ϣ
		Base obj;
		const type_info &objInfo = typeid(obj);
		cout << objInfo.name() << " | " << objInfo.raw_name() << " | " << objInfo.hash_code() << endl;
		//��ȡһ�����������Ϣ
		const type_info &baseInfo = typeid(Base);
		cout << baseInfo.name() << " | " << baseInfo.raw_name() << " | " << baseInfo.hash_code() << endl;
		//��ȡһ���ṹ���������Ϣ
		const type_info &stuInfo = typeid(struct STU);
		cout << stuInfo.name() << " | " << stuInfo.raw_name() << " | " << stuInfo.hash_code() << endl;
		//��ȡһ����ͨ���͵�������Ϣ
		const type_info &charInfo = typeid(char);
		cout << charInfo.name() << " | " << charInfo.raw_name() << " | " << charInfo.hash_code() << endl;
		//��ȡһ�����ʽ��������Ϣ
		const type_info &expInfo = typeid(20 * 45 / 4.5);
		cout << expInfo.name() << " | " << expInfo.raw_name() << " | " << expInfo.hash_code() << endl;
}

void CPlusPlus11::generalTest()
{
	int rate1 = 73;
	int rate2 = 159;
	float exponential = rate1 / 32.0 - 2;
	double tmp = pow(10, exponential);

	float exponential_1 = rate1 + 1 / 32.0 - 2;
	double tmp1 = pow(10, exponential_1);
	float exponential_2 = rate1 / 32.0 - 2;
	double tmp2 = pow(10, exponential_2);
	double tmp3 = 256 * tmp1 * tmp2;
	double tmp4 = rate2 / tmp3;

	int  speedvalue = (int)ceil(tmp + tmp4);
	std::cout << speedvalue << endl;
}

CPlusPlus11::CPlusPlus11()
{
}


CPlusPlus11::~CPlusPlus11()
{
}

int add(int i, int j)
{
	return i + j;
}
int foo() { 
	cout << "foo()" << endl;
	return 1;
};


template<class U, class V>                  //decltype(u*v)�����Ǻ����ķ���ֵ����auto������
auto Multiply(U u, V v) -> decltype(u*v)    // Note -> after the function bracet.  
{
	return u*v;
}

void CPlusPlus11::decltypeTest()
{
	typeID();

	decltype(add(5, 6)) var = 5;   //decltype(add(5, 6)) ��ʾ����add�����ķ������ͣ�����int
	cout << typeid(var).name() << endl; // This will print int

	//////////////////////////////////////////////////////////////////////////
	struct M { double x; };

	double pi = 3.14;
	const M* m = new M();
	decltype((m->x)) piRef = pi;
	cout << typeid(piRef).name() << endl; // This will print int
	// Note: Due to the inner bracets the inner statement is evaluated as expression,  
	// rather than member 'x' and as type of x is double and as this is lvale  
	// the return of declspec is double& and as 'm' is a const pointer   
	// the return is actually const double&.  
	// So the type of piRef is const double& 

	//////////////////////////////////////////////////////////////////////////
	//int foo() {};
	decltype(foo()) x; // x is an int and note that   
					   // foo() is not actually called at runtime 
	                   //����ִ�б��ʽ������auto�ͻ�
	x = 10;
	//////////////////////////////////////////////////////////////////////////
}

void CPlusPlus11::autoTest()
{
	/////////////////////////////////////////////////////////////////////////////
	//wxg20170330
	std::map<int, int64_t>  send_to_consumers_delays;
	send_to_consumers_delays[123] = 123;
	send_to_consumers_delays[124] = 124;
	send_to_consumers_delays.erase(123);

	/////////////////////////////////////////////////////////////////////////////
	//wxg20170321
	int MAX_THREADS = 16;
	int count = 4;
	std::array<std::vector<int>, 16> jobs;
	for (int n = 0; n < count; ++n)
		jobs[n*MAX_THREADS / count].push_back(n);
	for (int i = 0;i<MAX_THREADS;++i)
	{
		for (auto k:jobs[i])  //jobs[i]��һ��vector������ֻ��һ��Ԫ�أ����Ա���һ��
		{
			std::cout << "k= " << k << " jobs[" << i << "]= " << jobs[i][0] << std::endl;
		}
	}
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	//vec.insert()
	//vec.erase()
	cout << vec.front() << " " << vec.back() << endl;
	//��vector����Ķ�������һ�飬��������Ϊvector����ֻ��һ��Ԫ��
	std::fill(vec.begin(), vec.end(), -1);
	for (auto kk:vec)
	{
		cout << kk << endl;
	}
	////////////////////////////////////////////////////////////////
	auto a = 12;
	auto b = 12.0f;
	auto c = true;
	auto d = [](int x)->int { return 12; };
	auto e = std::bind(&foo/*, std::placeholders::_1*/);
	e();
	//template<typename T>
	//using Tlist = std::list<T>;
	using Tlist = std::list<char>;
	using df = void(*)();//�ȼ���typedef void(*df)()
}

//////////////////////////////////////////////////////////////////////////
std::string readFileContent()
{
	std::string filecontent = "oldContent";
	return filecontent;
}

//��ֵ���õ�����ͨ������Ϊ�������ã��ƶ����������ת��

void CPlusPlus11::stdmove()
{

	//��ֵ��ֵ����
	lValueRvalue();
	//����һ���˷ѣ������ķ���ֵ��������s�к�ջ�ϵ���ʱ�����ͻ������
	std::string s = readFileContent();

	//C++11
	//����ss�ڱ���ֵ��ʱ�򣬷���std::string::operator =(std::string&&)�ᱻ���ã�����&&����std::string��ı�д�ߣ�
	//����Ĳ�����һ����ʱ���󣬿���Ų�������ݣ�����std::string::operator =(std::string&&)��ʵ�ִ����У����ÿ��βΣ�
	//ͬʱ��ԭ�����������β��е������ƶ���������������ʱ������ֻҪ������Ϊ������Ҫ�����ݣ������Կ�����std::move�ƶ�
	std::string ss = std::move(readFileContent());

	string A("abc");
	string AA("abc");
	string&& Rval = std::move(A);
	string& Lval = AA;//std::move(AA);
	string B(Rval);    // this is a copy , not move.
	cout << A << endl;   // output "abc"
	string C(std::forward<string>(Rval));  // move.
	std::string D = std::forward<string>(Lval);  //����Ҳ��һ��move
	std::string E = std::forward<string>(B);  //move
	cout << A << endl;       /* output "" */
	cout << AA << endl;       /* output "" */

	string str = "asd";
	string& str1 = std::move(str);
	string str2 = std::move(str);

	//int &i = 6; // error��lvalue reference �����������泣��	
				// error: cannot bind non-const lvalue reference of type ��int&�� to an rvalue of type ��int��
	const int &j = 6; // ok�����Խ�һ����ʱ����󶨵�һ�� const ����ֵ����

	//X &ref_a = X(); 		// error
	//const X &ref_ca = X();	// ok�����Խ�һ����ʱ����󶨵�һ�� const ����ֵ����

	int &&rref = 6;		// ok��rvalue reference �������ã����泣��
	//X &&rref_a = X();	// ok��rvalue reference �������ã���ʱ����
}
template<typename T>
void swap(T& a, T& b)
{
	T t(std::move(a)); //aΪ�գ�tռ��a�ĳ�ʼ����
	a = std::move(b);  //bΪ�գ�aռ��b�ĳ�ʼ����
	b = std::move(t);  //tΪ�գ�bռ��a�ĳ�ʼ����
}
//��֮��std::move��Ϊ���ܶ����ģ���ʽ��Ϊ�������������������������ʩ������C++11�е�STL���ܴ��������
//��ʹC++�û���Ȼ���Ҿ��еķ�ʽ�����룬��Ȼ�������°�STL�ȱ�׼���ǿ�������档

//////////////////////////////////////////////////////////////////////////

//��ֵ����ֵ�Ķ���
//��C++�У����Էŵ���ֵ������ = ��ߵ�����ֵ�����Էŵ���ֵ�������ұߵ�����ֵ����Щ�����ȿ��Ե���ֵ�ֿ��Ե���ֵ��
//��һ����������ֵΪLvalue����ʵL����Location����ʾ���ڴ��п���Ѱַ�����Ը�����ֵ������const����Ҳ����Ѱַ�����ǲ��ܸ�ֵ����
//Rvalue�е�R����Read�����ǿ���֪������ֵ��
//��ֵ����&����ֵ����&&
//��ֵ����������Ϊ&����ֵ����������Ϊ&&����C++�У���ʱ��������Ϊ��ֵ�����ǿ�����Ϊ��������const &
//{
	double b = 1.2;
	//int& a = b; //������Ϊ���ַ�ʽ������һ����ʱ����������ʱ�������г��ԣ�Ҳ����˵a���õ��Ǵ��г��Ե���ʱ���� 
	const int& a = b;//������Ҫ��const���Σ���ʱ��a�������ʱ���������֣���b��û�й�ϵ��������ô�޸�b��������Ӱ��a����Ȼa�����ܱ��޸�
//}
void print_lvalue(int& i)
{
	cout << "lvalue:" << i << endl;
}
void print_rvalue(int&& i)
{
	cout << "rvalue:" << i << endl;
}
struct X
{
};
void inner0(const X&)
{
	cout << "inner(const X&)" << endl;
}
void inner0(X&&) { cout << "inner0(X&&)" << endl; }
template<typename T>
void outer0(T&& t) { inner0(forward<T>(t)); }

void CPlusPlus11::lValueRvalue()
{
	stdforward();

	int i = 0;
	print_lvalue(i);
	//print_rvalue(i);  //�޷�����ֵ���ð󶨵���ֵ
	print_rvalue(10);
	//print_lvalue(1);    //�ǳ������õĳ�ʼֵ����Ϊ��ֵ
	//���i��������ʹ���ˣ�ϣ��������ֵ���ݳ�ȥ������std::move��Ϊ�����ṩ�˽���ֵ����ת��Ϊ��ֵ���õķ�����
	print_rvalue(std::move(i));  

	//��������ֵa������ֵX()������������std::move������
	//��ʵ�ֶ���������������ֵ���ã���ֵ��һ�֣������ϱ�׼�иú����Ķ���
	X a;
	X&& b = std::move(a);
	X&& c = std::move(X());

	//��������ֵa������ֵX()�����������ô�����ֵ���ò����ĺ���ģ��outer��
	//ֻҪ��outer������ʹ��std::forward����ת��������
	//���ܱ�������������ֵ���ԣ��Ӷ�ʵ���˺���ģ�����������ת��
	outer0(a);
	outer0(X());
	inner0(forward<X>(X()));
}
//////////////////////////////////////////////////////////////////////////
//template <typename T> 
//struct Identity
//{
//	typedef T type;
//};
//template <typename T> 
//T&& Forward(typename Identity<T>::type&& t)
//{
//	return (T&&)t;
//}
// Disables template argument deduction from Forward helper
template<class T>
struct Identity
{
	// Map T to type unchanged
	typedef T Type;
};

template<class T>
inline T&& Forward(typename Identity<T>::Type& arg) throw()
{
	// Forward arg, given explicitly specified Type parameter
	return (T&&)arg;
}
void inner(int&,int&)
{
	cout << "inner(int&,int&)" << endl;
}
void inner(int&, const int&) 
{
	cout << "inner(int&, const int&)" << endl;
}
void inner(const int&, int&) {
	cout << "inner(const int&, int&)" << endl;
}
void inner(const int&, const int&) {
	cout << "inner(const int&, const int&)" << endl;
}
template <typename T1, typename T2> 
void outer(T1&& t1, T2&& t2) {
	inner(std::forward<T1>(t1), Forward<T2>(t2));
}

void CPlusPlus11::stdforward()
{
	std::string wcmd;
	//std::getline(std::wcin, wcmd); // TODO: It's blocking...
	wcmd = "000����";
	cout << wcmd << endl;
	int a = 1;
	const int b = 2;
	cout << "Directly calling inner()." << endl;
	inner(a, a);
	inner(b, b);
	inner(3, 3);
	inner(a, b);
	inner(b, a);
	inner(a, 3);
	inner(3, a);
	inner(b, 3);
	inner(3, b);
	cout << endl << "Calling outer()." << endl;
	outer(a, a);
	outer(b, b);
	outer(3, 3);
	outer(a, b);
	outer(b, a);
	outer(a, 3);
	outer(3, a);
	outer(b, 3);
	outer(3, b);
}

void CPlusPlus11::variableArray(unsigned int x, unsigned int y)
{
	const int t = 10;
	int a[t];
}

typedef std::chrono::high_resolution_clock c_t;
using namespace std::chrono;
void CPlusPlus11::stdtime()
{
	auto time1(c_t::now());
	int64_t a = 8e9l;
	cout << "a = " << a << endl;

	static const double PI = std::atan(1.0)*4.0;
	static const double H_PI = std::atan(1.0)*2.0;

	std::wstring audio_layouts = lrReturn();
	//wcout << audio_layouts << endl;

	std::wstring name = audio_layouts;
	std::transform(name.begin(), name.end(), name.begin(), std::tolower);
	//wcout << name << endl;

	system_clock::time_point frame_start_time = (system_clock::time_point)(
		duration_cast<seconds>(system_clock::now().time_since_epoch() + seconds{ 5 }));
	int64_t timeout = (uint64_t)duration_cast<nanoseconds>(
		(frame_start_time).time_since_epoch()).count();
	system_clock::time_point frame_start_time01 = (system_clock::time_point)(
		duration_cast<seconds>(system_clock::now().time_since_epoch() + milliseconds{ 5000 }));
	int64_t timeout01 = (uint64_t)duration_cast<nanoseconds>(
		(frame_start_time01).time_since_epoch()).count();

	cout << " timeout " << timeout << " timeout01 " << timeout01 << " delta " << timeout - timeout01 <<endl;

}

std::wstring CPlusPlus11::lrReturn()
{
	return LR"(
		<audio>
			<channel-layouts>
				<channel-layout name="mono"        type="mono"        num-channels="1" channel-order="FC" />
				<channel-layout name="stereo"      type="stereo"      num-channels="2" channel-order="FL FR" />
			</channel-layouts>			
		</audio>
	)";
}

