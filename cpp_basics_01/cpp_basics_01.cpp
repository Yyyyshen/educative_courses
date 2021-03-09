// cpp_basics_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

/**
 * c++基础
 */
void* foo = nullptr;
/*
Primitive or fundamental data types #
Primitive data types are predefined data types. These are:
Integer
Floating-point
Double
Void
Character
Boolean
类型占字节数受编译器及系统位数影响，可以用具体指明位数的变量类型来确保不会出错（uint32_t等

Derived data types #
Data types that are derived from primitive data types are known as derived data types. These are:
Function
Arrays
Pointers
Reference

User-defined data types #
Data types that are defined by the user are known as user-defined data types. These are:
Structure
Union
Enum
Class
Typedef

*/
using namespace std;
void test_0() {
	signed number = 90;//未使用数据类型修饰符定义任何数据类型，则该数据类型将为int
	cout << number << endl;

	long double number1 = 77.889;
	char character = number1;//显示类型转换
	cout << "character = " << character << endl;
}
/*
运算符
*/
void test_1() {
	string str1 = "Microsoft";
	string str2 = "Samsung";
	//字符串将进行逐字符比较（不用括号会编译错误
	cout << " Is operand1 greater than operand2? " << (str1 > str2) << endl;

	float f1 = 2, f2 = 1;
	//int mod = f1 % f2;//error:浮点数不能模运算

	//位运算符
	int operand1 = 3;
	int operand2 = 2;
	cout << "operand1 = " << operand1 << " , operand2 = " << operand2 << endl;
	cout << "operand1 & operand2 = " << (operand1 & operand2) << endl;
	cout << "operand1 | operand2 = " << (operand1 | operand2) << endl;
	cout << "operand1 ^ operand2 = " << (operand1 ^ operand2) << endl;

	int operand3 = 2;
	int operand4 = 1;
	cout << "operand1 >> operand2 = " << (operand3 >> operand4) << endl;// 2/2 = 1
	cout << "operand1 << operand2 = " << (operand3 << operand4) << endl;// 2*2 = 4
}
/**
 条件语句
 */
void test_2() {
	//switch 只接受int和char
	//当符合条件块执行后，如果不用break，会运行后面每个情况的语句
	char alph = 'a';
	switch (alph)
	{
		//...范围语法在gcc中支持，vs不支持
		//case 'a' ... 'z':
		//	cout << "lower" << endl;
		//	break;
		//case 'A' ... 'Z':
		//	cout << "upper" << endl;
		//	break;
	default:
		cout << "not an alph" << endl;
		break;
	}
}
/**
 * 循环
 */
void test_3() {
	do
	{
		//常用语句块，条件false只执行一次，但可以方便的进行错误控制
		//宏定义中也常见，可以确保宏中语句逻辑的正确性
	} while (false);
}
void is_prime(int number) {
	//判断是否为质数
	bool isPrime = true;
	// if block
	/*Checks if the value of a `number` is less than or equal to
	1. If yes, then execute line No. 13 to 16. If no, then execute
	line No. 18*/
	if (number <= 1) {
		//Sets the value of `isPrime` to false
		isPrime = false;
	}
	// for block
	for (int counter = 2; counter <= number / 2; counter++) {
		// if block
		if (number % counter == 0) {
			isPrime = false;
			// jump to line No. 27
			break;
		}
	}
	// if-else block
	/*If isPrime = true then execute line No. 30.
	If no, then execute line No. 32*/
	if (isPrime) {
		cout << "Number is prime";
	}
	else {
		cout << "Number is not prime";
	}
}
void d2b(int decimal) {
	//十进制转2进制
	int binary = 0;
	int remainder, product = 1;
	// Prints value of decimal
	cout << "Decimal Number = " << decimal << endl;
	// while block
	/*Checks if the value of `decimal` is not equal to `0`.
	If yes, then execute line No. 17 to 21.
	If no, then execute line No. 23.
	*/
	while (decimal != 0) {
		remainder = decimal % 2;
		binary = binary + (remainder * product);
		decimal = decimal / 2;
		product *= 10;
	}
	// while exit
	cout << "Binary Number = " << binary;
}
void is_Palindrome(int number)
{
	//判断一个数字是否为回文
	int remainder = 0, reverse = 0;
	// To reverse a number store it in temp
	int temp = number;
	// while loop，反转数字，跟原数字对比
	while (temp != 0) {
		// Get the last digit of temp
		remainder = temp % 10;
		// Store the remainder after the initially stored value in reverse
		reverse = reverse * 10 + remainder;
		// Remove the last digit of temp
		temp = temp / 10;
	}
	// if condition
	if (number == reverse) {
		cout << "is palindrome";
	}
	else {
		cout << "not a palindrome";
	}
}
/**
 * 函数
 */
int number_sum(int, int);//函数声明可以不写变量名
int number_sum(int num1 = 30, int num2 = 20) {  //有默认值的参数之后的参数也必须有默认值
	return num1 + num2;
}
//函数对象及lambda表达式
int addFunc(int a, int b) { return a + b; }
struct AddObj {
	//重载()运算符
	int operator()(int a, int b) const { return a + b; }
};
#include <vector>
#include <numeric>
void test_func_obj() {
	AddObj addObj;
	addObj(3, 4) == addFunc(3, 4);

	//直接用lambda表达式
	//auto addObj = [](int a, int b) {return a + b; };
	/*
	[]: Captures the used variables.
	(): Necessary for parameters.
	->: Necessary for complex lambda functions.
	{}: Function body, per default const.

	[]() mutable -> {...} has a non-constant function body.
	*/
	/* []捕获说明
	Binding					Description
	[]						no binding
	[a]						a per copy
	[&a]					a per reference
	[=]						all used variables per copy
	[&]						all used variables per reference
	[=,&a]					per default per copy; a per reference
	[&,a]					per default per reference; a per copy
	[this]					data and member of the enclosing class per copy
	[l=std::move(lock)]		moves lock (C++14)
	*/

	auto add11 = [](int i, int i2) { return i + i2; };
	auto add14 = [](auto i, auto i2) { return i + i2; };//c++14
	std::vector<int> myVec{ 1, 2, 3, 4, 5 };
	auto res11 = std::accumulate(myVec.begin(), myVec.end(), 0, add11);
	auto res14 = std::accumulate(myVec.begin(), myVec.end(), 0, add14);

	std::cout << res11 << std::endl;
	std::cout << res14 << std::endl;

	std::vector<std::string> myVecStr{ "Hello"s, " World"s };
	auto st = std::accumulate(myVecStr.begin(), myVecStr.end(), ""s, add14);
	std::cout << st << std::endl; // Hello World
}
//lambda，捕获示例
#include <functional>
std::function<int(int)>/*参数int，返回int*/ makeLambda(int a) {
	return [a](int b) { return a + b; };
}
void test_makeLambda() {
	auto add5 = makeLambda(5);
	auto add10 = makeLambda(10);
	cout << (add5(10) == add10(5));
}
/**
 * 递归
 * 分治法常用
 *
 * 与迭代的区别
在计算机语言中，迭代可以重复一组特定的指令，直到满足指定条件为止。
而递归函数使您可以继续在函数体内调用自身，直到满足某些条件为止。
迭代和递归的唯一目的是实现重复。循环通过重复结构实现重复，而递归通过重复函数调用实现重复。
当循环条件失败时，迭代终止。另一方面，当我们的基本条件评估为true时，递归终止。
迭代发生在同一函数内；因此，它占用更少的内存。
而在递归函数中，存在函数调用的开销，这会使我们的程序变慢，并且由于每个函数调用都会调用该函数的另一个副本，因此会消耗更多的内存。
在迭代中，我们的代码很大。递归可以帮助我们编写较短的代码。
迭代代码比递归代码快。
无限循环将停止程序的进一步执行，但不会导致任何系统崩溃。而无限递归调用将由于内存溢出而导致CPU崩溃。
 */
int power(int base, int exponent) {
	//求幂
	// Base case
	if (exponent == 0) {
		return 1;
	}
	// Recursive case
	else
		return base * power(base, exponent - 1);
}
int count_digits(int number) {
	//计算数字位数
	// Base Case
	if (abs(number) / 10 == 0) {
		return 1;
	}
	// Recursive Case  
	else {
		return 1 + count_digits(number / 10);
	}
}
int Fibonacci(int n) {
	//斐波那契数计算
	// Base Case
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	// Recursive Case
	else {
		return Fibonacci(n - 1) + Fibonacci(n - 2);
	}
}
/**
 * 数组
 */

int main()
{
	//test_0();
	test_makeLambda();
}
