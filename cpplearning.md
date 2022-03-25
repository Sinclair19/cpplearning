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


