# 1

## 1.2 初始输入输出
`iostream` 库提供输入输出
```cpp
std::cout<<'Hello World!'<<std::endl;
```
`::`作用运算符

`using`声明
`using namespace::name;`

## 1.3
```cpp
/*
*
*comment
*/

//comment
```

## 1.4 控制流

### 1.4.1 `while`

`++` before `i` means incrementation must be carried out before assignment;
`++` after `i` means incrementation must be carried out after assignment:

### 1.4.2 `for`

### 1.4.3 读取数量不定的输入数据

```cpp
#include<iostream>
int main() {
	int sum = 0, value = 0;
	while (std::cin >> value) 
		sum += value;
	std::cout << "sum is :" << sum << std::endl;
	return 0;
}
```

文件结束
Windows `Ctrl+Z` `Enter`
UNIX `Ctrl+D`

### 1.4.4 `if`语句


## 1.5 类简介
来自标准库的头文件用尖括号 `<>`
不属于标准库的头文件使用双引号 `""`

### 1.5.2 成员函数
点运算符`.`
调用运算符`()`

# 2 变量和基本类型

## 2.1基本内置类型

算术类型 字符 整型数 布尔值 浮点数

空类型

### 2.1.1 算术类型

整型 浮点型

|类型|含义|最小尺寸|
|---|---|---|
|bool|布尔类型|未定义|
|char|字符|8位|
|wchar_t|宽字符|16位|
|char16_t|Unicode字符|16位|
|char32_t|Unicode字符|32位|
|short|整短型|16位|
|int|整型|16位|
|long|长整型|32位|
|long long|长整型|64位|
|float|单精度浮点数|6位有效数字|
|double|双精度浮点数|10位有效数字|
|long double|扩展精度浮点数|10位有效数字|

整型可划分为带符号(`signed`)和无符号的(`unsigned`)

### 2.1.2 类型转换

从无符号数中减去一个值时，不管这个值是不是无符号数，都必须确保结果不能是一个负值

`unsigned`类型负数会自动被转换为无符号数

### 2.1.3 字面值常量
字符串字面值的类型实际上是由常量字符构成的数组

## 2.2 变量

### 2.2.1 变量定义
类型说明符 后跟变量名
初始值 初始化对象
- 初始化不是赋值，初始化的含义是创建变量时赋予其一个初始值
- 赋值的含义是把对象的当前值擦除，而以一个新值来替代
  
列表初始化

```cpp
int list1 = 0;
int list1 = {0};
int list1{0};
int list1(0);
```

默认初始化
- 定义于任何函数体之外的变量被初始化为0
- -定义在函数体内部的内置类型变量将不被初始化，一个未被初始化的内置类型变量的值是未定义的，如果试图拷贝或以其他形式访问此类值将引发错误

### 2.2.2 变量声明和定义的关系
C++语言支持分离式编译
声明一个变量，变量名前添加关键字`extern`

变量能且只能被定义一次，但是可以被多次声明

### 2.2.3 识别符
C++标识符由字母数字和下划线组成，其中必须以字母或下划线开头，对大小写字母敏感

### 2.2.4 名字的作用域
大多数作用域都以花括号分隔
- 全局作用域
- 块作用域
  
作用域嵌套
- 内层作用域
- 外层作用域

## 2.3 复合类型

### 2.3.1 引用
通过声明符写成`&d`的形式来定义引用类型
引用即别名

### 2.3.2 指针
指针与引用的不同
- 指针本身是一个对象，允许对指针赋值和拷贝，而且指针的生命周期内它可以先后指向几个不同的对象
- 指针无需在定义的时赋初值

定义指针写成`*d`的形式

指针值属于一下四种状态
- 指向一个对象
- 指向紧邻对象所占空间的下一个位置
- 空指针，意味着指针没有指向任何对象
- 无效指针，也就是上述情况之外的其他值

空指针
空指针不指向任何对象
```cpp
int *p1 = nullptr;
int *p2 = 0;

#include<cstdlib>
int *p3 = NULL
```

指针值为0，条件取False
指针值为任何非0值，条件值取True

void* 指针

### 2.3.3 理解复合类型的声明

## 2.4 `const`限定符
其值不能被改变

`const`对象必须初始化

默认情况下，`const`对象被设定为仅在文件内有效，当多个文件中出现了同名const对象时，等同于在不同文件中分别定义了独立的变量

`extern const`只在一个文件中定义，其他文件中声明并使用

### 2.4.1 `const`的引用
对常量的引用

```cpp
double dval = 3.14
const int &ri = dval
```
等效于
```cpp
double dval = 3.14
const int temp = dval
const int &ri = temp
```

### 2.4.2 指针和`const`
指向常量的指针不能用于改变其所指对象的值，要想存放常量对象的地址，只能使用指向常量的指针

`const`指针
常量指针必须初始化

### 2.4.3 顶层`const`

顶层`const`表示指针本身是个常量
底层`const`表示指针所指的对象是一个常量


### 2.4.4 `constexpr`和常量表达式

常量表达式指不会改变并且编译过程就能得到计算机过的表达式

`constexpr`变量
C++ 11中允许用此来验证变量的值是否为一个常量表达式

字面值类型
一个`constexpr`指针的初始值必须是`nullptr`或者`0`，或者是存储于某个固定地址的对象

指针和`constexpr`
```cpp
const int *p = nullptr;
constexpr int *q = nullptr;
```

## 2.5 处理类型

### 2.5.1 类型别名
`using a = b`

指针、常量和类型别名
```cpp
typedef char *pstring;
const pstring cstr =0;
const pstring *ps;
```

### 2.5.2 `auto`类型说明符
`auto item = a + b`

### 2.5.3 `decltype`类型指示符
`decltype(f()) sum = x;`

decltype((variable))的结果永远是引用
decltype(variable)的结果只有当variable本身就是一个引用是才是引用

## 2.6 自定义数据结构

### 2.6.1 定义 Sales_data 类型

类关键词
`struct` 紧跟类名和类体
类体由花括号包围形成一个新的作用域

类内由数据成员
c++11开始可以为数据成员提供一个类内初始值

```cpp
sturct name {/*    */};
```

### 2.6.2 使用 Sales_data 类型

### 2.6.3 编写自己的头文件
头文件保护符
`#define`将一个名字设定为预处理变量
`#ifdef`当且仅当变量已定义时为真
`#ifndef`当且仅当变量未定义时为真
`#endif`一旦检查结果为真，则执行后续操作直至遇到其为止
```cpp
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include<string>
struct Sales_data{
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif
```

# 3 字符串、向量和数组

## 3.1 命名空间的 `using` 声明
形式
```cpp
using namespace::name;
```

# 3.2 标准库类型 `string`
`using std::string`

# 3.2.1 定义和初始化 `string` 对象
默认初始化为一个空字符串

直接初始化与拷贝初始化
- 拷贝初始化 通过等号初始化一个变量
- 直接初始化 不适用等号初始化一个变量

# 3.2.2 `string` 对象上的操作

- 读写 `string` 对象
	- 使用IO操作符读写`string`对象
	```cpp
	string s;
	cin >> s;
	cout << s << endl;
	```
- 读取未知数量的 `string` 对象
	- eg
	```cpp
	int main(){
		string word;
		while (cin>>word)
			cout << word << endl;
		return 0;
	}
	```
- 使用 `getline` 读取一整行
	- eg
	```cpp
	int main(){
		string line;
		while (getline(cin,line))
			cout << line << endl;
		return 0;
	}
	```
- `string` 的 empty 和 size 操作
	- empty
		- 根据 `string` 对象是否为空返回一个对应的布尔值
		```cpp
		while (getline(cin,line))
			if (!line.empty())
				cout << line << endl;
	- size
		- 返回 `string` 对象的长度
- `string::size_type` 类型
	- size 函数返回一个无符号整型数，含有size()函数尽量不适用 int 
- 比较 `string` 对象
	- 大小写敏感
	- == 和 != 分别校验两个 `string` 对象相等或不相等
	- 相等意味着长度相同而且包含的字符也完全相同
	- <,<=,>,>=
		- 长度不同，且已有位数相同，较短字符串小
		- 有不同，比较第一个相异位字符
- 为 `string` 对象赋值
	- 使用加法不能将两个字面值相加，可以字符串变量与字面值相加
	错误 `string s1 = "Hello" + "World";`
	正确 `string s2 = s1 + "World"` 

	- 字符串字面值与 `string` 是不同的类型

### 3.2.3 处理 `string` 对象中的字符
- cctype 头文件中的函数
	- `isalnum()` 但字符为字母或数字时为真
	- `isalpha()` 函数来检查字符是否为字母字符；
	- `isdigits()` 函数来测试字符是否为数字字符；
	- `isspace()` 测试字符是否为空白，如换行符、空格和制表符；
	- `ispunct()` 函数来测试字符是否为标点符号
	- `islower()` 函数来判断参数是否是小写字母，若是返回true
	- `isupper()` 函数来判断参数是否是大写字母，若是返回true
	- `tolower()` 函数：如果参数是大写字母，则返回其小写，否则返回该参数
	- `toupper()` 函数：如果参数是小写字母，则返回其大写，否则返回该参数

- 使用 for 处理每个字符
	- eg
	```cpp
	for (declaration : expression)
		statement
	```

- 使用范围 for 语句改变字符串中的字符
	- eg
	```cpp 将字符串中字母转换为大写
	string s('abc');
	for (auto &c : s)
		c = toupper(c);
	cout << s << endl;
	`
- 只处理一部分字符
	- 下标运算符  
	- 使用下标执行迭代
		- eg 
		```cpp
		string s;
		for (decltype(s.size()) index = 0 ; index != s.size() && isspace(s[index]); ++index)
			s[index] = toupper(s[index]);
		```
- 使用下标执行随机访问
	- 使用字符串下标需检查其合理性

## 3.3 `vector`
表示对象的集合，其中所有对象的类型都相同
需要包含头文件
```cpp
#include<vector>
using std::vector;
```
vector为类模板，编译器根据模板创建类或函数的过程称为实体化

### 3.3.1 定义和初始化 `vector`对象
|初始化方法|说明|
|---|---|
|`vector<T> v1`|v1为空vector，其元素为T类型，执行默认初始化|
|`vector<T> v2(v1)`等同于`vector<T> v2=v1`|为v1副本|
|`vector<T> v3(n,val)`|n个值为val的元素|
|`vector<T> v4(a,c,c)`|初始化元素的个数，每个对应初始值|

- 列表初始化vector对象
	- eg `vector<string> articles = {"a","b","c"};`
- 创建指定数量的元素
	- eg `vector<string> v1(10,-1)`
- 值初始化
	- eg `vector<string> v1(10)` 10个元素每个初始化为0

### 3.3.2 向 `vector` 对象中添加元素
`push_back`将元素添加对vector对象尾端
eg
```cpp
vector<int> v2;
for (int i=0; i!=100,++i)
	v2.push_back(i)
```

### 3.3.3 其他 `vector` 操作
- v.empty() 返回类型 布尔值
- v.size() 返回类型 size_type
- v[n]

- 计算 `vector` 内对象的索引

## 3.4 迭代器的介绍
有效迭代器指向某个元素或者指向尾元素的下一位置

### 3.4.1 使用迭代器
```cpp
auto b = v.begin()
auto e = v.end()
```
- 迭代器运算符
	- 如果连个迭代器指向的元素相同或者都是同一个容器的尾后迭代器，则相等

	|运算符|说明|
	|---|---|
	|`*iter`|返回迭代器 `iter` 所指元素的额引用|
	|`iter->mem`|解引用 `iter` 并获取该元素名为 `mem` 的成员，等价于 `(*iter).mem` |
	|`++iter` |下一个元素|
	|`--iter` |上一个元素|
	|`iter1 == iter2` `iter1 != iter2`|判断是否相等|

- 将迭代器从一个元素移动到另一个元素
	- eg
	```cpp
	for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
		*it = toupper(*it);
	```

- 迭代器类型
	- `iterator`
	- `const_iterator`

- begin 和 end 运算符
	- `iterator`
	- `const_iterator`

- 结合解引用和成员访问操作
	- `(*it).empty()`
	- 箭头运算符(->)
		- eg
		```cpp
		for (auto it = text.cbegin(); it != text.cend() && !it->emtpy(); ++it)
			cout << *it << endl;
		```

- 某些对 `vector` 对象的操作会导致迭代器失效
	- 在范围 `for` 循环中向 `vector` 对象添加元素

### 3.4.2 迭代器的运算

|vector和string迭代器支持的运算|说明|
|---|---|
|`iter + n`|向前移动了n个元素|
|`iter - n`|向后移动了n个元素|
|`iter += n`|将iter1加n的结果赋给iter1|
|`iter -= n`|将iter1减n的结果赋给iter1|
|`iter1 - iter2`|两个迭代器之间的距离|
|>,>=,<,<=|大小判断|

- 迭代器的算术运算
	- 迭代器与整数值加减，向前或向后移动若干个位置
		- eg
		```cpp
		auto mid = vi.begin() + vi.size()/2
		```
	- 相减得到距离，类型为 `difference_type` 的带符号整数型

- 使用迭代器运算
迭代器二分搜索
```cpp
auto beg = text.begin(), end = text.end();
auto mid = text.begin() + (end-beg)/2;
while(mid != end && *mid != sought){
	if(sought < *mid)
		end = mid;
	else
		beg = mid + 1
	mid = beg + (end - beg)/2
}
```

## 3.5 数组
数组的大小确定不变，不能随便向数组中增加元素

### 3.5.1 定义和初始化内置数组
数组的维度必须是一个常量表达式

- 显式初始化数组元素 
	- 初始化允许忽略数组的维度
- 字符数组的特殊性
	- eg
	```cpp
	char a[] = "c++" //讲自动添加表示字符串结束的空字符\0
	```
- 不允许拷贝和赋值
	-不能将数组的内容拷贝给其他数组作为初始值，也不能用数组为其他数组赋值
- 理解复杂的数组声明
	- eg
	```cpp
	int *ptrs[10]; //ptrs为含有10个整型指针的数组
	int (*Parray)[10] = &arr; //Parray指向一个含有10个整数的数组
	int (&arrRef)[10] = arr; //arrRef引用一个含有10个是整数的数组

### 3.5.2 访问数组元素
数组下标定义为 size_t 类型
```cpp
for (auto i : scores)
	cout<< i <<" ";
cout << endl;
```
- 检查下标值，防止数组下标越界

### 3.5.3 指针和数组
在大多数表达式中，使用数组类型的对象其实是使用一个指向该数组首元素的指针

- 指针也是迭代器
	- 尾后指针 `int *e = &arr[10]` 不存在元素用来初始化e

- 标准库函数 begin 和 end
	- eg
	```cpp
	int ia[] = {0,1,2,3};
	int *beg = begin(ia);
	int *last = end(ia);
	```

- 指针运算
	- 一个指针加上减去整数值结果仍是指针
	- 两指针相减结果为他们的距离(类型`ptrdiff_t`)

- 下标和指针

### 3.5.4 C 风格字符串
按照此习惯书写的字符串存放在字符数组中并以空字符结束

- C 标砖库 String 函数
	- eg
	|||
	|---|---|
	|strlen(p)|返回p的长度，空字符串不计算在内|
	|strcmp(p1, p2)|比较p1和p2的相等性，如果 p1==p2 ，返回0，如果 p1 > p2，返回正值，如果p1 < p2 返回一个负值|
	|strcat(p1, p2)|将p2附加到p1之后，返回p1|
	|strcpy(p1, p2)|将p2拷贝给p1，返回p1|

- 比较字符串
	- string 关系运算符，相等运算符
	- char strcmp 函数

- 目标字符串的大小由调用者决定

### 3.5.5 与旧代码的接口
- 混用 string 对象和 C 风格字符串
	- 允许使用以空字符串结束的字符数组来初始化string对象或为string对象赋值
	- 在 string 对象的加法运算中允许使用以空字符串结束的字符串数组作为其中一个运算对象；在 string 对象的复合赋值运算中允许使用以空字符结束的字符数组作为右侧的运算对象

- 使用数组初始化 vector 对象
	- eg
	```cpp
	int int_arr[] = {0,1,2,3,4};
	vector<int> ivec(begin(int_arr),end(int_arr));
	```

## 3.6 多维数组
数组的元素是数组

对于二维数组，常把第一个维度称作行，第二个维度称作列
```cpp
int ia[2][3] = {{0,1,2},{3,4,5}}
int ia[2][3] = {0,1,2,3,4,5}
//两者等价
```

- 多维数组的下标引用
	- 遍历元素
	```cpp
	constexpr size_t rowCnt = 3, colCnt = 4;
	int ia[rowCnt][colCnt];
	for (size_t i = 0; j != rowCnt; ++i){
		for (size_t j = 0; j != colCnt; ++j)
			ia[i][j] = i * colCnt + j;
	}
	```
- 使用范围 for 语句处理多维数组
	- 简化eg
	```cpp
	size_t cnt = 0;
	for (auto &col : row){
		col = cnt;
		++cnt
	}
	- notice 外层循环使用引用
	```cpp
	for (const auto &row: ia)
		for (auto col : row)
			cout<<col<<endl;
	使用for语句处理多维数组，除了最内层的循环外，其他所有循环的控制变量都应该是引用类型
- 指针和多维数组
	- eg
	```cpp
	for (auto p = begin(ia); p != end(ia); ++p){
		for (auto q= begin(*p); q != end(*p); ++q)
			cout <<*q<< ' ';
		cout << endl;
	}
- 类型别名简化多维数组的指针
	- eg
	```cpp
	using int_array = int[4];
	typedef int int_array[4]; // 两种声明方式
	for (int_array *p = ia; p != ia + 3; ++p){
		for (int *q = *p; q != *p + 4; ++q)
			cout << *q << " ";
		cout<< endl;
	}


# 4 表达式 

## 4.1 基本概念
- 运算符分类
	- 一元运算符
	- 二元运算符

- 重载运算符
- 左值和右值
	左值时为对象的身份，右值时为对象的值

### 4.1.2 优先级和结合律

### 4.1.3 求值顺序
- 逻辑与 (&&)
	- 先求左侧运算对象的值，左侧为真时才继续求右侧运算符值
- 逻辑或 (||)
- 条件运算符 (?:)
- 逗号运算符

## 4.2 算数运算符

## 4.3 逻辑和关系运算符
&& 两对象都为真时结果为真
|| 两对象一个为真时结果为真

- 短路求值 两者均从左边开始验证

- 逻辑非运算符
将运算对象取值反后返回

- 关系运算符
关系运算符比较运算对象的大小并返回布尔值
连续比较两个以上需使用 &&

- 相等性测试与布尔字面值
```cpp
if (val) //如果val是任意的非0值，条件为真
if (!val) // 如果val是0，条件为真
```

## 4.4 赋值运算符 

## 4.5 递增和递减运算符
前置版本后置版本
```cpp
int i = 0 , j;
j = ++i; // j = 1 , i = 1 
j = i++; // j = 1 , i = 2
```
前置版本首先将运算对象加1，然后将改变后的对象作为结果
后置版本也会将运算对象加1，但是求值结果是运算对象改变之前那个值的副本
优先使用前置版本

- 在一条语句中混用解引用和递增运算符
```cpp
auto pbeg = v.begin();
while (pbeeg != v.end() && *beg >= 0)
	cout << *pbeg++ << endl; //输出当前值并将pbeg向前移动一个元素
	// *pbeg++ = *(pbeg++)
```


## 4.6 成员访问运算符
- 点运算符 获取类对象的一个成员
- 箭头运算符 与点运算符相关 

`ptr->mem` 等价于 `(*ptr).mem`

## 4.7 条件运算符
条件运算符 (?:) 允许我们吧简单的if-else 逻辑嵌入单个表达式中  
使用形式:
	cond? expr1 : expr2;
	//如果cond条件为真，调用expr1，否则调用expr2
- 嵌套条件运算符

- 条件运算符优先级较低，通常需要再两端添加括号

## 4.8 位运算符
|运算符|功能|用法|
|:---:|:---:|:---:|
|\`|位求反|`expr|
|<<|左移|expr1 << expr2|
|>>|右移|expr1 >> expr2|
|&|位与|expr & expr|
|^|位异或|expr ^ expr|
|\||位或|expr | expr|

- 移位运算符  
令左侧运算对象的内容按照右侧运算对象的要求移动指定位数，然后将左侧运算对象的拷贝作为求值结果  
右侧运算对象一定不能为负，值必须严格小于结果的位数  
	- 左移运算符  
	在右侧插入值为0的二进制位
	- 右移运算符
	在左侧插入符号位或值为0的二进制位
- 位求反运算符  
将运算对象逐位求反后生成一个新值  
- 位与、位或、位异或运算符  
	- 位与运算符(&)  
	如果两个运算对象的对应位置都是1，则运算结果中该位为1，否则为0
	- 位或运算符(|)  
	如果两个运算对象对应位置至少有一个为1，则运算结果中该位为1，否则为0  
	- 位或运算符(^)  
	如果两个运算对象的对应位置有且只有一个为1，则运算结果该位为1，否则为0
- 使用位运算符

- 移位运算符(又叫IO运算符)满足左结合律  
优先级比算术运算符低，比关系运算符、赋值运算符和条件运算符优先级高

## 4.9 sizeof 运算符
返回一条表达式或一个类型名字所占的字节数  
满足右结合律  
所得值为 size_t 类型的的常量表达式  

```cpp
sizeof (type)
sizeof expr
```

- 对 char 或者类型为 char 的表达式执行 sizeof 运算，结果得1
- 对引用类型执行 sizeof 运算得到被引用对象所占空间的大小
- 对指针执行 sizeof 运算得到指针本身所占空间的大小
- 对解引用指针执行 sizeof 运算得到指针指向对象所占空间的大小，指针不需有效
- 对数组执行 sizeof 运算得到整个数组所占空间的大小，等价于对数组中所有的元素各执行一次sizeof运算并将所得到的结果求和
	- attention sizeof运算不会把数组转换成指针来处理
- 对 string 对象或 vector 对象执行 sizeof 运算只会返回该类型固定部分的大小，不会计算对象中的元素占用了多少空间

```cpp
vector<int> ia;
constexpr size_t sz = sizeof(ia)/sizeof(*ia);
int arr2p[sz];
```

## 4.10 逗号运算符
含有两个运算对象，按照从左向右的顺序依次求值，规定了运算对象求值的顺序

```cpp
vector<int>::size_type cnt = ivec.size();
for(vector<int>::size_type ix =0; ix !=ivec.size(); ++ix, --cnt)
	ivec[ix] = cnt;
```

## 4.11 类型转换
如果两类型可以互相转换，那么他们就是关联的  
隐式转换发生条件
- 比int小的整数型首先提升为较大的整数类型
- 在条件中，非布尔值转换成布尔类型
- 初始化过程中，初始值转化成变量的类型，在赋值语句中，右侧对象转换成左侧运算对象的类型
- 如果算术运算或关系运算的运算对象有多种类型，需要转化成同一种类型

### 4.11.1 算术转换
- 整形提升
	将小整数类型转化成较大的整数类型，如果可能的值都能存在int里，就会被提升为int类型
- 无符号类型的运算对象
	- 均无符号，小类型转化成较大的类型
	- 无符号类型不小于带符号类型，带符号的运算对象转化成无符号的
	- 带符号类型大于无符号类型，结果依赖于机器

### 4.11.2 其他隐式类型转换
- 数组转换成指针，在大多数用到数组的表达式中，数组自动转换成指向数组首元素的指针
- 指针的转换
	- 常量整数值0或者字面值nullptr能转换成任意指针类型
	- 指向任意非常量的指针能转换成void*
	- 指向任意对象的指针能转换成const void*
- 转换成常量
	允许将指向非常量类型的指针转换成指向相应的常量类型的指针
- 类类型定义的转换

### 4.11.3 显式转换
- 命名的强制类型转换
	`cast-name<type>(expression)`
	cast-name 为 static_cast \ dynamic_cast \ const_cast \ reinterpret_cast 中一种
	- static_cast
	任何具有明确定义的类型转换，只要不包含底层 const
	eg `double slope = static_cast<double>(j) / i`
	- const_cast
	只能改变运算对象的底层 const
	- reinterpret_cast
	运算对象的位模式提供较低层上的重新解释
- 旧式的强制类型转换
	`type (expr);`
	`(expr) type;`


# 5 语句

## 5.1 简单语句
C++ 语言中的大多数语句都以分号结束，表达式末尾加上分号就变成了表达式语句

- 空语句
	`;`
- 复合语句(块)
	将要执行的语句用花括号括起来

## 5.2 语句作用域
在 if、switch、while和for 语句的控制结构内定义变量，定义在控制结构当中的变量只在相应语句内部可见

## 5.3 条件语句

### 5.3.1 if 语句
判断一个指定条件是否为真，根据判断结果决定是否执行另一条语句
- 悬垂 else
	C++规定 else 与离它最近的尚未匹配的 if 匹配，从而消除了程序的二义性
- 使用花括号控制绝对路径

### 5.3.2 switch 语句

case 标签必须是整型常量表达式  
任何连个 case 标签的值不能相同  
default 也是一种特殊的 case 标签

- switch 内部的控制流
	- 如果某个 case 标签匹配成功，将从该标签开始向后顺序执行所有 case 分支，除非程序显式地中断了这一过程，否则知道 switch 的结尾处才会停下来
- 漏写 break 容易引发缺陷
- switch 内部的变量定义
	不允许跨过变量的初始化语句直接跳转到该变量作用域内的一个位置

## 5.4 迭代语句

### 5.4.1 while 语句
只要条件为真，while 语句就重复地执行循环体

- 使用 while 循环

### 5.4.2 传统的for语句
```cpp
for (init-statment;condition;expression)
	statement
```

init-statement 必须为以下三种形式中的一种 声明语句，表达式语句或者空语句

- for语句头中的多重定义
	init-statement 可以定义多个对象，但是只能有一条声明语句，因此所有变量类型必须相同
- 省略 for 语句头的某些部分
	使用空语句

### 5.4.3 范围 for 语句
```cpp
for (declaration : expression)
	statement
```
expression 表示的必须是一个序列，要求拥有能返回迭代器的 begin 和 end 成员  

### 5.4.4 do while 语句
do while 语句先执行循环体后检查条件，不论条件如何，都至少执行一次循环

```cpp
do
	statement
	while (condition);
```

不允许在条件部分定义变量


## 5.5 跳转语句

### 5.5.1 break 语句
break 语句只能出现在迭代语句或者 switch 语句内部(包括嵌套在此类循环里的语句或块的内部)
作用范围为最近的循环或者 switch

### 5.5.2 continue 语句
终止最近的循环中的当前迭代并立即开始下一次迭代
只能出现在 for、while和do while 循环内部，或者嵌套在此类循环里的语句或块的内部

### 5.5.3 goto 语句

从 goto 语句无条件跳转到同一函数内的令一条语句

```cpp
goto label;
label: expression
```
标签标识符可以和程序中其他实体的标识符使用同一个名字而不会互相干扰  
goto 语句和控制权转向的那条带标签的语句必须位于同一个函数之内

## 5.6 try语句块和异常处理

### 5.6.1 throw表达式

包含关键字 throw 和紧随其后的一个表达式，其中表达式的类型就是抛出的异常类型

### 5.6.2 try 语句块
```cpp
try{
	program-statements
} catch (exception-declaration){
	handler-statements
} catch (exception-declaration){
	handler-statements
}
```
try块后跟一个或多个 catch 子句，其中括号内为异常声明，之后为执行内容

### 5.6.3 标准异常
- exception 头文件
- stdexcept 头文件
	- 
	|name|explanation|
	|---|---|
	|exception|常见问题|
	|runtime_error|只有运行时才能检测出的问题|
	|range_error|运行时错误，生成结果超出了有意义的值域范围|
	|overflow_error|运行时错误，计算上溢|
	|underflow_error|运行时错误，计算下溢|
	|logic_error|程序逻辑错误|
	|domain_error|逻辑错误，参数对应的结果不存在|
	|invalid_argument|逻辑错误，无效参数|
	|length_error|逻辑错误，试图创建一个超出该类型最大长度的对象|
	|out_of_range|逻辑错误，使用一个超出有效范围的值|
- new 头文件
- type_info 头文件

## 6 函数

包括部分
- 返回类型
- 函数名字
- 由0或者多个形参组成的列表
- 函数体

- 函数的形参列表
	- 空形参
	```cpp
	void f1() //隐式定义
	void f2(void) //显式定义
	```
	- 形参列表，每个形参都是一个含有声明符的声明

### 6.1.1 局部对象
名字具有作用域，对象具有生命周期

- 局部静态变量
	在程序的执行路径第一次经过对象定义语句时初始化，并且直到程序终止才被销毁
	`static`

### 6.1.2 函数声明
函数声明也被称为函数原型，可以包含函数三要素

- 在头文件中进行函数声明

### 6.1.3 分离式编译
- 编译和链接多个源文件
	编译器提供了分离式编译每个文件的机制，这一过程通常会产生一个后缀名为 .obj 或 .o 的文件，包含对象代码