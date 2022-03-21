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