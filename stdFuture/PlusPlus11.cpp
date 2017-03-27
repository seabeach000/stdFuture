#include "stdafx.h"
#include "PlusPlus11.h"
#include <iostream>
#include <functional>
#include <list>
#include <string>
#include <vector>
#include <array>
using namespace std;
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
	//wxg20170321
	int MAX_THREADS = 16;
	int count = 4;
	std::array<std::vector<int>, 16> jobs;
	for (int n = 0; n < count; ++n)
		jobs[n*MAX_THREADS / count].push_back(n);
	for (int i = 0;i<MAX_THREADS;++i)
	{
		for (auto k:jobs[i])
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

//void variableArray(int x, int y)
//{
//	int t = 0;
//	std::cin >> t;
//	int b[10];
//}