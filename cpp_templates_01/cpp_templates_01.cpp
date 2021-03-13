// cpp_templates_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
/**
 * c++路线：
 * 模板
 */
void* foo = nullptr;
//关于constexpr
const int func() {
	return 10;//const 只表示值无法被直接修改，并不能表示就是常量
}
constexpr int func_constexpr() {
	return 10;
}
void test_constexpr() {
	//int arr[func()];//compile error
	int arr[func_constexpr()];
}
//模板函数
template<typename T>
void f(T s)
{
	std::cout << s << '\n';
}
//重载模板
template void f<double>(double); // instantiates f<double>(double)
template void f<>(char); // instantiates f<char>(char), template argument deduced
template void f(int); // instantiates f<int>(int), template argument deduced
//模板应用
template<int m, int n>
struct Power {
	static int const value = m * Power<m, n - 1>::value;
};

template<int m>
struct Power<m, 0> {
	static int const value = 1;
};
void test_template() {
	std::cout << Power<2, 10>::value << std::endl;
}
//模板类
template <typename T>
struct Base {
	void func_base() { cout << "Base" << endl; }
};
template <typename T>
struct Derived : Base<T> {
	using Base<T>::func_base;
	void func_derived() {
		//func_base();       // ERROR 模板类继承，子类不会自动提供基类方法
		//需要使用基类方法可以这样
		this->func_base();
		Base<T>::func_base();
		func_base();//加入using声明后，可直接使用
	}
};
void test_template_1() {
	Derived<int> d;
	d.func_derived();
}
//别名模板
template <typename T, int Line, int Col>
class Matrix {
};
template <typename T, int Line>
using Square = Matrix<T, Line, Line>;
template <typename T, int Line>
using Vector = Matrix<T, Line, 1>;
Matrix<int, 5, 3> ma;
Square<double, 4> sq;
Vector<char, 5> vec;
//各参数类型模板
template <typename T>
class ClassTemplate {
public:
	ClassTemplate() {
		std::cout << "typeid(T).name(): " << typeid(T).name() << std::endl;
	}
};
template < void(*func)(void) >
class AcceptFunction {
public:
	AcceptFunction() {
		std::cout << "AcceptFunction: " << typeid(func).name() << std::endl;
	}
};
void test_template_2() {
	ClassTemplate<int> clTempInt;
	ClassTemplate<double> clTempDouble;
	ClassTemplate<std::string> clTempString;
	AcceptFunction<test_template> tempFunc;
}
//模板模板
#include <initializer_list>
#include <list>
#include <vector>
template <typename T, template <typename, typename> class Cont >
class Matrix_TT {
public:
	explicit Matrix_TT(std::initializer_list<T> inList) : data(inList) {
		for (auto d : data) std::cout << d << " ";
	}
	int getSize() const {
		return data.size();
	}

private:
	Cont<T, std::allocator<T>> data;//可使用相同签名的容器类型，如vector、list等
};
void test_template_3() {
	Matrix_TT<int, std::vector> myIntVec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::cout << std::endl;
	std::cout << "myIntVec.getSize(): " << myIntVec.getSize() << std::endl;
}
//模板参数；默认类型
template <typename T, typename Pred = std::less<T>>
bool isSmaller(T fir, T sec, Pred pred = Pred()) {
	return pred(fir, sec);
}
template <typename R, typename T, typename U>
R add(T fir, U sec) {
	return fir + sec;
}
//模板专业化
class Account {};
template<typename T>
struct Type {
	std::string getName() const {
		return "unknown";
	}
};
template<typename T>
struct Type<T*> {
	std::string getName() const {
		return "pointer";
	}
};
template<typename T>
struct Type<const T> {
	std::string getName() const {
		return "const";
	}
};
template<>
struct Type<int> {
	std::string getName() const {
		return "int";
	}
};
template<>
struct Type<double> {
	std::string getName() const {
		return "double";
	}
};
template<>
struct Type<std::string> {
	std::string getName() const {
		return "std::string";
	}
};
template<>
struct Type<Account> {
	std::string getName() const {
		return "Account";
	}
};
//可变参数
template <typename... Args>
int printSize(Args... args) {
	return sizeof ...(args);
}

template<int ...>
struct Mult;

template<>
struct Mult<> {
	static const int value = 1;
};

template<int i, int ... tail>
struct Mult<i, tail ...> {
	static const int value = i * Mult<tail ...>::value;
};
void test_template_4() {
	std::cout << "printSize(): " << printSize() << std::endl;
	std::cout << "printSize(template,2011,true): " << printSize("template", 2011, true) << std::endl;
	std::cout << "printSize(1, 2.5, 4, 5, 10): " << printSize(1, 2.5, 4, 5, 10) << std::endl;

	std::cout << std::endl;

	std::cout << "Mult<10>::value: " << Mult<10>::value << std::endl;
	std::cout << "Mult<10,10,10>::value: " << Mult<10, 10, 10>::value << std::endl;
	std::cout << "Mult<1,2,3,4,5>::value: " << Mult<1, 2, 3, 4, 5>::value << std::endl;
}
//数据格式化输出例子
void myPrintf(const char* format)
{
	//适配循环最后无可变参数情况
	std::cout << format;
}
template<typename T, typename... Args>
void myPrintf(const char* format, T value, Args... args)
{
	for (; *format != '\0'; format++) {
		if (*format == '%') {
			std::cout << value;
			myPrintf(format + 1, args...);
			return;
		}
		std::cout << *format;
	}
}
void test_printf() {
	myPrintf("% world% %\n", "Hello", '!', 2011);
}
//折叠表达式 c++17
template<typename... Args>
bool all(Args... args) {
	return (true && ... && args);
}
template<typename... Args>
bool any(Args... args) { return (... || args); }
template<typename... Args>
bool none(Args... args) { return not(... || args); }
template<typename ...Args>
auto addStr(Args ... args) {
	return (std::string("0") + ... + args); // 字符串 串联
}
//模板中的友元
template <typename T, int N>
class Array {

public:
	Array() = default;

	template <typename T2, int M> friend class Array;

	template <typename T2>
	Array<T, N>& operator=(const Array<T2, N>& arr) {
		static_assert(std::is_convertible<T2, T>::value, "Cannot convert source type to destination type!");
		elem.clear();
		elem.insert(elem.begin(), arr.elem.begin(), arr.elem.end());
		return *this;
	}

	int getSize() const;

private:

	std::vector<T> elem;
};

template <typename T, int N>
int Array<T, N>::getSize() const {
	return N;
}
void test_template_5() {
	Array<double, 10> doubleArray{};
	Array<int, 10> intArray{};

	doubleArray = intArray;
}

//自动返回类型
template<typename T1, typename T2>
auto add_return_auto(T1 first, T2 second) -> decltype(first + second) {
	return first + second;
}

/*
The template recursion depth is limited.
模板递归深度
C++03: 17
C++11: 1024
*/
template <int N>
struct Factorial {
	static int const value = N * Factorial<N - 1>::value;
};
//模板递归计算阶乘；与函数递归的区别是，模板递归是编译期实例化不会造成运行时栈溢出，但递归层数过多会导致编译栈溢出，所以最好尽量避免使用递归
template <>
struct Factorial<1> {
	static int const value = 1;
};
//用于类型判断
#include<type_traits>
namespace rgr {

	template<class T, class U>
	struct is_same : std::false_type {};

	template<class T>
	struct is_same<T, T> : std::true_type {};

	template< class T >
	struct remove_const {
		typedef T type;
	};

	template< class T >
	struct remove_const<const T> {
		typedef T type;
	};
}
void test_rgr() {
	std::cout << std::is_same<int, std::remove_const<const int>::type>::value << std::endl;
	std::cout << rgr::is_same<int, rgr::remove_const<const int>::type>::value << std::endl;
}
//求最大公约数
template<typename T1, typename T2>
//typename std::conditional<(sizeof(T1) < sizeof(T2)), T1, T2>::type /*除了手动确定较小类型之外，还可以使用common_type确定所有类型都能隐式转换为的类型*/
typename std::common_type<T1, T2>::type
gcd(T1 a, T2 b) {
	static_assert(std::is_integral<T1>::value, "T1 should be integral!");
	static_assert(std::is_integral<T2>::value, "T2 should be integral!");
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}
//类型断言可以写在模板定义里
template<typename T1, typename T2,
	typename std::enable_if<std::is_integral<T1>::value, T1 >::type = 0,
	typename std::enable_if<std::is_integral<T2>::value, T2 >::type = 0,
	typename R = typename std::conditional<(sizeof(T1) < sizeof(T2)), T1, T2>::type>
	R gcd(T1 a, T2 b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}
//三种方式判断类型
// SFINAE
template <typename T, std::enable_if_t < std::is_arithmetic<T>{} > * = nullptr >
auto get_value_SFINAE(T) {
	std::cout << "get_Value_SFINAE(5)" << std::endl;
}
template <typename T, std::enable_if_t < !std::is_arithmetic<T>{} > * = nullptr >
auto get_value_SFINAE(T) {
	std::cout << "get_Value_SFINAE(five)" << std::endl;

}
// Tag dispatch
template <typename T>
auto get_value_TAG_DISPATCH(T, std::true_type) {
	std::cout << "get_Value_TAG_DISPATCH(5)" << std::endl;
}
template <typename T>
auto get_value_TAG_DISPATCH(T, std::false_type) {
	std::cout << "get_Value_TAG_DISPATCH(five)" << std::endl;
}
template <typename T>
auto get_value_TAG_DISPATCH(T t) {
	return get_value_TAG_DISPATCH(t, std::is_arithmetic<T>{});
}
// constexpr if
template <typename T>
auto get_value_CONSTEXPR_IF(T) {
	if constexpr (std::is_arithmetic_v<T>) {
		std::cout << "get_Value_CONSTEXPR_IF(5)" << std::endl;
	}
	else {
		std::cout << "get_Value_CONSTEXPR_IF(five)" << std::endl;
	}
}
void test_getValue() {
	get_value_SFINAE(5);
	get_value_SFINAE("five");

	std::cout << std::endl;

	get_value_TAG_DISPATCH(5);
	get_value_TAG_DISPATCH("five");

	std::cout << std::endl;

	get_value_CONSTEXPR_IF(5);
	get_value_CONSTEXPR_IF("five");
}
/**
 * 多态与模板
 */
template<class T>
class Base1 {
	//...
};
//CRTP：代表C ++习惯用法Curiously Recurring Template Pattern，是C ++中的一种技术，其中Derived类从类模板Base派生。关键为基类以派生类作为模板参数
class Derived1 : public Base1<Derived1> {
	//...
};
//CRTP典型用法：静态多态性，智能指针
class ShareMe : public std::enable_shared_from_this<ShareMe> {
	std::shared_ptr<ShareMe> getShared() {
		return shared_from_this();
	}
};
//Mixin，提供大量基本类模板，为其他派生类提供一些通用功能
template<class Derived>
class Relational {};
template <class Derived>
bool operator > (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return d2 < d1;
}
template <class Derived>
bool operator == (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return !(d1 < d2) && !(d2 < d1);
}
template <class Derived>
bool operator != (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return (d1 < d2) || (d2 < d1);
}
template <class Derived>
bool operator <= (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return (d1 < d2) || (d1 == d2);
}
template <class Derived>
bool operator >= (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return (d1 > d2) || (d1 == d2);
}
//使用示例
class Apple :public Relational<Apple> {
public:
	explicit Apple(int s) : size{ s } {};
	friend bool operator < (Apple const& a1, Apple const& a2) {
		return a1.size < a2.size;
	}
private:
	int size;
};
void test_mixin() {
	Apple apple1{ 5 };
	Apple apple2{ 10 };
	std::cout << "apple1 < apple2: " << (apple1 < apple2) << std::endl;
	std::cout << "apple1 > apple2: " << (apple1 > apple2) << std::endl;
	std::cout << "apple1 == apple2: " << (apple1 == apple2) << std::endl;
	std::cout << "apple1 != apple2: " << (apple1 != apple2) << std::endl;
	std::cout << "apple1 <= apple2: " << (apple1 <= apple2) << std::endl;
	std::cout << "apple1 >= apple2: " << (apple1 >= apple2) << std::endl;
}
/**
 * 这个课程基本全程都在让读者去看cppreference和wiki
 * https://zh.cppreference.com/
 */

int main()
{
	//test_template_5();
	//test_printf();
	test_mixin();
}
