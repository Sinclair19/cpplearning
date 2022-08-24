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


## 8.3 string 流
`istringstream` 从string对取数据  
`ostringstream` 向string写入数据
`stringstream` 既可从string读数据也可向string写数据  
`stringstream` 特有地操作  
|||
|---|---|
|sstream strm|strm是一个未绑定地stringstream对象，sstream是头文件sstream中定义地一个类型|
|sstream strm(s)|strm是一个sstream对象，保存string s 地一个拷贝，此构造函数是explicit的|
|strm.str()|返回strm所保存的string的拷贝|
|strm.str(s)|将string s 拷贝到strm中，返回 void|

### 8.3.1 使用 istringstream
当某些工作是对整行文本进行处理，而其他一些工作是处理行内的单个单词时，通常可以使用 istringstream
```cpp
struct PersonInfo {
    string name;
    vector<string> phones;
};
string line, word;
vector<PersonInfo> people;
while (getline(cin,line)){
    PersonInfo info;
    istringstream record(line);
    record >> info.name;
    while (record >> word)
        info.phones.push_back(word);
    people.push_back(info);
}
```

### 使用 ostringstream
通过将内容写入到一个内存 ostringstream 中再统一进行输出

# 9 顺序容器

## 9.1 顺序容器概述
- 向容器添加或从容器中删除元素的代价
- 非顺序访问容器中元素的代价  

顺序容器类型  
|||
|---|---|
|vector|可变大小数组，支持快速随机访问，在尾部之外的位置插入或删除元素可能很慢|
|deque|双端队列，支持快速随机访问，在头尾位置插入删除速度很快|
|list|单向链表，只支持单向顺序访问，在链表任何位置进行插入/删除操作速度很快|
|forward_list|单向列表，只支持单向顺序访问，在链表任何位置进行插入/删除操作速度都很快|
|array|固定大小数组，支持快速随机访问，不能添加或删除元素|
|string|与vector相似的容器，但专门用于保存字符，随机访问快，在尾部插入删除速度块|

- 确定使用哪种顺序容器
    通常，使用vector是最好的选择，除非你有很好的理由选择其他容器
    - 如果你的程序有很多小的元素，且空间额外开销很重要，则不要使用list 或 forward_list
    - 如果程序要求随机访问元素，应使用 vector 或 deque
    - 如果程序要求在容器的中间插入或删除元素，应使用 list 或 forward_list
    - 如果程序需要在头尾位置插入或删除元素，但不会在中间位置进行插入或删除操作，则使用 deque
    - 如果程序只有在读取输入时才需要在容器中间位置插入元素，随后需要随机访问元素，则
        - 调用sort函数重排 vector 避免在中间位置添加元素
        - 考虑在输入阶段使用 list ，一旦输入完成，将内容拷贝到 vector 中
    
## 9.2 容器库概览
- 容器类型上的操作形成了一种层次
    - 某些操作是所有容器类型都提供的
    - 另外一些操作仅针对顺序容器、关联容器或无序容器
    - 还有一些操作只适用于一小部分容器

- 对容器可以保存的元素类型的限制
    - 较旧的编辑器可能需要再练个尖括号之间键入空格

### 9.2.1 迭代器
- 迭代器范围
    - 由一对迭代器表示，分别指向同一个容器中的元素或者尾元素之后的位置，属于左闭右合区间
- 使用左闭右合范围蕴含的编程设定
    - begin 与 end 想等，则范围为空
    - 如果 begin 与 end 不等，则范围至少包含一个元素，且 begin 指向该范围中的第一个元素
    - 我们可以对 begin 递增若干次，使得 begin == end

### 9.2.2 容器类型成员
```cpp
//通过 list<string>定义的一个迭代器类型
list<string>::iterator iter;
//通过 vector<int> 定义的difference_type
vector<int>::difference_type count;
```

### 9.2.3 begin 和 end 成员
begin 和 end 具有多版本  
```cpp
list<string> a = {"a","b","c"};
auto it1 = a.begin(); // list<string>::iterator
auto it2 = a.rbegin(); // list<string>::reverse_iterator
auto it3 = a.cbegin(); // list<string>::const_iterator
auto it4 = a.crbegin(); // list<string>::const_reverse_iterator
```
当不需要写访问时，应使用 cbegin 和 cend

### 9.2.4 容器定义和初始化
- 将一个容器初始化未另一个容器的拷贝
    - 方法
        - 直接拷贝整个容器
        - 拷贝由一个迭代器对指定的元素范围(array除外)
    - 当将一个容器初始化为另一个容器的拷贝时，两个容器的容器类型和元素类型都必须相同
    ```cpp
    deque<string> authList(authors.begin(), it);
    // 拷贝元素，直到（但不包括）it 指向的元素
    ```
- 列表初始化
- 与顺序容器大小相关的构造函数
    只有顺序容器的构造函数才接受大小参数，并联容器并不支持
- 标准库 array 具有固定大小
    - 当定义一个 array 时，除了指定元素类型，还要指定容器大小
  
### 9.2.5 赋值和 swap
- 容器赋值运算
    |||
    |---|---|
    |c1 = c2|将c1中的元素替换为c2中元素的拷贝，c1 c2 必须具有相同的类型|
    |c = {a,b,c}|将c1中元素替换为初始化列表中元素的拷贝(array不适用)|
    |swap(c1,c2)<br>c1.swap(c2)|交换c1和c2中的而元素，两者必须具有相同的类型，swqp通常比从c2向c1拷贝元素快得多|
    |seq.assign(b,e)|将seq中的元素替换为迭代器b和e所表示的范围中的元素，迭代器b和e不能指向seq中的元素|
    |seq.assign(i1)|将swq中的元素替换为初始值列表i1中的元素|
    |seq.assign(n,t)|将seq中的元素替换为n个值为t|
- 使用 assign (仅顺序容器)
    - 赋值运算
        - 要求左边和右边的运算对象具有相同的类型
        - 将右边运算对象中所有元素拷贝到左边运算对象中
    - assign 允许我们从一个不同但相容的类型赋值，或者从容器中的一个子序列赋值
    - saaign 操作用参数所指定的元素的拷贝替换左边容器中的元素
- 使用 swap
    - swap操作会交换两个相同类型容器的内容
    - swap 不对任何元素进行拷贝、删除或插入操作，因此可保证在常数时间内完成
    - 指向容器的迭代器、引用和指针在 swap 操作之后不会失效，仍指向 swap 操作之前的那些元素
  
### 9.2.6 容器大小操作
1. 成员函数 size 返回容器中元素的数目
2. empty 当 size 为 0 时返回布尔值 true，否则返回 false
3. max_size 返回一个大于或等于该类型容器所能容纳的最大元素值
4. forward_list 支持 max_size 和 empty， 但不支持 size

### 9.2.7 关系运算符
- 所有容器都支持相等运算符(==,!=)
- 除了无序关联容器外的所有容器都支持关系运算符(>,>=,<,<=) 
- 关系运算符两边的运算对象必须是相同类型的容器，且必须保存相同类型的元素
两个容器的比较
1. 如果两个容器具有相同大小且所有元素都两两对应想等，则这两个容器想等；否则不等
2. 如果两个容器大小不同，但较小的容器每个元素都等于较大容器中的对应元素，则较小容器小于较大容器
3. 如果两个容器都不是另一个容器的前缀子序列，则他们的比较结果取决于第一个不相等的元素的比较结果

- 容器的关系运算符使用元素的关系运算符完成比较


## 9.3 顺序容器操作

### 9.3.1 向顺序容器添加元素
向一个 vector string deque 插入元素会使所有指向容器的迭代器、引用和指针失效  

- 使用 push_back
    - 将一个元素追加到一个容器的尾部
    - 当我们用一个对象来初始化元素时，或将一个对象插入到容器中时，实际上放入到容器中的是对象值的一个拷贝，而不是对象本身
- 使用 push_front
    - list, forward_list, deque 支持将元素插入到容器头部
- 在容器中的特定位置添加元素
    - vector, deque, list, string 支持insert成员
    - forward_list 具有特殊的 insert 成员
    - 将元素插入到 vector, deque 和 string 中的任何位置都是合法的，然而这样做可能很耗时
- 插入范围元素
    - `svec.insert(sevc.end(), 10, "anna")` 将10个元素插入到 svec 的尾部
    - 接受元素个数或范围的 insert 版本返回指向第一个新加入元素的迭代器
- 使用 insert 的返回值
- 使用 emplace 操作
    - 根据元素的类型而变化，参数必须与元素类型的构造函数相匹配
  
### 9.3.2 访问元素
- 包括 arrary 在内的每个顺序容器都有一个 front 成员函数
- 除 forward_list 之外的所有容器都有一个 back 成员函数

|||
|---|---|
|c.back()|返回 c 中尾元素的引用|
|c.front()|返回 c 中首元素的引用|
|c[n]|返回 c 中下标为 n 的元素的引用|
|c.at(n)|返回下标为 n 的元素的引用|

- 访问成员函数返回的是引用
    使用 auto 变量来保存函数的返回值

- 下标操作和安全的随机访问
  

### 9.3.3 删除元素
|||
|---|---|
|c.pop_back()|删除 c 中的尾元素|
|c.pop_front()|删除 c 中首元素|
|c.erase(p)|删除迭代器 p 所指定的元素，返回一个只想被删元素之后元素的迭代器|
|c.erase(b,e)|删除迭代器 b 和 e 所指定范围内的元素，返回一个指向最后一个被删元素之后元素的迭代器|
|c.clear()|删除 c 中所有元素|

- pop_front 和 pop_back 成员函数

- 从容器内部删除一个元素
    erase 可以从容器中指定位置删除元素，我们可以删除由一个迭代器指定的单个元素，也可以删除由一对迭代器指定的范围内的所有元素
- 删除多个元素
    - 删除所有元素 
    ```cpp
    slist.clear();
    slist.erase(slist.bvegin(), slist.end()); //二者等价
    ```

### 9.3.4 特殊的 forward_list 操作
当添加或删除一个元素时，删除或添加的元素之前的那个元素的后继会发生改变  
为了添加或删除一个元素，我们需要访问其前驱，以改变前驱的链接
定义了 before_begin(返回一个首前迭代器)
1. insert_after
2. emplace_after
3. erase_after

### 9.3.5 改变容器大小
用 resize 来增大或缩小容器
|||
|---|---|
|c.resize(n)|调整 c 的大小为 n 个元素，若 n<c.size() 则多出的元素会被丢弃，若必须添加新元素，对新元素初始化|
|c.resize(n,t)|调整 c 的大小为 n 个元素，任何新添加的元素都初始值为值 t|


### 9.3.6 容器操作可能使迭代器失效
- 添加元素
    - 容器是vector 或 string ，且存储空间重新分配，则指向插入位置之前的元素的迭代器、指针和引用都会失效
    - 对于 deque，插入到除首尾位置之外的任何位置都会导致迭代器、指针和引用失效，如果在首尾位置添加元素，迭代器会失效
    - 对于 list 和 forward_list，指向容器的迭代器和首前迭代器、指针和引用仍有效
- 删除元素
    - 对于 list 和 forward_list，只想容器其他位置的迭代器、引用和指针仍有效
    - 对于 deque，如果在首尾之外的任何位置删除元素，那么指向被删除元素外其他元素的迭代器、引用或指针也会失效；删除尾元素，尾后迭代器影响；删除首元素，这些不会影响
    - 对于 vector 和 string，指向被删元素之前的迭代器、引用和指针仍有效
- 编写改变容器的循环程序
    ```cpp
    vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
    auto iter = vi.begin();
    whild(iter != vi.end()){
        if(iter != vi.end()){
            iter = vi.insert(iter, *iter);
            iter += 2; //向前移动迭代器
        } else
            iter = vi.erase(iter);
    }
    ```
    调用 erase 后，不必递增迭代器，erase 返回的迭代器已经指向序列中下一个元素  
    调用 insert 后，需要递增迭代器两次(insert 在给定位置之前插入新元素，然后返回指向新元素的迭代器)
- 不要保存 end 返回迭代器
    - 如果在一个循环中插入/删除 deque 、 string 或 vector 中的元素，不要缓存 end 返回的迭代器 


## 9.4 vector 对象是如何增长的
当不得不获取新的内存空间时，vector和 string的实现通常会分配比新的空间需求更大的内存空间  
- 管理容量的成员函数
    |||
    |---|---|
    |c.shrink_to_fit()|将 capacity()减少为与size()相同大小|
    |c.capacity()|不重新分配内存空间的话，c 可以保存多少元素|
    |c.reserve(n)|分配至少能容纳 n 个元素的内存空间|
- reseve 并不改变容器中元素的数量，它仅影响预先分配多大的内存空间
    调用 reserve 永远不会减少容器占用的内存空间
- capacity 和 size
    size 指它已经保存的元素的数目
    capacity 则是在不分配新的内存空间的前提下它最多可以保存多少元素
每个 vector 实现都可以选择自己的内存分配策略，但是必须遵守一条原则是，只有当迫不得已时才可以分配新的内存空间


## 9.5 额外的 string 操作

### 9.5.1 构造 string 的其他方法
|||
|---|---|
|string s(cp,n)|s 是 cp 指向的数组中前 n 个字符的拷贝。此数组至少应该包含 n 个字符|
|string s(s2,pos2)|s 是 string s2 从下标 pos2 开始的字符的拷贝。若 pos2>s2.size()，构造函数的行为未定义|
|string s(s2, pos2, len2)|s 是 string s2从下标pos2 开始 len2 个字符的拷贝。若pos2>s2.size()，构造函数的行为未定义。不管 len2 的值是多少，构造函数之多拷贝s2.size()-pos2个字符|

通常当我们从一个 const char*创建 string 时，指针指向的数组必须以空字符结尾，拷贝操作遇到空字符时停止  
如果传递给构造函数一个计数值，数组就不必以空字符结尾，如果我们未传递计数值且数组也未以空字符结尾，或者给定计数值大于数组大小，则构造函数的行为是未定义的  

- substr 操作
  - 返回一个 string，是原始string的一部分或全部的拷贝，可以传递给 substr 一个可选的开始位置和计数值

### 9.5.2 改变 string 的其他方法
除了接受迭代器的 insert 和 erase 版本外，string 还提供了接收下标的版本，下标指出了开始删除的位置，或是insert 到给定值之前的位置

- append 和 replace 函数
    - append 未在 string 末尾进行插入操作的一种简写形式
        - 将字符追加到末尾，返回一个指向字符串的引用
    - replace 是调用 erase 和 insert 的一种简写形式
        - 删除一个范围内的字符，替换为另一个字符
- 改变 string 的多重重载函数
    - assign 和 append 函数无须指定删除元素范围的方式，可以通过一个位置和一个长度来指定位置，也可以通过一个迭代器范围来指定
    - assign 总是替换 string 中的所有内容， append 总是将新字符追加到 string 末尾
    - insert 函数允许我们用两种方式指定插入点: 用一个下标或一个迭代器，在两种情况下，新元素都会插入到指定下标之前的位置
    - append 总是将新字符追加到 string 末尾

### 9.5.3 string 搜索操作
- 搜索成功，返回一个 `string::size_type` 值，表示匹配发生位置的下标  
- 搜索失败, 则返回一个名为 `string::nops`的 static 成员
    - 标准库将 nops 定义为一个 `const string::size_type` 类型，并初始化为 -1  

|||
|---|---|
|`s.find(args)`|查找 s 中 args 第一次出现的位置|
|`s.rfind(args)`|查找 s 中 args 最后一次出现的位置|
|`s.find_first_of(args)`|在 s 中查找 args 中任何一个字符第一次出现的位置|
|`s.find_last_of(args)`|在 s 中查找 args 中任何一个字符最后一次出现的位置|
|`s.find_first_not_of(args)`|在 s 中查找第一个不在 args 中的字符|
|`s.find_last_not_of(args)`|在 s 中查找最后一个不在 args 中的字符|

`args` 必须为以下形式
1. (`c,pos`) 从 s 中位置 pos 开始查找字符 c， 默认为0
2. (`s2,pos`) 从 s 中位置 pos 开始查找字符串 s2, 默认未0
3. (`cp,pos`) 从 s 中位置 pos 开始查找指针 cp 指向的以空字符串结尾的 C 风格字符串，默认为0
4. (`cp,pos,n`) 从 s 中位置 pos 开始查找指针 cp 指向的数组的前 n 个字符，无默认值

- 指定在哪里开始搜索
- 逆向搜索
    - `rfind`

### 9.5.4 compare 函数
根据 s 等于大于还是小于参数指定的字符串 返回 0 正数或负数
1. (`s2`) 比较 s 和 s2
2. (`pos1, n1, s2`) 将 s 中从 pos1 开始的 n1 个字符与 s2 进行比较
3. (`pos1, n1, s2, pos2, n2`) 将 s 中从 pos1 开始的 n1 个字符与 s2 中从 pos2 开始的 n2 个字符进行比较
4. (`cp`) 比较 s 与 cp 指向的以空字符串结尾的字符数组
5. (`pos1, n1, cp`) 将 s 中从 pos1 开始的 n1 个字符与 cp 指向的以空字符结尾的字符数组进行比较
6. (`pos1, n1, cp, n2`) 将 s 中从 pos1 开始的 n1 个字符与指针 cp 指向的地址开始的 n2 个字符进行比较

### 9.5.5 数值转换
```cpp
int i = 42;
string s = to_string(i);
double d = stod(s);
```
如果 string 不能转换成某个数值 `invalid_argument`
如果转换得出的数值无法用任何类型来表示 `out_of_range`
