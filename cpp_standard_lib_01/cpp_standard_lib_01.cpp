// cpp_standard_lib_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

/**
 * c++路线：标准库
 */
using namespace std;
/**
 * g++编译器基本使用示例 g++ -std=c++14 thread.cpp -o thread -pthread  （手动链接thread库）
 */
#include <algorithm> 
void* doo = nullptr;
/**
 * 自带算法
 */
void test_minmax() {
	//基本比较函数
	cout << "std::min(2011, 2014):\t\t\t ";
	cout << std::min(2011, 2014) << "\n";                           // 2011
	cout << "std::min({3, 1, 2011, 2014, -5}):\t";
	cout << std::min({ 3, 1, 2011, 2014, -5 }) << "\n";               // -5
	//lambda函数定义比较规则，这里取绝对值
	cout << "std::min(-10, -5, [](...) {...}):\t\t";
	cout << std::min(-10, -5, [](int a, int b)
		{ return std::abs(a) < std::abs(b); }) << "\n\n";

	std::pair<int, int> pairInt = std::minmax(2011, 2014);
	auto pairSeq = std::minmax({ 3, 1, 2011, 2014, -5 });
	auto pairAbs = std::minmax({ 3, 1, 2011, 2014, -5 }, [](int a, int b)
		{ return std::abs(a) < std::abs(b); });
	//返回pair
	cout << "pairInt.first, pairInt.second:\t\t";
	cout << pairInt.first << ", " << pairInt.second << "\n"; // 2011,2014
	cout << "pairSeq.first, pairSeq.second:\t\t";
	cout << pairSeq.first << ", " << pairSeq.second << "\n";  // -5,2014
	cout << "pairAbs.first, pairAbs.second:\t\t ";
	cout << pairAbs.first << ", " << pairAbs.second << "\n";  // 1,2014
}
/**
 * move和copy
 * std::move会把尝试把参数转为右值引用，将资源移动；copy性能较低，是整体复制
 * copy可能会因内存不足导致分配空间失败；而move后的源将处于“有效但未指定”状态
 * 如果编译器无法进行move，则会使用copy
 *
 * 移动语义具有两个优点。首先，节约性能，不需要多余的内存分配和释放。其次，存在无法复制的对象，例如线程或锁。
 */
#include <utility>
void test_move_and_copy() {
	std::string str1 = "abcd";
	std::string str2 = "efgh";
	std::cout << "str1: " << str1 << std::endl;
	std::cout << "str2: " << str2 << "\n\n";

	// Copying
	str2 = str1;             // copy semantic
	std::cout << "After copying" << std::endl;
	std::cout << "str1: " << str1 << std::endl;
	std::cout << "str2: " << str2 << "\n\n";

	str1 = "abcd";
	str2 = "efgh";

	// Moving 
	//移动操作后，str1为空。（不能保证，但通常是这样）
	//使用函数std::move明确请求了移动语义。
	//如果确定不再需要移动语义的源，则编译器将自动执行移动语义。
	str2 = std::move(str1);
	std::cout << "After moving" << std::endl;
	std::cout << "str1: " << str1 << std::endl;
	std::cout << "str2: " << str2 << "\n\n";
}
//对于自定义类，需要有对应的构造函数或赋值运算符重载才有对应的语义功能
class MyData {
	MyData(MyData&& m) = default; // move constructor
	MyData& operator = (MyData&& m) = default; // move assignment 
	MyData(const MyData& m) = default; // copy constructor
	MyData& operator = (const MyData& m) = default; // copy assignment
};
/**
 * std::forward
 * 工厂函数是创建对象的函数，因此必须相同地传递参数。
 * 构造函数通常使用其参数来使用相同的参数来初始化其基类。forward是通用库作者的常用工具
 * forward与可变参数模板结合使用可以定义完全通用的函数模板,可以接受任意数量的参数，并以不变的方式转发它
 */
struct MyData_2 {
	MyData_2(int, double, char) {};
};
//函数模板createT必须将其参数用作通用引用：Args&& …args`。通用引用或也称为转发引用是类型推导上下文中的右值引用
template <typename T, typename...  Args>
T createT(Args&&... args) {
	return T(std::forward<Args>(args)...);
}
#include <vector>
#include <initializer_list>
typedef std::vector<int> IntVec;
using std::initializer_list;
void test_forward() {
	int a = createT<int>();
	int b = createT<int>(1);
	std::string s = createT<std::string>("Only for testing.");
	MyData_2 myData = createT<MyData_2>(1, 3.19, 'a');
	IntVec intVec = createT<IntVec>(initializer_list<int>({ 1, 2, 3 }));
}
/**
 * std::swap
 * 使用move语义交换
 */
template <typename T>
inline void swap(T& a, T& b) {
	T tmp(std::move(a));
	a = std::move(b);
	b = std::move(tmp);
}
/**
 * std::bind
 * std::function
 *
 * c++11以后，一般使用lambda表达式直接代替bind，auto自动推导代替function
 *
 * 通过std::bind，可通过多种方式创建函数对象：
 * 将参数绑定到任意位置，
 * 改变参数的顺序，
 * 引入占位符作为参数，
 * 调用新创建的函数对象，在STL的算法中使用它们或将它们存储在std::function中。
 */
#include <functional>
using namespace std::placeholders;
using std::bind;
using std::function;
double divMe(double a, double b) { return a / b; };
void test_bind_and_func() {
	function <double(double, double)> myDiv1 = bind(divMe, _1, _2);
	function <double(double)> myDiv2 = bind(divMe, 2000, _1);
	std::cout << (divMe(2000, 10) == myDiv1(2000, 10) == myDiv2(10));
}
//更多应用
#include <map>
using std::make_pair;
using std::map;
void test_function() {
	//用map做函数映射，可代替switch控制块
	map<const char, std::function<double(double, double)>> tab;
	tab.insert(make_pair('+', [](double a, double b) { return a + b; }));//lambda代替bind
	tab.insert(make_pair('-', [](double a, double b) { return a - b; }));
	tab.insert(make_pair('*', [](double a, double b) { return a * b; }));
	tab.insert(make_pair('/', [](double a, double b) { return a / b; }));

	std::cout << "3.5 + 4.5\t=  " << tab['+'](3.5, 4.5) << "\n";  //3.5 + 4.5	=  8
	std::cout << "3.5 - 4.5\t=  " << tab['-'](3.5, 4.5) << "\n";  //3.5 - 4.5	=  -1
	std::cout << "3.5 * 4.5\t=  " << tab['*'](3.5, 4.5) << "\n";  //3.5 * 4.5	=  15.75
	std::cout << "3.5 / 4.5\t=  " << tab['/'](3.5, 4.5) << "\n";  //3.5 / 4.5	=  0.777778
}
/**
 * std::pair
 * std::make_pair
 * 可构建任意类型对，常用于各种map中
 */
void test_pairs() {
	pair<const char*, double> charDoub("str", 3.14);
	pair<const char*, double> charDoub2 = make_pair("str", 3.14);
	auto charDoub3 = make_pair("str", 3.14);

	cout << charDoub.first << ", " << charDoub.second << "\n";    // str, 3.14
	charDoub.first = "Str";
	get<1>(charDoub) = 4.14;
	cout << charDoub.first << ", " << charDoub.second << "\n";    // Str, 4.14
}
//元组扩展到更多个元素
void test_elements() {
	//tuple是固定大小，泛化的pair
	std::tuple<std::string, int, float> tup1("first", 3, 4.17f);
	auto tup2 = std::make_tuple("second", 4, 1.1);

	int first = 1;
	int second = 2;
	int third = 3;
	int fourth = 4;
	cout << first << " " << second << " "
		<< third << " " << fourth << endl;          // 1 2 3 4

	auto tup = tie(first, second, third, fourth)      // bind the tuple
		= std::make_tuple(101, 102, 103, 104);   // create the tuple 
												 // and assign it
	cout << get<0>(tup) << " " << get<1>(tup) << " " << get<2>(tup)
		<< " " << get<3>(tup) << endl;              // 101 102 103 104
	cout << first << " " << second << " " << third << " "
		<< fourth << endl;                          // 101 102 103 104

	first = 201;
	get<1>(tup) = 202;
	cout << get<0>(tup) << " " << get<1>(tup) << " " << get<2>(tup)
		<< " " << get<3>(tup) << endl;              // 201 202 103 104
	cout << first << " " << second << " " << third << " "
		<< fourth << endl;                          // 201 202 103 104

	int a, b;
	tie(std::ignore, a, std::ignore, b) = tup;
	cout << a << " " << b << endl;                   // 202 104
}
/**
 * std::reference_wrapper
 */
void foo() {
	std::cout << "Invoked" << std::endl;
}
void test_ref_wrap() {
	typedef void callableUnit();
	std::reference_wrapper<callableUnit> refWrap(foo);

	refWrap(); // Invoked
}
/**
 * std::ref		将创建一个非常量引用包装
 * std::cref	将创建一个常量引用包装
 */
void invokeMe(const std::string& s) {
	std::cout << s << ": const " << std::endl;
}
template <typename T>
void doubleMe(T t) {
	t *= 2;
}
void test_ref() {
	std::string s{ "string" };
	invokeMe(std::cref(s));        // string

	int i = 1;
	std::cout << i << std::endl;   // 1
	doubleMe(i);
	std::cout << i << std::endl;   // 1
	doubleMe(std::ref(i));
	std::cout << i << std::endl;   // 2
}


int main()
{
	test_bind_and_func();
}
