// cpp_standard_lib_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

/**
 * 标准库继续
 * 容器
 */
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <array>
using namespace std;
/*
以vector为例的创建及删除方法
Type	                        Example
Default	                        std::vector<int> vec1
Range	                        std::vector<int> vec2(vec1.begin(), vec1.end())
Copy	                        std::vector<int> vec3(vec2)
Copy	                        std::vector<int> vec3= vec2
Move	                        std::vector<int> vec4(std::move(vec3))
Move	                        std::vector<int> vec4= std::move(vec3)
Sequence (Initializer list)	    std::vector<int> vec5 {1, 2, 3, 4, 5}
Sequence (Initializer list)	    std::vector<int> vec5= {1, 2, 3, 4, 5}
Destructor	                    vec5.~vector()
Delete elements	                vec5.clear()

因为std::array是在编译时生成的，所以有些特殊之处。
array没有移动构造函数，因此无法使用范围或初始化列表创建。
但是，可以使用聚合初始化来初始化std::array。同样，std::array也没有删除其元素的方法。
*/
void test_create_and_del() {
	vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	map<string, int> m = { {"bart", 12345}, {"jenne", 34929}, {"huber", 840284} };
	unordered_map<string, int> um{ m.begin(), m.end() };

	for (auto v : vec) cout << v << " "; // 1 2 3 4 5 6 7 8 9
	cout << "\n";
	for (auto p : m) cout << p.first << "," << p.second << " "; //bart,12345 huber,840284 jenne,34929
	cout << "\n";
	for (auto p : um) cout << p.first << "," << p.second << " "; //bart,12345 jenne,34929 huber,840284
	cout << "\n";

	vector<int> vec2 = vec;
	cout << vec.size() << endl; // 9
	cout << vec2.size() << endl; // 9

	vector<int> vec3 = move(vec);
	cout << vec.size() << endl; // 0
	cout << vec3.size() << endl; // 9

	vec3.clear();
	cout << vec3.size() << endl; // 0
}
//确定容器大小
void test_size() {
	vector<int> intVec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	map<string, int> str2Int = { {"bart", 12345},
							  {"jenne", 34929}, {"huber", 840284} };
	set<double> douSet{ 3.14, 2.5 };

	//判空用empty通常比判断size是否为0要快；并且有些容器没有size方法
	cout << intVec.empty() << endl;  // false
	cout << str2Int.empty() << endl; // false
	cout << douSet.empty() << endl;  // false

	cout << intVec.size() << endl;  // 9
	cout << str2Int.size() << endl; // 3
	cout << douSet.size() << endl;  // 2

	cout << intVec.max_size() << endl;  // 4611686018427387903
	cout << str2Int.max_size() << endl; // 256204778801521550
	cout << douSet.max_size() << endl;  // 461168601842738790
}
//访问元素，迭代器
struct MyInt {
	MyInt(int i) : myInt(i) {};
	int myInt;
};
void test_it() {
	std::vector<MyInt> myIntVec;
	myIntVec.push_back(MyInt(5));
	myIntVec.emplace_back(1);
	std::cout << myIntVec.size() << std::endl;         // 2

	std::vector<int> intVec;
	intVec.assign({ 1, 2, 3 });
	for (auto v : intVec) std::cout << v << " ";        // 1 2 3
	cout << std::endl;

	intVec.insert(intVec.begin(), 0);
	for (auto v : intVec) std::cout << v << " ";        // 0 1 2 3
	cout << std::endl;

	intVec.insert(intVec.begin() + 4, 4);
	for (auto v : intVec) std::cout << v << " ";        // 0 1 2 3 4
	cout << std::endl;

	intVec.insert(intVec.end(), { 5, 6, 7, 8, 9, 10, 11 });

	for (auto v : intVec) std::cout << v << " ";        // 0 1 2 3 4 5 6 7 8 9 10 11
	cout << std::endl;

	for (auto revIt = intVec.rbegin(); revIt != intVec.rend(); ++revIt)
		std::cout << *revIt << " ";                   // 11 10 9 8 7 6 5 4 3 2 1 0 
	cout << std::endl;

	intVec.pop_back();
	for (auto v : intVec) std::cout << v << " ";       // 0 1 2 3 4 5 6 7 8 9 10
	cout << std::endl;
}
//比较，常用比较运算符都可以使用
void test_compare() {
	vector<int> vec1{ 1, 2, 3, 4 };
	vector<int> vec2{ 1, 2, 3, 4 };
	cout << (vec1 == vec2) << endl;       // 1

	array<int, 4> arr1{ 1, 2, 3, 4 };
	array<int, 4> arr2{ 1, 2, 3, 4 };
	cout << (arr1 == arr2) << endl;       // 1

	set<int> set1{ 1, 2, 3, 4 };
	set<int> set2{ 4, 3, 2, 1 };
	cout << (set1 == set2) << endl;       // 1

	set<int> set3{ 1, 2, 3, 4, 5 };
	cout << (set1 < set3) << endl;        // 1

	set<int> set4{ 1, 2, 3, -3 };
	cout << (set1 > set4) << endl;        // 1

	unordered_map<int, string> uSet1{ {1, "one"}, {2, "two"} };
	unordered_map<int, string> uSet2{ {1, "one"}, {2, "Two"} };
	cout << (uSet1 == uSet2) << endl;     // 0
}

/**
 * 顺序容器
 */


int main()
{
	std::cout << "Hello World!\n";
}
