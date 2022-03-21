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

