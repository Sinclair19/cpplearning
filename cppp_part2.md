PART 2 C++标准库

# 8 IO 库

## 8.1 IO 类
|头文件|类型|
|---|---|
|iostream|istream, wisdtream 从流读取数据<br>ostream, wostream 向流写入数据<br>iostream, wisotream 读写流|
|fstream|ifstream, wifstream 从文件读取<br>ofstream, wofstream 向文件写入数据<br>fstream, wfstream读写文件|
|sstream|istringstream, wistringstream 从 string 读取数据<br>ostringstream, wostringstream 向 string 写入数据 <br>stringstream, wstringstream 读写 string|

为了支持宽字符语言，标准库定义了一组类型和对象来操纵 wchar_t 类型的数据，宽字符版本以一个 w 开始

- IO 类型间的关系
    标准库可以使我们忽略这些不同类型的流之间的差异，通过继承机制实现
    继承机制声明一个特定的类继承自另一个类，我们通常可以将一个派生类(继承类)对象当作其基类对象来使用

### 8.1.1 IO 对象无拷贝或赋值
不能拷贝或对 IO 对象赋值

读写一个 IO 对象会改变其状态，因此传递和返回的引用不能是 const 的

### 8.1.2 条件状态

|sentences|expression|
|---|---|
|strm::iostate|strm一种IO类型，提供了表达条件状态的完整功能|
|strm::badbit|指出流已崩溃|
|strm::failbit|指出一个IO操作失败了|
|strm::eofbit|流到达了文件结束|
|strm::goodbit|流未处于错误状态，此值保证为零|
|s.eof()|eofbit置位 true|
|s.fail()|failbit置位 true|
|s.bad()|batbit置位 true|
|s.good()|有效状态 true|
|s.clear()|将所有条件状态复位，设置为有效 返回 void|
|s.clear(flag)|将s中对应条件状态位复位 返回void|
|s.setstate(flag)|flags标志位，将对应条件状态置位 返回void|
|s.rdstate()|返回当前状态, 返回类型位 strm::iostate|


一旦一个流发生错误，其上后续的 IO 操作都会失败，只有当一个流处于无措状态时，才可以从它读取数据，向它写入数据

确定一个流对象的状态的最简单的方法是将它当作一个对象来使用  
`while(cin>>word)`

- 查询流的状态
    将流当作条件使用代码等价于 `fail()`
- 管理状态条件

### 8.1.3 管理输出缓冲
- 原因
    - 程序正确结束
    - 缓冲区满时，需要刷新缓冲
    - endl等操作符显式刷新缓冲区
    - 用操作符unitbuf 设置流的内部状态
    - 当读写被关联的流时，关联道德流的缓冲区会被刷新
- 刷新输出缓冲区
    - endl
    - flush 刷新但不输出任何额外字符
    - ends 向缓冲区插入一个空字符，然后刷新
- unitbuf 操作符
```cpp
cout<< unitbuf //所有输出操作都会立即刷新缓冲区
cout << nounitebuf //回到正常的缓冲方法
```
- 关联输入和输出流

## 8.2 文件输入输出
`ifstream`从一个给定文件读取数据  
`ofstream`向一个给定文件写入数据  
`fstream`可以读写文件  

`fstream` 特有操作
|||
|---|---|
|fstream fstrm|创建一个未绑定的文件流|
|fstream fstrm(s)|创建一个fstream，应打开名为s的文件|
|fstream fstrm(s,mode)|指定mode打开文件|
|fstrm.open(s)|打开名为s的文件，与fstrm绑定|
|fstrm.close()|关闭与fstrm绑定的文件|
|fstrm.is_open|返回一个bool值，指出与fstrm关联的文件是否成功打开且尚未关闭|

### 8.2.1 使用文件流对象
- 用 fstram 代替 iostream&
- 成员函数 open 和 close
定义一个空文件六对象，随后调用 open 将它与文件关联起来
```cpp
ifstream in(ifile);
ofstream out;
out.open(ifile + ",copy")
```
进行 open 是否成功的检测
`if(out)`

- 自动构造和析构
当一个 fstream对象被销毁时，close 会自动调用

### 8.2.2
每个流都有一个关联的文件模式
|||
|---|---|
|in|以读方式打开|
|out|以写方式打开|
|app|每次写操作前均定位到文件末尾|
|ate|打开文件后立即定位到文件末尾|
|trune|阶段文件|
|binary|以二进制方式进行IO|

- 以out模式打开文件会丢弃已有数据
默认情况下，当我们打开一个 ofstream 时，文件的内容会被丢弃，阻止一个 ofstream 清空给定文件内容的方式是同时指定 app 模式
```cpp
ofstream app("file2", ofstream::app);
ofstream app2("file2", ofstream::out | ofstram::app);
```
- 每次调用 open 时都会确定文件模式
每次打开文件时，都要设置文件模式，可能是显式地设置，也可能是隐式地设置，当程序未指定模式时，就是用默认值

