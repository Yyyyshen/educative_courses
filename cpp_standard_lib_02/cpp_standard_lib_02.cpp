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
#include <numeric>
void test_array() {
	//数组，固定大小，可随机访问，没有动态内存分配
	std::array<int, 10> arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (auto a : arr) std::cout << a << " ";    // 1 2 3 4 5 6 7 8 9 10
	cout << "\n";

	double sum = accumulate(arr.begin(), arr.end(), 0);
	std::cout << sum << std::endl;               // 55

	double mean = sum / arr.size();
	std::cout << mean << std::endl;              // 5.5
	std::cout << (arr[0] == std::get<0>(arr));   // 1 (1 represents true)
}
//vector，可动态调整大小，元素在内存中连续保存，支持指针运算
void test_vector() {
	std::vector<int> intVec1(5, 2011);
	intVec1.reserve(10);
	std::cout << intVec1.size() << std::endl;     // 5
	std::cout << intVec1.capacity() << std::endl; // 10

	intVec1.shrink_to_fit();
	std::cout << intVec1.capacity() << std::endl; // 5

	std::vector<int> intVec2(10);
	std::cout << intVec2.size() << std::endl;     // 10

	std::vector<int> intVec3{ 10 };
	std::cout << intVec3.size() << std::endl;     // 1
}
//deque，双向队列
#include <deque>
class MyInt_2 {
private:
	int myInt;
public:
	MyInt_2(int i) : myInt(i) {};
	friend ostream& operator << (ostream& os, const MyInt_2& m)
	{
		os << m.myInt << " ";
		return os;
	}
};
void test_deque() {
	std::deque<MyInt_2> myIntDeq;

	myIntDeq.push_back(MyInt_2(5));
	myIntDeq.emplace_back(1);
	std::cout << myIntDeq.size() << std::endl;      // 2

	std::deque<MyInt_2> intDeq;

	intDeq.assign({ 1, 2, 3 });
	for (auto v : intDeq) cout << v << " ";   // 1 2 3
	cout << endl;

	intDeq.insert(intDeq.begin(), 0);
	for (auto v : intDeq) cout << v << " ";   // 0 1 2 3
	cout << endl;

	intDeq.insert(intDeq.begin() + 4, 4);
	for (auto v : intDeq) cout << v << " ";   // 0 1 2 3 4
	cout << endl;

	intDeq.insert(intDeq.end(), { 5, 6, 7, 8, 9, 10, 11 });
	for (auto v : intDeq) cout << v << " ";   // 0 1 2 3 4 5 6 7 8 9 10 11
	cout << endl;

	for (auto revIt = intDeq.rbegin(); revIt != intDeq.rend(); ++revIt)
		std::cout << *revIt << " ";                     // 11 10 9 8 7 6 5 4 3 2 1 0
	cout << endl;

	intDeq.pop_back();
	for (auto v : intDeq) cout << v << " ";   // 0 1 2 3 4 5 6 7 8 9 10
	cout << endl;

	intDeq.push_front(-1);
	for (auto v : intDeq) cout << v << " ";   // -1 0 1 2 3 4 5 6 7 8 9 10
	cout << endl;
}
//std::list 双向链表
void test_list() {
	std::list<int> list1{ 15, 2, 18, 19, 4, 15, 1, 3, 18, 5,
					4, 7, 17, 9, 16, 8, 6, 6, 17, 1, 2 };

	list1.sort();
	for (auto l : list1) std::cout << l << " ";
	// 1 1 2 2 3 4 4 5 6 6 7 8 9 15 15 16 17 17 18 18 19 
	std::cout << std::endl;

	list1.unique();
	for (auto l : list1) std::cout << l << " ";
	// 1 2 3 4 5 6 7 8 9 15 16 17 18 19
	std::cout << std::endl;

	std::list<int> list2{ 10, 11, 12, 13, 14 };


	list1.splice(std::find(list1.begin(), list1.end(), 15), list2);
	for (auto l : list1) std::cout << l << " ";
}
//forward_list 单链表
#include <forward_list>
void test_forward_list() {
	std::forward_list<int> forw;
	std::cout << forw.empty() << std::endl; // 1 (1 denoted true)

	forw.push_front(7);
	forw.push_front(6);
	forw.push_front(5);
	forw.push_front(4);
	forw.push_front(3);
	forw.push_front(2);
	forw.push_front(1);
	for (auto i : forw) cout << i << " "; // 1 2 3 4 5 6 7
	cout << "\n";

	forw.erase_after(forw.before_begin());
	cout << forw.front(); // 2
	cout << "\n";

	std::forward_list<int> forw2;
	forw2.insert_after(forw2.before_begin(), 1);
	forw2.insert_after(++forw2.before_begin(), 2);
	forw2.insert_after(++(++(forw2.before_begin())), 3);
	forw2.push_front(1000);
	for (auto i = forw2.cbegin(); i != forw2.cend(); ++i) cout << *i << " ";  // 1000 1 2 3
	cout << "\n";

	auto IteratorTo5 = std::find(forw.begin(), forw.end(), 5);
	forw.splice_after(IteratorTo5, std::move(forw2));
	for (auto i = forw.cbegin(); i != forw.cend(); ++i) cout << *i << " ";  // 2 3 4 5 1000 1 2 3 6 7
	cout << "\n";

	forw.sort();
	for (auto i = forw.cbegin(); i != forw.cend(); ++i) cout << *i << " ";
	// 1 2 2 3 3 4 5 6 7 1000
	cout << "\n";

	forw.reverse();
	for (auto i = forw.cbegin(); i != forw.cend(); ++i) cout << *i << " ";
	// 1000 7 6 5 4 3 3 2 2 1
	cout << "\n";

	forw.unique();
	for (auto i = forw.cbegin(); i != forw.cend(); ++i) cout << *i << " ";
	// 1000 7 6 5 4 3 2 1
	cout << "\n";
}
/**
 * 关联容器
 */
void test_asso_container() {
	std::multiset<int> mySet{ 3, 1, 5, 3, 4, 5, 1, 4, 4, 3, 2, 2, 7, 6, 4, 3, 6 };

	for (auto s : mySet) std::cout << s << " "; // 1 1 2 2 3 3 3 3 4 4 4 4 5 5 6 6 7
	std::cout << "\n";

	mySet.insert(8);
	std::array<int, 5> myArr{ 10, 11, 12, 13, 14 };
	mySet.insert(myArr.begin(), myArr.begin() + 3);
	mySet.insert({ 22, 21, 20 });
	for (auto s : mySet) std::cout << s << " ";
	// 1 1 2 2 3 3 3 3 4 4 4 4 5 5 6 6 7 10 11 12 20 21 22
	std::cout << "\n";

	std::cout << mySet.erase(4);  // 4
	mySet.erase(mySet.lower_bound(5), mySet.upper_bound(15));
	for (auto s : mySet) std::cout << s << " ";
	// 1 1 2 2 3 3 3 3 20 21 22
	std::cout << "\n";
}
//有序关联容器
#include <regex>
#include <sstream>
#include <fstream>
using str2Int = std::unordered_map<std::string, size_t>;
using intAndWords = std::pair<std::size_t, std::vector<std::string>>;
using int2Words = std::map<std::size_t, std::vector<std::string>>;
// count the frequency of each word
str2Int wordCount(const std::string& text) {
	std::regex wordReg(R"(\w+)");
	std::sregex_iterator wordItBegin(text.begin(), text.end(), wordReg);
	const std::sregex_iterator wordItEnd;
	str2Int allWords;
	for (; wordItBegin != wordItEnd; ++wordItBegin) {
		++allWords[wordItBegin->str()];
	}
	return allWords;
}
// get to all frequencies the appropriate words
int2Words frequencyOfWords(str2Int& wordCount) {
	int2Words freq2Words;
	for (auto wordIt : wordCount) {
		auto freqWord = wordIt.second;
		if (freq2Words.find(freqWord) == freq2Words.end()) {
			freq2Words.insert(intAndWords(freqWord, { wordIt.first }));
		}
		else {
			freq2Words[freqWord].push_back(wordIt.first);
		}
	}
	return freq2Words;
}
void test_map() {
	// get the filename
	std::string myFile = "Test.rtf";

	// open the file
	std::ifstream file(myFile, std::ios::in);
	if (!file) {
		std::cerr << "Can't open file " + myFile + "!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// read the file
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string text(buffer.str());

	// get the frequency of each word
	auto allWords = wordCount(text);

	std::cout << "The first 20 (key, value)-pairs: " << std::endl;
	auto end = allWords.begin();
	std::advance(end, 20);
	for (auto pair = allWords.begin(); pair != end; ++pair) {
		std::cout << "(" << pair->first << ": " << pair->second << ")";
	}
	std::cout << "\n\n";

	std::cout << "allWords[Web]: " << allWords["Web"] << std::endl;
	std::cout << "allWords[The]: " << allWords["The"] << "\n\n";

	std::cout << "Number of unique words: ";
	std::cout << allWords.size() << "\n\n";

	size_t sumWords = 0;
	for (auto wordIt : allWords) sumWords += wordIt.second;
	std::cout << "Total number of words: " << sumWords << "\n\n";

	auto allFreq = frequencyOfWords(allWords);

	std::cout << "Number of different frequencies: " << allFreq.size() << "\n\n";

	std::cout << "All frequencies: ";
	for (auto freqIt : allFreq) std::cout << freqIt.first << " ";
	std::cout << "\n\n";

	std::cout << "The most frequently occurring word(s): " << std::endl;
	auto atTheEnd = allFreq.rbegin();
	std::cout << atTheEnd->first << " :";
	for (auto word : atTheEnd->second) std::cout << word << " ";
	std::cout << "\n\n";

	std::cout << "All word which appears more then 1000 times:" << std::endl;
	auto biggerIt = std::find_if(allFreq.begin(), allFreq.end(), [](intAndWords iAndW) {return iAndW.first > 1000; });
	if (biggerIt == allFreq.end()) {
		std::cerr << "No word appears more then 1000 times !" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		for (auto allFreqIt = biggerIt; allFreqIt != allFreq.end(); ++allFreqIt) {
			std::cout << allFreqIt->first << " :";
			for (auto word : allFreqIt->second) std::cout << word << " ";
			std::cout << std::endl;
		}
	}
}
//无序关联容器
#include <unordered_set>
void getInfo(const unordered_set<int>& hash) {
	cout << "hash.bucket_count(): " << hash.bucket_count();
	cout << "hash.load_factor(): " << hash.load_factor();
}
void test_unordered_container() {
	// Create an unoredered set and initialize it with the array
  // Set will contain only random elements
	int arr[100];
	for (int i = 0; i < 100; i++)
		arr[i] = (rand() % 100) + 1;
	unordered_set<int> hash(arr, arr + sizeof(arr) / sizeof(int));
	cout << "hash.max_load_factor():\t" << hash.max_load_factor() << endl; // hash.max_load_factor():	1

	getInfo(hash);
	//hash.bucket_count(): 103hash.load_factor(): 0.660194
	cout << endl;

	hash.insert(500);
	cout << "hash.bucket(500):\t" << hash.bucket(500) << endl; // 88

	getInfo(hash);
	cout << endl;
	//hash.bucket_count(): 103hash.load_factor(): 0.669903

	hash.rehash(500);

	getInfo(hash);
	//hash.bucket_count(): 503hash.load_factor(): 0.137177500

	cout << endl << "hash.bucket(500):\t" << hash.bucket(500); //hash.bucket(500):	500
}
/**
 * 基于deque的高级容器
 */
#include <stack>
void test_stack() {
	std::stack<int> myStack;

	std::cout << myStack.empty() << std::endl;   // true
	std::cout << myStack.size() << std::endl;    // 0

	myStack.push(1);
	myStack.push(2);
	myStack.push(3);
	std::cout << myStack.top() << std::endl;     // 3

	while (!myStack.empty()) {
		std::cout << myStack.top() << " ";
		myStack.pop();
	}                                            // 3 2 1

	std::cout << std::endl << myStack.empty() << std::endl;   // 1 (denotes true)
	std::cout << myStack.size() << std::endl;    // 0
}
//停一下

int main()
{
	std::cout << "Hello World!\n";
}
