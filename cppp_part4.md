PART 4 高级主题

# 17 标准库特殊设施

## 17.1 tuple 类型
tuple 是类似 pair 的模板  
不同 tuple 类型的成员类型不同，但一个 tuple 可以有任意数量的成员，每个确定的 tuple 类型的成员数目是固定的，但一个 tuple 类型的成员数目可以与另一个 tuple 类型不同  
tuple 类型及其伴随类型的函数都定义在 tuple 头文件中

1. `tuple<T1,T2, ..., Tn> t;`  t 是一个 tuple，成员数为 n，第 i 个成员的类型为 Ti，所有组成员都进行值初始化
2. `tuple<T1,T2, ..., Tn> t(v1, v2, ..., vn);`  t 是一个 tuple，成员类型是 T1..Tn，每个成员用对应的初始值 vi 进行初始化，此构造函数时 explicit 的
3. `make_tuple(v1, v2, ..., vn)` 返回一个用给定初始值初始化的 tuple，tuple 的类型从初始值的类型推断
4. `t1 == t2`  当两个 tuple 具有相同数量的成员且成员对应相等时，两个 tuple 相等，这两个操作使用成员的 == 运算符来完成，一旦发现某队成员不等，接下来的成员就不用比较了
5. `t1 relop t2`  tuple 的关系运算使用字典序。两个 tuple 必须具有相同数量的成员。使用 < 运算符比较 t1 的成员和 t2 中的对应成员
6. `get<i>(t)` 返回 t 的第 i 个数据成员的引用；如果 t 是一个左值，结果是一个左值引用；否则，结果是一个右值引用。 tuple 的所有成员都是 public 的
7. `tuple_size<tupleType>::value`  一个类模板，可以通过一个 tuple 类型来初始化。它有一个名为 value 的 `public constexpr static` 数据成员，类型为 size_t, 表示给定 tuple 类型中成员的数量
8. `tuple_element<i, tupleType>::type` 一个类模板，可以通过一个整形常量和一个 tuple 类型来初始化，有一个名为 type 的 public 成员，表示给定 tuple 类型中指定成员的类型

可以将 tuple 看作一个快速而随意的数据结构

### 17.1.1 定义和初始化 tuple
定义一个 tuple时，需要指出每个成员的类型  
可以使用 tuple默认构造函数对每个成员进行初始化  
该构造函数为 explicit 的，必须使用直接初始化语法
```cpp
tuple<size_t, size_t, size_t> threeD = {1,2,3}; //incorrect
tuple<size_t, size_t, size_t> threeD{1,2,3}; //correct
```
可以使用 make_tuple 生成 tuple 对象，
其使用初始值的类型来推断 tuple 的类型

- 访问 tuple 的成员
    - 使用 get 标准库函数模板
    - 指定一个显式模板实参指出像访问第几个成员
        ```cpp
        auto book = get<0>(item);  //返回第一个成员
        auto cnt = get<1>(item);  //返回第二个成员
        auto price = get<2>(item)/cnt;  //返回item最后一个成员
        get<2>(item) *= 0.8; //打折20%
        ```
    - <> 中必须是一个整型常量表达式，从 0 开始计数
    - 查询 tuple 成员的数量和类型
        ```cpp
        typedef decltype(item) trans;
        size_t sz = tuple_size<trans>::value; // 返回成员个数
        tuple_element<1, trans>::type cnt = get<1>(item); // cnt 是一个 int
        ```
    - 关系和相等运算符
        - tuple 的关系和相等运算符的行为类似容器的对应操作，逐对比较左侧 tuple 和右侧 tuple 的成员
        - 只有两个 tuple 具有相同数量的成员时，才可以比较它们，且每对成员的的比较运算符都必须合法
        - tuple 定义了 < 和 == 运算符，可以将 tuple 序列传递给算法，可以在无序容器中将 tuple 作为关键字类型 

### 17.1.2 使用 tuple 返回多个值
tuple 的一个常见用途是从一个函数返回多个值
- 返回 tuple 的函数
    - 编写查找给定书籍的函数
        
        ```cpp
        typedef tuple<vector<Sales_data>::size_type, vector<Sales_data>::const_iterator, vector<Sales_data>::const_iterator> matches;
        vector<matches> findBook(const vector<vector<Sales_data>> &files, cosnt string &book){
            vector<matches> ret;
            for (auto it = files.cbegin(); it != files.cend(); ++it){
                auto found = equal_range(it->cbegin(),it->cend(),book, compareIsbn);
                if (found.first != found.second){
                    ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second));
                }
            }
            return ret;
        }
        ```
    - equal_range 标准库算法
        - 前两个实参是输入序列的爹大气，第三个参数是一个值
        - 默认情况下 equal_range 使用 < 运算符来比较元素
        - 返回一个迭代器 pair，表示元素的范围，若未找到则两个迭代器相等，表示空范围，否则 pair 的 first 成员表示第一台匹配的记录，second 表示匹配的尾后尾置 
- 使用函数返回的 tuple
    ```cpp
    void reportResults(istream &in, ostream &os, const vector<vector<Sales_data>> &files){
        string s;
        while (in >> s){
            auto trans = findBook(files, s);
            if (trans.empty()){
                cout << s << "not found in any stores" << endl;
            }
            for (const auto &store : trans){
                os << "stores" << get<0>(store) <<" sales: "<< accumulate(get<1>(store), get <2>(store), Sales_data(s)) << endl;
            }
        }
    }
    ```
    
## 17.2 bitset 类型
标准库定义了 bitset 类，使得位运算的使用更为容易，并且能够处理超过最长整型类型大小的位集合  
定义在 头文件 bitset 中

### 17.2.1 定义和初始化 bitset
bitset 类是一个类模板，类似 array 类，具有固定的大小  
当我们定义一个 bitset 时，需要声明它包含多少个二进制位  
`bitset<32> bitvec(1U); //32位 低位为1，其他位为0`
大小必须是一个常量表达式，这条语句定义 bitvec 为一个包含 32 位的 bitset  
通过位置访问，二进制位的位置从 0 开始编号， 
bitvec 包含编号从 0 到 31 的 32 个二进制位  
编号从 0 开始的二进制位被称为低位，编号到 31 结束的二进制位被称为高位
- 初始化 bitset 的方法
    - bitset<n> b; b 有 n 位；每一位均为 0，此构造函数是一个 constexpr
    - bitset<n> b(u); b 是 unsigned long long 值 u 的低 n 位的拷贝，如果 n 大于 unsigned long long 的大小，则 b 中超过 unsigned long long 的高位被置为 0，此构造函数是一个 constexpr
    - bitset<n> b(s, pos, m, zero, one); b 是 string s 从位置 pos 开始 m 个字符的拷贝。s 只能包含字符 zero 或 one; 如果 s 包含任何其他字符，构造函数会抛出 invalid_argument 异常。字符在 b 中分别保存为  zero 和 one。 pos 默认为 0，m 默认为 string::npos, zero 默认为 '0'， one 默认为 '1' 
    - bitset<n> b(cp, pos, m, zero, one); 与上一个构造函数相同 ，从 cp 指向的字符数组中拷贝字符，如果未提供 m，则 cp 必须指向一个 C 风格字符串，如果提供了 m， 则从 cp 开始必须至少有 m 个 zero 或 one 字符
- 用 unsigned 值初始化 bitset
    - 用一个整数值来初始化 bitset 时，此值将被转换为 unsigned long long 类型并被当作位模式来处理
    - bitset 中的二进制位将是此模式的一个副本
    - 如果 bitset 的大小大于一个 unsigned long long 中的二进制数，则剩余的高位被置为 0，如果 bitset 的大小小于一个 unsigned long long 中的二进制位数，则只使用给定值中的低位，超出 bitset 大小的高位被丢弃
- 从一个 string 初始化 bitset
    - 可以从一个 string 或一个字符数组指针来初始化 bitset，两种情况下，字符都直接表示位模式
    - 如果 string 包含的字符数比 bitset 少，则 bitset 的高位被置为 0
    - string 的下标编号习惯与 bitset 正相反，string 中下标最大的字符用来初始化 bitset 中的低位
        ```cpp
        string str("1111111000000111");
        bitset<32> bitvec5(str, 5, 4); //从 str[5]开始的 4个二进制位
        bitset<32> bitvec6(str, str.size()-4); // 使用最后四个字符
        ```

## 17.3 正则表达式
正则表达式是一种描述字符序列的方法  
C++ 正则表达式库(RE库)，定义在 regex 中
- regex 表示有一个正则表达式的类
- regex_search 寻找第一个与正则表达式匹配的子序列
- regex_replace 使用给定格式替换一个正则表达式
- sregex_iterator 迭代器适配器，调用 regex_search 来遍历一个 string 中所有匹配的子串
- smatch 容器类，保存在 string 中搜索的结果
- ssub_match string 中匹配的子表达式的结果

函数 regex_match 和 regex_search 确定一个给定字符序列与一个给定 regex 是否匹配，如果输入序列中一个子串与表达式匹配，则 regex_search 函数返回 true  
- regex_search 和 regex_match 的参数  返回 bool 值，指出是否找到匹配
    - (seq, m, r, mft) 在字符串 seq 中查找 regex 对象 r 中的正则表达式， seq 可以是一个 string、表示范围的一对迭代器以及一个指向空字符结尾的字符数组的指针
    - (seq, r, mft) m 是一个 match 对象，用来保存匹配结果的相关细节。m 和 seq 必须具有兼容的类型，mft 是一个可选的 regex_constants::match_flag_type 值


### 17.3.1 使用正则表达式库
```cpp
string pattern("[^c]ei");
pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]";
regex r(pattern);
smatch results;
string test_str = "receipt freind theif receive";
if (regex_search(test_str, result, r))
    cout << result.str() << endl;
```

[^c] 表明希望匹配任意不是 'c' 的字符，而 [^c]ei 指出想要匹配这种字符后接 ei 的字符串  
默认情况下 regex 使用的正则表达式语言为 ECMAScript  
`[[::alpha]]` 匹配任意字幕  
`+` `*` 表示希望一个或多个 或 零个或多个 匹配  `[[::alpha:]]*` 将匹配零个或多个字母

- 指定 regex 对象的选项
    - 当我们定义一个 regex 或是对一个 regex 调用 assign 为其赋予新值时，可以指定一些标志来影响 regex 如何操作，这些标志控制 regex 如何操作，控制 regex 对象的处理过程

![regex 和 wrgex 选项](./sources/17_3_1_1.png)

编写一个正则表达式来识别上述任何一种扩展名邮寄其他普通文件扩展名

```cpp
regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
smatch results;
string filename;
while(cin >> filename)
    if (regex_search(filename, results, r))
        cout << results.str() << endl;
```

- 指定或使用正则表达式时的错误
    - 可以将正则表达式本身看作用一种简单程序设计语言编写的程序，正则表达式是在运行时，当一个 regex 对象被初始化或被赋予一个新模式时，才被“编译”的，与任何其他程序设计语言一样
    - 一个正则表达式的语法是否正确是在运行时解析的
    - 如果编写正则表达式存在错误，则在运行时会抛出一个类型为 regex_error 的异常，类似标准异常类型，regex_error 有一个 what 操作来描述发生了什么错误
    - regex error 还有名为 code 的成员，用来返回某个错误类型对应的数值编码
        ```cpp
        try {
            regex r("[[:alnum:]+\\.(cpp|cxx|cc)$", regex::icase);
        } catch (regex_error e)
        { cout<< e.what() << "\ncode:" << e.code() << endl; }
        ```
    - 正则表达式错误类型
        ![正则表达式错误类型](./sources/17_3_1_2.png)

- 正则表达式类和输入序列类型
    - 输入可以是普通 char 数据或 wchar_t 数据，字符可以保存在标准库 string 或是 char 数组中。 RE 为这些不同的输入序列都定义了对应的类型
    - 标准库还定义了一个 wregex 类保存 wachar_t，其操作与 regex 完全相同，两者唯一的差别是 wregex 的初始值必须使用 wchar_t 而不是 char
    - 匹配和迭代器类型更为特殊，类型的差异不仅在于字符类型，还在于序列是在标准库 string 中还是在数组中，smatch 表示 string 类型的输入序列; cmatch 表示字符数组序列; wsmatch 表示宽字符串 (wstring) 输入; wcmatch 表示宽字符数组
    - 对应的 string 版本 RE 库组件
        - `string`  regex, smatch, ssub_match, sregex_iterator
        - `const char*` regex, cmatch, csub_match, cregex_iterator
        - `wstring` wregex, wsmatch, wssub_match, wsregex_iterator
        - `const wchar_t*` wregex, wcmatch, wcsub_match, wcregex_iterator


### 17.3.2 匹配与 regex 迭代器类型
使用 sregex_iterator 来获得所有匹配
- sergex_iterator 操作
    |||
    |---|---|
    |`sregex_iterator it(b, e, r);`|一个 seregex_iterator，遍历迭代器 b 和 e 表示的 string。调用 sregex_search(b, e, r) 将 it 定位到输入中第一个匹配的位置|
    |`sregex_iterator end;`|sregex_iterator 的尾后迭代器|
    |`*it` <br> `it->`|根据最后一个调用 regex_search 的结果，返回一个 smatch 对象的引用或一个指向 smatch 对象的指针|
    |`++it` <br> `it++`|从输入序列当前匹配位置开始调用 regex_search。前置版本返回递增后迭代器，后置版本返回旧值|
    |`it1 == it2` <br>`it1 != it2`|如果两个 sregex_iterator 都是尾后迭代器，则它们相等两个非尾后迭代器是从相同的输入序列和 regex 对象构造，则它们相等|
    
    当将一个 sregex_iterator 绑定到一个 string 和一个 regex 对象时，迭代器自动定位到给定 string 中第一个匹配位置  
    sregex_iterator 构造函数对给定 string 和 regex 调用 regex_search, 当我们解引用迭代器时，会得到一个对应最近一次搜索结果的 smatch 对象，递增迭代器时，调用 regex_search 在输入 string 中查找下一个匹配
- 使用 sregex_iterator
    ```cpp
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern, regex::icase);
    for (sregex_iterator it(file.begin(), file.end(), r), end_it; it != end_it; ++it)
        cout << it->str() << endl;
    ```
- 使用匹配数据
    - smatch 和 ssub_match 允许我们获得匹配的上下文
    - 匹配类型有 prefix 和 suffix 成员，分别返回舒徐序列中当前匹配和之后部分的 ssub_match 对象
    - 一个 ssub_match 对象有两个名为 str 和 length 的成员，分别返回匹配的 string 和该 string 的大小
    - it -> prefix().str() | it -> str | it ->suffix().str()
        ```cpp
        for (sregex_iterator it(file.begin(),file.end(), r), end_it; it != end_it; ++it){
            auto pos = it->prefix().length();
            pos = pos >40 ? pos -40 : 0;
            cout << it ->prefix().str().substr(pos) << "\n\t\t>>>" << it->str() <<"<<<\n" << it->suffix().str().substr(0,40) << endl
        }
        ```
    - smatch 操作
        ![smatch 操作](sources/17_3_2_1.png)


### 17.3.3 使用子表达式
正则表达式中的模式通常包含一个或多个子表达式，一个子表达式是模式的一部分，本省也具有意义  
正则表达式语法通常用括号表示子表达式  
匹配对象除了提供匹配整体的相关信息外，还提供访问模式中每个子表达式的能力  
子匹配是按位置来访问的，第一个子匹配位置为 0，表示整个模式对应的匹配，随后是每个子表达式对应的匹配  
eg  
    filename -- foo.cpp 
results.str(0) -- foo.cpp 
results.str(1) -- foo
results.str(2) -- cpp

- 子表达式用于数据验证
    - 子表达式的一个常见用途是验证必须匹配特定格式的数据
    - ECMAScript 正则表达式语言的一些特性
        - `\{d}` 表示单个数字，而 `\{d}{n}` 表示一个 n 个数字的序列
        - 在方括号中的字符集合表示匹配这些字符中任意一个 (eg : `[-. ]`匹配短横线，点或空格)
        - 后接 `?` 的组件是可选的
        - 类似 C++， ECMAScript 使用反斜线表示一个字符本身而不是其特殊含义，由于模式包含括号，而括号是 EMCMAScript 中的特殊字符，因此必须使用 `\()` 来表示括号是我们模式的一部分而不是特殊字符
        - 反斜线是 C++ 特殊字符，在模式中出现 \ 的地方，必须用一个额外的反斜线来告知 C++ 需要一个反斜线字符而不是一个特殊符号
- 使用子匹配操作
    - 适用于 ssub_match, csub_match, wssub_match, wcsub_match
    - `matched` : 一个`publicboo`l数据成员，指出此`ssub_match` 是否匹配了
    - `first` `second` : `public` 数据成员, 指向匹配序列首元素和尾后位置的迭代器，如果未匹配，则 `first `和 `second` 是相等的
    - `length()` : 匹配的大小，如果 `match` 为 false，则返回 0
    - `str()` : 返回一个包含输入中匹配部分的 string，如果 `matched` 为 false，则返回空 string
    - `s = ssub` : 将 `ssub_match` 对象 ssub 转化为 string 对象 s，等价于 `s=ssub.str()` 转换运算符不是 explicit 的

### 17.3.4 使用 `regex_replace`
正则表达式还可以用在我们想将找到的序列替换为另一个序列的时候  
调用 `regex_replace`，接受一个输入字符序列和一个 `regex` 对象，还接受一个描述我们想要的输出形式字符串
- 正则表达式替换操作
    - `m.format(dest,fmt,mft)`  `m.format(fmt,mft)`
        - 使用格式字符串 fmt 生成格式化输出，匹配在 m 中，可选的 `match_flag_type` 标志在 mft 中  第一个版本写入迭代器 dest 指向的目的位置并接受 fmt 参数，可以是一个 string，也可以是表示字符数组中范围的一对指针  第二个版本返回一个 string，也可以是一个指向空字符结尾的字符数组的指针  mft 的默认值为 `format_default`
    - `regex_replace(dest, seq, r, fmt, mft)`  `regex_replace(seq, r, fmt, mft)`
        - 遍历 seq ，用 regex_search 查找与 regex 对象 r 匹配的子串  使用格式化字符串 fmt 和可选的  `match_flag_type` 标志来生成输出  第一个版本将输出写入到迭代器 dest 指定的位置，并接受一对迭代器 seq 表示范围  第二个版本返回一个 string，保存输出，且 seq 既可以是一个 string，也可以是指向空字符串结尾的字符中数组的指针，且 mft 的默认值为 `match_default`
    - 可以用 `$` 后跟子表达式的索引号来表示一个特定的子表达式
- 只替换输入序列的一部分
- 用来控制匹配和格式的标志
    - 标准库定义了用来在替换过程中控制匹配或格式的标志，这些标志可以传递给函数 regex_search 或 regex_match 或是类 smatch 的 format 成员
    - 匹配和格式化标志的类型名为 match_flag_type，值定义在 regex_constants 命名空间中
    - 为了使用 regex_constants 中的名字，需要在名字前同时加上两个命名空间的限定符  `using std::regex_constants::format_no_copy`  `using namespace std::regex_constants;`
    - 匹配标志 （定义在`regex_constants::match_flag_type`中）
        - `match_default` : 等价于 format_default
        - `match_not_bol` : 不将首字符作为行首处理
        - `match_not_eol` : 不将尾字符作为行尾处理
        - `match_not_bow` : 不将首字符作为单词首处理
        - `match_not_eow` : 不将首字符作为单词尾处理
        - `match_any` : 如果存在多余一个匹配，则可返回任意一个匹配
        - `match_not_null` : 不匹配任何空序列
        - `match_continuous` : 匹配必须从输入的首字符开始
        - `match_prev_avail` : 输入序列包含第一个匹配之前的内容
        - `format_default` : 用 ECMAScript 规则替换字符串
        - `format_sed` : 用 POSIX sed 规则替换字符串
        - `format_no_copy` : 不输出输入序列中未匹配的部分
        - `format_first_only` : 只替换子表达式的第一次出现
- 使用格式标志
    - 默认情况下 regex_replace 输出整个输入序列
    - 未与正则表示式匹配的部分会原样输出
    - 匹配的部分按格式字符串指定的格式输出
    - 可以通过 regex_replace 调用中指定 format_no_copy 来改变这种默认行为

## 17.4 随机数
C 和 C++ 依赖于 C 库函数 rand 生成随机数，此函数生成均与分布的伪随机整数，每个随机数的范围在 0 和一个系统相关的最大值(至少为 32767)之间  
rand 函数有一个问题，即使不是大多数，也有很多程序需要不同范围的随机数，为了解决试图转换 rand 生成的随机数的范围、类型或分布时，会引入非随机性  
定义在头文件 random 中的随机数库通过一组协作的类来解决：随机数引擎类和随机数分布类，一个引擎类可以生成 unsigned 随机数序列，一个分布类使用一个引擎类生成指定的，在给定范围内的，服从特定概率分布的随机数  
- 随机数库的组成
    |||
    |---|---| 
    |引擎|类型，生成随机 unsigned 整数序列|
    |分布|类型，使用引擎返回服从特定概率分布的随机数|
- C++ 程序不应该使用库函数 rand，而应使用 default_random_engine 类和恰当的分布类对象

### 17.4.1 随机数引擎和分布
随机数引擎式函数对象类  
定义了一个调用运算符，该运算符不接受参数并返回一个随机 unsigned 整数  
调用一个随机数引擎对象来生成原始随机数
```cpp
default_random_engine e;
for (size_t = 0; i < 10; ++i)
    cout << e() << endl;
```

- 随机数引擎操作  
    |||  
    |---|---|
    |`Engine e;`|默认构造函数，使用该引擎型默认的种子|
    |`Engine e(s);`|使用整数值 s 作为种子|
    |`e.seed(s)`|使用种子 s 重置引擎的状态|
    |`e.min()` <br> `e.max`|此引擎可生成的最小值和最大值|
    |`Engine::result_type`|此引擎生成的 unsigned 整数类型|
    |`e.discard(u)`|将此引擎推进 u 步; u 的类型为 unsigned long long|
- 分布类型和引擎
    - 为了得到在一个指定范围的数，需要使用一个分布类型的对象
        ```cpp
        uniform_int_distribution<unsigned> u(0,9);
        default_random_engine e;
        for (size_t i =0; i < 10; ++i)
            cout << u(e) << endl;
        ```
    - 分布类型定义了一个调用运算符，接受一个随机数引擎作为参数，分布对象使用它的引擎参数生成随机数，并将其映射到指定的分布
    - 当我们说随机数发生器时，是指分布对象和引擎对象的组合
- 比较随机数引擎和 rand 函数
    - e.min() e.max() 返回系统定义范围
- 引擎生成一个数值序列
    - 对一个给定的发生器，每次运行程序都会返回相同的数值序列
    - 将引擎和关联的分布对象定义成 static 的，使其在接下来的调用之间也会博爱吃住状态
    - 一个给定的随机数发生器一直会生成相同的随机数序列，一个函数如果定义了局部的随机数发生器，应该将其(包括引擎和分布对象)定义为 static 的，否则，每次 调用函数都会生成相同的序列
- 设置随机数发生器种子
    - 为引擎设置种子有两种方式，在创建引擎对象时提供种子，或者调用引擎的 seed 成员
    - 最常用的方法是调用系统函数 time
        - 定义在头文件 ctime 中
        - 返回从一个特定时刻到当前经过了多少秒
        - 函数 time 接受单个指针参数，指向用于写入时间的数据结构，如果此指针为空，则函数简单地返回时间
        - `default_random_engine e1(time(0))`
        - 由于 time 以秒计，此方式只适用与生成种子地间隔为秒级或更长地应用
    - 如果程序作为一个自动过程的一部分反复运行，将 time 地返回值作为种子地方式就无效了，可能多次使用地都是相同地种子

### 17.4.2 其他随机数分布
随机数引擎生成 unsigned 数，范围内的每个数都生成的概率相同，应用程序常常需要不同类型或不同分布地随机数，标准库通过定义不同随机数分布对象来满足两方面要求
- 生成随机数
    - 程序需要一个随机浮点数地源，特别是从 0 到 1 之间的随机数
    - 定义一个 uniform_real_distribution 类型地对象，让标准库来处理从随机整数到随机浮点数地映射，
        ```cpp
        default_random_engine e;
        uniform_real_distribution<double> u(0,1);
        for (size_t i = 0; i < 10; ++i)
            cout << u(e) << " ";
        ```
    - 分布类型地操作
        |||
        |---|---|
        |`Dist d;`|默认构造函数，使 d 准备好被使用|
        |`d(e)`|用相同地 e 连续调用 d 地话，会根据 d 的分布式类型生成一个随机数序列; e 是一个随机数引擎对象|
        |`d.min() <br> d.max()`|返回 d(e) 能生成的最小值和最大值|
        |`d.reset()`|重建 d 的状态，使得随后对 d 的使用不依赖于 d 已经生成的值|
- 使用分布的默认结果类型
    - 分布类型都是模板，具有单一的模板类型参数，表示分布生成的随机数的类型
    - 每个分布模板都有一个默认模板实参，生成浮点值的分布类型默认生成 double 值，而生成整型值的分布默认生成 int 值，由于分布类型只有一个模板参数，当希望使用默认随机数类型时要记得在模板名之后使用空尖括号
        `uniform_real_distribution<> u(0,1);`
- 生成非均匀分布的随机数
    - 正态分布
        ```cpp
        default_random_engine e;
        normal_distribution<> n(4,1.5);
        vector<unsigned> vals(9);
        for (size_t i = 0; i != 200; ++i){
            unsigend v = lround(n(e));
            if (v < vals.size())
                ++vals[v];
        }
        for (size_t j = 0; j != vals.size(); ++j)
            cout << j << ": " << string(vals[j], '*') << endl;
        ```
- bernoulli_distribution 类
    - 不接受模板参数，返回一个布尔值，然会 true 的概率为常熟 0.5
    - 由于引擎返回相同的随机数序列，所以必须在循环外声明引擎对象，否则，每步循环都会创建一个新引擎，从而每步循环都会生成相同的值，类似的，分布对象也要保持状态，因此也应该在循环外定义

## 17.5 IO 库再探
格式控制  
未格式化 IO  
随机访问  

### 17.5.1 格式化输入与输出
除了条件状态外，每个 iostream 对象还维护一个格式状态来控制 IO 如何格式化的细节，格式状态控制格式化的某些方面  
标准库定义了一组操作符来修改流的格式状态  
一个操作符是一个函数或是一个对象，会影响流的状态，并能用作输入或输出运算符的运算对象  
endl 输出一个换行符并刷新缓冲区  
- 很多操纵符改变格式状态
    - 控制熟知的输出形式以及控制补白的数量和位置
    - 大多数改变格式状态的操作符都是设置/复原成对的: 一个操作符用来将格式状态设置为一个新值，而另一个用来将其复原，恢复为正常的默认格式
    - 当操作符改变流的格式状态时，通常改变后的状态对所有后续 IO 都生效
- 控制布尔值的格式
    - 操作符改变对象的格式状态的一个例子是 boolalpha 操作符
        - 向 cout 写入了 boolalpha ，就改变了 cout 打印 bool 值的方式，后续打印 bool 值的操作都会打印 true 或 false 而非 1 或 0
        - 使用 noboolalpha 将内部状态恢复为默认格式
- 指定整型值的进制
    - 默认情况下，整型值的输入输出使用十进制，使用操作符 hex, oct, dec 将其改为 十六进制，八进制，或是改回十进制
    - 只影响整型运算对象，浮点值的表示形式不受影响
- 在输出中指出进制
    - showbase 操作符会在结果中显示进制，遵循与整型常量中指定进制相同的规范
        - 前导 0x 表示十六进制
        - 前导 0 表示八进制
        - 无前导字符串表示十进制
        - noshowbase 恢复原状态
    - uppercase 操作符来输出大写的 X 并将十六进制数字 a-f 以大写输出
- 控制浮点数格式
    - 以多高精度打印浮点数
        - 默认情况下按六位数字精度打印
    - 数值是是大因为十六进制，定点十进制还是科学计数法形式
        - 默认选择一种可读性更好的格式
    - 对于没有小数部分的浮点值是否打印小数点
        - 默认没有小数部分不打印小数点
    - 指定打印精度
        - 通过调用 IO 对象的 precision 成员或使用 setprecision 操作符来改变精度
            - precision 成员为重载的
                - 一个版本接受一个 int 值，将精度设置为此值
                - 另一个版本不接受参数，返回当前竞渡之
            - setprecision 操作符接受一个参数，用来设置精度
            - 定义在头文件 iomanip 中
    - 定义在 iostream 中的操作符
        ![](./sources/17_5_1_1.png)
        ![](./sources/17_5_1_2.png)
    - 指定浮点数计数法
        - 除非需要控制浮点数的表示形式，否则标准库选择计数法是最好的方式
        - 操作符 scientific 改变流的状态来使用科学技术法
        - 操作符 fixed 改变流的状态来使用定点十进制
        - 操作符 hexfloat 强制使用十六进制格式
        - 操作符 defaultfloat 将流恢复到默认状态
    - 打印小数点
        - showpoint 操作符强制打印小数点
        - noshowpoint 恢复
    - 输出补白
        - setw 指定下一个数字或字符串值的最小空间
        - left 表示左对齐输出
        - right 表示右对齐输出，右对齐是默认格式
        - internal 控制负数的符号位置，左对齐符号，右对齐值，用空格填满所有中间空间
        - setfill 允许指定一个字符代替默认的空格来补白输出
- 控制输入格式
    - 操作符 noskipws 会令输入运算符读取空白符，而不是跳过它们
    - skipws 恢复默认行为

### 17.5.2 未格式化的输入/输出操作
标准库还提供了一组低层操作，支持未格式化 IO ，这些操作允许我们将一个流当作一个无解释的字节序列来处理

- 单字节操作
    - 有几个未格式化操作每次一个字节地处理流，会读取而不是忽略空白符
    - 单字节低层 IO 操作
        - `is.get(ch)` 从 istream is 读取下一个字节存入字符 ch 中，返回 is
        - `os.put(ch)` 将字符 ch 输出到 ostream os，返回 os
        - `is.get()` 将 is 地下一个字节作为 int 返回
        - `is.putback(ch)` 将字符 ch 放回 is，返回 is
        - `is.unget()` 将 is 向后移动一个字节，返回 is
        - `is.peek()` 将下一个字节作为 int 返回，但不从流中删除它
- 将字符放回输入流
    - 标准库提供了三种方法退回字符，有着细微地差别
        - `peak` 返回输入流中下一个字符地副本，但不会将它从流中删除，`peek` 返回的值仍然留在流中
        - `unget` 使得输入流向后移动，从而最后读取的值又回到流中，即使我们不知道最后从流中读取到什么值，仍然可以调用 unget
        - `putback` 是更特殊版本的 `unget`，退回从流中读取的最后一个值，但它接受一个参数，此参数必须与最后读取的值相同
    - 一般情况下，在读取下一个值之前，标准库保证我们可以退回最多一个值，即标准库不保证在中间不进行读取操作的情况下能连续调用 `putback` 或 `unget`
- 从输入操作返回的 int 值
    - 函数 peek 和无参的 get 版本都以 int 类型从输入流返回一个字符
        - 原因是可以返回文件尾标记
    - 返回 int 的函数将它们要返回的字符先转换为 unsigned char 然后再将结果提升到 int，即使又负值，返回的 int 也是正值
    - 标准库使用负值表示文件尾，可以保证与任何合法字符的值都不同
    - 头文件 cstdio 定义了一个名为 EOF 的 const，可以用来检测从 get 返回的值是否是文件尾
        ```cpp
        int ch;
        while ((ch = cin.get()) != EOF)
            cout.put(ch);
        ```
- 多字节操作
    - 一些未格式化 IO 操作一次处理大块数据
    ![多层次低层 IO 操作](sources/17_5_2_1.png)
    - get和 getline 函数接受相同的参数，他们的行为类似但不相同，在两个函数中，sink 都是一个 char 数组，用来保存数据。
    - 两个函数都一致读取数据，直至下面条件之一发生
        - 已读取了 size-1 个字符
        - 遇到了文件尾
        - 遇到了分隔符
    - 处理分隔符的方式butong
        - get 将分割符流作 istream 中的下一个字符
        - getline 读取并丢弃分隔符
    - 一个常见的错误是本想从流中删除分割符，却忘了做
- 确定读取了多少个字符
    - 可以调用 gcount 来确定最后一个未格式化输入操作读取了多少个字符，应该在任何后续未格式化输入操作之前调用 gcount
    - 如果在调用 gcount 之前调用了 peek unget putback 则gcount 返回值为 0


### 17.5.3 流随机访问
各种流类型通常都支持对流中数据的随机访问，可以重定位流，使之跳过一些数据  
标准库提供了一堆函数，来定位(seek)到流中给定的位置，以及(tell)我们当前的位置  
随机 IO 本质上是依赖于系统的，为了理解如何使用这种特性，必须查询系统文档  
虽然标准库为所有类型的流都定义了 seek 和 tell 函数，但它们是否会做有意义的事请依赖于流绑定到哪个设备，在大多数系统中，绑定到 cin cout cerr 和 clog 的流不支持随机访问  

由于 istream 和 ostream 类型通常不支持随机访问，所以本节剩余内容只适用于 fstream 和 sstream 类型

- seek 和 tell 函数
    - IO 类型维护一个标记来确定下一个读写操作要在哪里进行
    - 提供两个函数
        - 通过将标记 seek 到一个给定位置来重定位它
        - tell 告知当前标记位置
    - g 版本对应读取
    - p 版本对应写入
- 只有一个标记
    - 在单一流中只维护单一标记，并不存在独立的读标记和写标记
    - 在可读写的流中，标准库将 g 和 p 版本的读写位置都映射到这个单一的标记
    - 由于只有单一的标记，因此只要我们在读写操作间切换，就必须进行 seek 操作来重定位标记
- 重定位标记
    - seek 函数两个版本
        - 一个移动到文件中的绝对地址  `seek(new_position);` 
        - 一个移动到一个给定位置的指定偏移量  `seek(offset, from);`
        - 参数 new_positon 和 offset 的类型分别是 pos_type 和 off_type
- 访问标记
    - 函数 tellg 和 tellp 返回一个 pos_type 值，表示流的当前位置
    - tell 函数通常用来记住一个位置，以便移后在定位回来
        ```cpp
        ostringstream writeStr;
        ostringstream::pos_type mark = writeStr.tellp();
        if (cancelEntry)
            writeStr.seekp(mark);
        ```
- 读写同一个文件
    - 给定一个要读取的文件，在此文件的末尾写入新的一行，这一行包含文件中每行的相对起始位置
    ```cpp
    int main(){
        fstream inOut ("copyOut", fstream::ate | fstream::in | fstream::out);
        if (!inOut) {
            cerr << "Unable to open file!" << endl;
            return EXIT_FALLURE;
        }
        auto end_mark = inOut.tellg();
        inOut.seekg(0, fstream::beg);
        size_t cnt = 0;
        string line;
        while (inOut && inOut.tellg() != end_mark && getline(inOut,line)){
            cnt += line.size() + 1;
            auto mark = inOut.tellg();
            inOut.seekp(0,fstream::end);
            inOut << cnt;
            if (mark != end_mark) inOut << " ";
            inOut.seekg(mark);
        }
        inOut.seekp(0, fstream::end);
        inOut << '\n';
        return 0;
    }
    ```
    - in out 指出想读写同一个文件，ate 会将读写标记定位到文件尾
    - 将原文件尾标记在 end_mark 中


# 18 用于大型程序的工具


## 18.1 异常处理
异常处理机制允许程序中独立开发的部分能够在运行时就出现的问题进行同行并作出对应的处理  
异常使得我们能够将问题的检测与解决过程分离开来，程序的一部分负责检测问题的出现，然后解决该问题的任务传递给程序的另一部分

### 18.1.1 抛出异常
通过抛出一条表达式来引发一个异常，被抛出的表达式的类型以及当前的调用链共同决定了那段处理代码将被用来处理该异常  
被选中的处理代码是在调用链中与抛出对象类型匹配的最近的处理代码  
当执行一个 throw 时，跟在 throw 后面的语句将不再被执行，程序的控制权从 throw 转移到与之匹配的 catch 模块  
- 控制权从一处转移到另一处
    - 沿着调用链的函数可能会提早退出
    - 一旦程序开始执行异常处理代码，则沿着调用链创建的对象将被销毁
- 栈展开
    - 当抛出一个异常后，程序暂停当前函数的执行过程并立即开始寻找与异常匹配的 catch 子句，如果找到了匹配的 catch ，就使用该 catch 处理异常，否则像上层继续查找
    - 栈展开过程沿着嵌套函数的调用链不断查找，直到找到了异常匹配的 catch 子句为止，或者可能一直没找到匹配的 catch ，则退出主函数后查找过程终止
    - 如果没找到匹配的 catch 子句，程序将退出，因为异常通常被认为是妨碍程序正常执行的事件，所以一旦引发了某个异常，当找不到匹配的 catch 时，程序将调用标准库函数 terminate，terminate 负责终止程序的执行过程
    - 一个异常如果没有被捕获，则它将终止当前程序
- 栈展开的过程中对象被自动销毁
    - 在栈展开过程中，位于调用链上的语句块可能会提前退出
    - 通常情况下，程序在这些块中创建了一些局部条件
- 析构函数与异常
    - 析构函数总是会被执行，但是函数中负责释放资源的代码却可能被跳过，这一特点对于我们如何组织程序结构有重要影响， 如果一个块分配了资源，并且在负责释放这些资源的代码前面，则释放资源的代码将不会被执行
    - 在栈展开的过程中，运行类型的局部对象的析构函数，因为这些析构函数是自动执行的，所以它们不应该抛出异常，一旦在栈展开的过程中析构函数抛出了异常，并且析构函数自身没能不哦到该异常，则程序将被终止
- 异常对象
    - 编译器使用异常抛出表达式来对异常对象进行拷贝初始化
    - 异常对象位于编译器管理的空间中，编译器确保无论最终调用的是哪个 catch 子句都能访问该空间，当异常处理完毕后，异常对象被销毁
    - 抛出指针要求在任何对应的处理代码存在的地方，指针所指的对象都必须存在

### 18.1.2 捕获异常
catch 子句中的异常声明看起来像是只包含一个形参的函数形参列表，像在形参列表中一样，如果 catch 无须访问抛出的表达式，可以忽略捕获形参的名字  
声明的类型决定了处理代码所能捕获的异常类型，这个类型必须是完全类型，可以是左值引用，但不能是右值引用  
- 通过异常对象初始化异常声明中的参数
    - 如果 catch 的参数类型是非引用类型，则该参数是异常对象的一个副本，在 catch 语句内改变该参数实际上改变的是局部副本而非异常对象本身
    - 如果参数是引用类型，则和其他引用参数一样，该参数是异常对象的一个别名，此时改变参数也就是改变异常对象
    - 如果 catch 的参数是基类类型，则可以使用其派生类类型的异常对象对其进行初始化
        - 此时如果 catch 的参数是非引用类型，则异常对象将被切掉一部分，这与将派生类对象以值传递的方式传给一个普通函数差不多
        - 如果 catch 的参数是基类的引用，则该参数将以常规方式绑定到异常对象上
- 如果 catch 接受的异常与某个继承体系有关，则最好将该 catch 的参数定义成引用类型

- 查找匹配的处理代码
    - 在搜寻 catch 语句的过程中，最终找到的 catch 未必是异常的最佳匹配，相反，挑选出来的应该是第一个与异常撇皮的 catch 语句，因此，专门的 catch 应该置于整个 catch 列表的前端
    - 异常和 catch 的匹配规则有更多限制
        - 允许从非常量向常量的类型转化，一条非常量对象的 throw 语句可以匹配一个接受常量引用的 catch 语句
        - 允许从派生类向基类的类型转换
        - 数组被转换成指向数组元素类型的指针，函数被转换成指向该函数类型的指针
        - 除此之外包括标准算术类型转换和类类型转换其他所有转换规则都不能在匹配 catch 的过程中使用
    - 如果在多个 catch 语句的类型之间存在继承关系，则我们应该把继承链最底端的类放在前面，而将继承链最顶端的类放在后面
- 重新抛出
    - 一个单独的 catch 语句不能完整的处理某个异常，在执行了某些矫正操作之后，当前的catch 可能会决定由调用链更上层的函数处理异常  一条 catch 语句通过重新抛出的操作将异常传递给另外一个 catch 语句  此时重新抛出一个 throw 语句不包含任何表达式
    - 空的 throw 语句只能出现在 catch 语句或 catch 语句直接或间接调用的函数之内，如果在处理代码之外的区域遇到了空 throw 语句，编译器将调用 terminate  
    - 一个重现抛出语句并不指定新的表达式，而是将当前的异常对象沿着调用链向上传递
- 捕获所有异常的处理代码
    - 为了一次性捕获所有异常，使用省略号作为异常声明，这样代码陈伟捕获所有异常
    - catch(...) 通常与重现抛出语句一起使用，其中 catch 执行当前局部能完成的工作，随后重新抛出异常
    - 如果 catch(...) 与其他几个 catch 语句一起出现，则 catch(...) 必须在最后的位置，出现在捕获所有一场语句后面的 catch 语句将永远不会被压缩


### 18.1.3 函数 try 语句块与构造函数
通常情况下，程序执行的任何时刻都可能发生异常，特别是异常可能发生在处理构造函数初始值的过程中  
构造函数在进入其函数体之前首先执行初始值列表，处理构造函数初始值抛出的异常必须将高槽函数写成函数 try 语句块  
把 Blob 的构造函数置于一个函数 try 语句块中
```cpp
template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) try : data (std::make_shared<std::vector<T>>(il)){

} catch(const std::bad_alloc &e) { handle_out_of_memory(e);}
```
处理构造函数初始值异常的唯一方法是将构造函数携程函数 try 语句块


### 18.1.4 noexcept 异常说明
C++ 11 中，可以通过 noexcept 说明指定某个函数不会抛出异常  
形式为 noexcept 紧跟在函数的参数列表后，用以表示该函数不会抛出异常  
对于一个函数来说，noexcept 说明要么出现在该函数的所有声明语句和定义语句中，要么依次也不出现，该说明应该在函数的尾置返回类型之前  
在成员函数中，noexcept 说明符需要在 const 及引用限定符之后，而在 final、ovvride 或虚函数 =0 之前  
- 违反异常说明
    - 一旦一个 noexcept 函数抛出了异常，程序会调用 terminate 以确保遵守不在运行时抛出异常的承诺
    - 通常情况下，编译器不能也不必再编译时验证异常说明
- 异常说明的实参
    - noexcept 说明符接受一个可选的实参，该实参必须能转换为 bool 类型，如果实参是 true，则函数不会抛出异常，如果实参是 false，则函数可能抛出异常
- noexcept 运算符
    - noexcept 说明符的实参常常与 noexcept 运算符混合使用
    - noexcept(e)
        - 当 e 调用的所有函数都做了不抛出说明且 e 本身不含有 throw 语句时，上述表达式为 ture，否则返回 false
    - 嵌套使用异常说明符  `void f() noexcept(noexcept(g()))`  如果 g 承诺了不会抛出异常，那 f 也不会抛出异常，如果 g 没有异常说明符，或者 g 虽然有异常说明符但允许抛出异常，则 f 也可能抛出异常
- 异常说明与指针、虚函数和拷贝控制
    - 尽管 noexcept 说明符不属于函数类型的一部分，但是函数的异常说明仍然会影响函数的使用
    - 函数指针及该指针所指的函数必须具有一致的异常说明，如果我们为某个指针做了不抛出异常说明，则该指针只能指向不抛出异常的函数，即使是承诺了不抛出异常的函数也可以
    - 如果一个虚函数承诺了它不会抛出异常，则后续派生出来的虚函数也必须做出同样的承诺，与之相反，如果基类的虚函数允许抛出异常，则派生类的对应函数既可以允许抛出异常，也可以不允许抛出异常


### 18.1.5 异常类层次
标准 exception 类层次
![标准 exception 类层次](./sources/18_1_5_1.png)
- 类型 exception 仅仅定义了拷贝构造函数，拷贝赋值运算符，一个虚析构函数和一个名为 what 的虚成员
- what 函数返回一个 const char*，该指针指向一个以 unll 结尾的字符数组，以确保不会抛出异常
- 类 exception、bat_cast 和 bad_alloc 定义了默认构造函数
- 类 runtime_error 和 logic_error 没有默认构造函数，但是有一个可以接受 C 风格字符串或者标准库 string 类型实参的构造函数
- 书店应用程序的异常类
    ```cpp
    class out_of_stock: public std::runtime_error {
    public:
        explicit out_of_stock(const std::string &s): std::runtime_error(s){ }
    };
    class isbn_mismatch: public std::logic_error {
    public:
        explicit isbn_mismatch(const std::string &s): std::logic_error(s) { }
        isbn_mismatch(const std::string &lhs, const std::string &rhs):
            std::logic_error(s), left(lhs), right(rhs) { }
        const std::string left, right;
    };
    ```
- 使用我们自己的异常类型
    - 当使用自定义异常类的方式与使用标准异常类的方式完全相同
    - 程序在某处抛出异常类型的对象，在灵位的地方捕获并处理这些出现的问题


## 18.2
多个库将名字放置在全局命名空间中将引发命名空间污染  
命名空间为防止名字冲突提供了更加可控的机制，命名空间分割了全局命名空间，其中每个命名空间就是一个作用域，通过再某个命名空间中定义库的名字，哭的作者以及用户可以避免全局名字固有的限制

### 18.2.1 命名空间定义
一个命名空间的定义包含两部分：首先是关键字 namespace，随后是命名空间的名字  
在命名空间名字后面是一系列由花括号括起来的声明和定义，只要能出现在全局作用域的声明就能治愈命名空间内  
主要包括：类、变量（及其初始化操作）、函数（及其定义）、模板和其他命名空间  
命名空间既可以定于i在全局作用域中，也可以定义在其他命名空间中，但是不能定义在函数或类的内部  
命名空间作用域后面无须分号  
- 每个命名空间都是一个作用域
    - 和其他作用于类似，命名空间中的每个名字都必须表示该空间中的唯一实体，因为不同命名空间的作用域不同，所以在不同命名空间内可以有相同名字的成员
    - 定义在某个命名空间中的名字可以被该命名空间内的其他成员直接访问，也可以被这些成员内嵌作用域中的任何单位访问，位于该命名空间之外的代码则必须明确指出所用的名字属于哪个命名空间
- 命名空间可以是不连续的
    - 命名空间的组织方式类似于我们将几个独立的接口和实现文件组成一个命名空间，此时，命名空间的组织方式类似于我们管理自定义类及函数的方式
        - 命名空间的一部分成员的作用是定义类，以及声明作为类接口的函数及对象，则这些成员应该置于头文件中，这些头文件将被包含在使用了这些成员的文件中
        - 命名空间的定义部分则置于另外的源文件中
    - 定义多个类型不相关的命名空间应该使用单独的文件分别表示每个类型（或关联类型构成的集合）
- 定义本书的命名空间
    - 通常不把 #include 放在命名空间内部
- 定义命名空间成员
    - 假定作用域中存在合适的声明语句，则命名空间中的代码可以使用同一命名空间定义的名字的简写形式
    - 在命名空间的内部，可以直接使用该命名空间的其他成员
- 模板特例化
    - 模板特例化必须定义在原始模板所属的命名空间中，只要我们在命名空间中声明了特列化，就能在命名空间外部定义
    ```cpp
    namespace std { template <> struct hash<Sales_data>;}
    template <> struct std::hash<Sales_data>{
        size_t operator()(const Sales_data& s) const{
            return hash<string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^
                    hash<double>()(s.revenue);
        }
    };
    ```
- 全局命名空间
    - 全局作用域中定义的名字（即在所有类、函数及命名空间之外定义的名字）也就是定义在全局命名空间中，全局名空间以隐式的方式声明，并且在所有程序中都存在，全局作用域中定义的名字被隐式地田间道全局命名空间中
- 嵌套的命名空间
    - 定义在其他命名空间中的命名空间
    - 内层命名空间声明的名字将隐藏外层命名空间声明的同名成员，在嵌套的命名空间中定义的名字只在内层命名空间中有效，外层命名空间中的代码要想访问它必须在名字前添加限定符
- 内联命名空间
    - C++11 新标准引入了一种新的嵌套命名空间称为内联命名空间，内联命名空间中的名字可以被外层命名空间直接使用
    - 在 namespace 前添加关键字 inline
    - 关键字 inline 必须出现在命名空间第一次定义的地方，后续再打开命名空间的时候可以写 inline，也可以不写
- 未命名的命名空间
    - 未命名的命名空间是指关键字 namespace 后紧跟花括号括起来的一系列声明语句
    - 其中变量拥有静态生命周期，在第一次使用前创建，知道程序结束被销毁
    - 可以在某个给定的文件内不连续，但是不能横跨多个文件，每个文件定义自己的命名空间的未命名空间
    - 未命名的命名空间中的成员可以通过外层命名空间的名字来访问


### 18.2.2 使用命名空间成员
- 命名空间的别名
    - 命名空间的别名使得我们可以为命名空间的名字设定一个短得多的同义词  
    - 不能在命名空间还没有定义前就声明别名，否则将产生错误
    - 可以指向一个嵌套的命名空间
    - 一个命名空间可以有好几个同义词或别名，所有别名都与命名空间原来的名字等价
- using 声明: 扼要概述
    - 一条 using 声明语句一次只能引入一个成员
    - using 声明引入的名字遵守与过去一样的作用域规则，有效范围从 using 声明的地方开始，一直到 using 声明所在的作用域结束
    - 一条 using 声明语句可以出现在全局作用域、局部作用域、命名空间作用域以及类的作用域，在类的作用域中，这样的声明语句只能指向基类成员
- using 指示
    - using 指示 无法控制哪些名字是可见的，因为所有名字都是可见的
    - using 指示以关键字 using 开始，后面是关键字 namespace 以及命名空间的名字
    - 可以出现在全局作用域，局部作用域和命名空间作用域中，不能出现在类作用域中
    - using 指示使得某个特定的命名空间中所有的名字都可见，无须再为它们添加任何前缀限定符，简写的名字从 using 开始，一直到 using 指示所在的作用域结束都能使用
    - 如果提供了一个对 std 等命名空间的 using 指示而为做任何特殊控制的话，将重新引入由于使用了多个库而造成的名字冲突问题
- using 指示与作用域
    - using 指示引入的名字的作用域远比 using 声明引入的名字的作用域复杂
    - using 指示一般被看作是出现在最近的外层作用域中
        ```cpp
        namespace A {
            int i, j;
        }
        void f(){
            using namespace A;
            cout << i* j << endl;
        }
        ```
    - using 指示实例
        ```cpp
        namespace blip {
            int i = 16, j = 15, k = 23;
        }
        int j = 0;
        void mainp(){
            using namespace blip;
            ++i; // blip::i = 17
            ++j; // 二义性错误
            ++::j; // 全局 j 指定为 1
            ++blip::j; // blip::j = 16
            int k = 97; // 当前局部隐藏了 blip::k
            ++K; //当前局部 k 设定为 98
        }
        ```
- 头文件与 using 声明或指示
    - 头文件如果在再其顶层作用域中含有 using 指示或 using 声明，则会将名字注入到所有包含了该头文件的文件中
    - 通常情况下，头文件应该只负责定义接口部分的名字，而不定义实现部分的名字
    - 头文件最多之能在它的函数或命名空间中使用 using 指示或 using 声明

### 18.2.3 类、命名空间与作用域
对命名空间内部名字的查找遵循常规的查找规则：即由内向外依次查找每个外层作用域  
外层作用域也可能是一个或多个嵌套的命名空间，直到最外层的全局命名空间查找过程终止，只有位于开放的块中且在使用点之前声明的名字才被考虑  
对于命名空间中的类来说，常规的查找规则仍然适用  
当成员函数使用某个名字时，首先在该成员中进行查找，接着在外层作用域中查找，这时一个或几个外层作用域可能就是命名空间 
可以从函数的限定名推断出查找名字时检查作用域的次序，限定名以相反次序指出被查找的作用域  
- 实参相关的查找与类类型形参
    - 当我们给函数传递一个类类型对象时，除了在常规的作用域查找外还会查找实参类所属的命名空间  
    - 查找规则的这个例外允许概念上作为类接口一部分的非成员函数无须单独的 using 声明
- 查找与 std::move 和 std::forward
    - 接受一个右值引用的函数形参，右值引用形参可以匹配任何类型
    - 如果程序定义了一个接受单一形参的 move 函数，则不管该形参是什么类型，应用程序的 move 函数都将与标准库的版本冲突
    - 建议书写 std::move 明确使用标准库的版本
- 友元声明与实参相关的查找
    - 当类声明了一个友元时，该友元声明并没有使得友元本身可见，然而一个另外的未声明的类或函数如果第一次出现在友元声明，则我们认为它是最近的外层命名空间的成员
    ```cpp
    namespace A {
        class C {
            // 这些函数隐式的称为命名空间 A 的成员
            friend void f2(); //除非另有声明，否则不会被找到
            friend void f(const C&); //根据实参相关的查找规则可以被找到
        };
    }
    int main(){
        A::C cobj:
        f(cobj); //correct
        f2(); //incorrect A::f2 没有被声明
    }
    ```

### 18.2.4 重载与命名空间
- 命名空间对函数的匹配过程有两方面的影响
    - using 声明或 using 指示能将某些函数添加到候选函数集

- 与实参相关的查找与重载
    - 对于接受类类型实参的函数来说，其名字查找将在实参类所属的命名空间中进行
    - 将在每个实参类(以及实参类的基类)所属的命名空间中搜寻函数
- 重载与 using 声明
    - using 声明语句声明的是一个名字，而非一个特定的函数
    - 当为函数书写 using 声明时，该函数的所有版本都被引入到当前作用域中
    - 一个 using 声明引入的函数将重载该声明语句所属作用域中已有的其他同名函数，如果 using 声明出现在局部作用域中，则引入的名字将隐藏外层作用域的相关声明
    - 如果 using 声明所在的作用域中已经有一个函数与新引入的函数同名且形参列表相同，则该 using 声明将引发错误
- 重载与 using 指示
    - using 指示将命名空间的成员提升到外层作用域，如果命名空间中的某个函数与该命名空间所属作用域的函数同名，则命名空间的函数将被添加到重载集合中
    - 对于 using 指示来说，引入一个与已有函数形参列表完全相同的函数并不会产生错误
- 跨域多个 using 指示的重载
    - 如果存在多个 using 指示，则来自每个命名空间的名字都会成为候选函数集的一部分

## 18.3 多重继承与虚继承
多重继承是指从多个直接基类中产生派生类的能力，多重继承的派生类继承了所有父类的属性

### 18.3.1 多重继承
在派生类的派生列表中可以包含多个基类  
每个基类包含一个可选的访问说明符，如果访问说明符被忽略掉了，则关键字 class 对应的说明符是 private，关键字 struct 对应的是 public  
多重继承的派生列表也只能包含已经被定义过的类，而且这些类不能是 final 的  
对于派生类能够继承的基类个数，没有特殊规定  
- 多重继承的派生类从每个基类中继承状态
    - 在多重继承关系中，派生类的对象包含有每个基类的子对象
- 派生类构造函数初始化所有基类
    - 构造一个派生类将同时构造并初始化它的所有基类子对象，与从一个基类进行派生一样
    - 多重继承的派生类的构造函数初始值也只能初始化它的直接基类
    - 其中基类的构造顺序与派生列表中基类的出现顺序保持一致，而与派生类构造函数初始值列表中积累的顺序无关
- 继承的构造函数与多重继承
    - 允许派生类从它的一个或几个基类中继承构造函数
    - 如果一个类从它的多个基类中继承了相同的构造函数，则这个类必须为构造函数定义它自己的版本
    ```cpp
    struct Base1 {
        Base1() = default;
        Base1(const std::string&);
        Base1(std::shared_ptr<int>);
    };
    struct Base2 {
        Base2() = default;
        Base2(const std::string&);
        Base2(int);
    };
    struct D1: public Base1, public Base2 {
        using Base1::Base1;
        using Base2::Base2;
    };
    struct D2: public Base1, public Base2 {
        using Base1::Base1; //从 Base1 继承构造函数
        using Bsee2::Base2; //从 Base2 继承构造函数
        // D2 必须自定义一个接受 string 的构造函数
        D2(const string &s): Base1(s), Base2(s) {}
        D2() = default; //一旦D2定义了它自己的构造函数
    };
    ```
- 析构函数与多重继承
    - 和往常一样，派生类的析构函数只负责清楚派生类本身分配的资源，派生类的成员及基类都是自动销毁的
    - 合成的析构函数体为空
- 多重继承的派生类的拷贝与移动操作
    - 多重继承的派生类如果定义了自己的拷贝/赋值构造函数和赋值运算符。则必须在完整的对象上执行拷贝、移动、或赋值操作
    - 只有当派生类使用的是合成版本的拷贝、移动或赋值成员时，才会自动对其基类部分执行这些操作

### 18.3.2 类型转换与多个基类
在只有一个基类的情况下，派生类的指针或引用能自动转换成一个可访问积累的指针或引用  
可以令某个可访问基类的指针或引用直接指向一个派生类对象  

- 基于指针类型或引用类型的查找
    - 对象，指针和引用的静态类型决定了我们能够使用哪些成员


### 18.3.3 多重继承下的类作用域
在只有一个基类的情况下，派生类的作用域嵌套在直接基类和简介基类的作用域中，查找过程沿着继承体系自低向上进行，知道找到所需的名字，派生类的名字将隐藏基类的同名成员  
在多重继承的情况下，相同的查找过程在所有直接基类中同时进行，如果名字在多个基类中都被找到，则对该名字的使用将具有二义性  
当一个类拥有多个基类时，有可能出现派生类从两个或更多基类中继承了同名成员的情况，此时，不加前缀限定符直接使用该成员将引发二义性

### 18.3.4 虚继承
派生列表中同一个基类只能出现一次，但实际上派生类可以多次继承同一个类，派生类可以通过它的直接基类分别继承同一个间接基类，也可以直接继承某个基类，然后通过另一个基类再一次间接继承该类  
在默认情况下，派生类中含有继承链上每个类对应的子部分，如果某个类在派生过程中出现了多次，则派生类中将包含该类的多个子对象  
在 C++ 中通过虚继承的机制解决上述问题，虚继承的目的是令某个类做出声明，承诺愿意共享它的基类，其中，共享的基类子对象称为虚基类  
这种机制下，无论虚积累出现多少次，在派生类中都只包含唯一一个共享的虚基类子对象  
- 另一个 Panda 类
    - 虚派生只影响从指定了虚基类的派生类中进一步派生出的类，它不会影响派生类本身
- 使用虚基类
    - 指定虚基类的方式是在派生列表中添加关键字 virtual
    - virtual 说明符表明了一种愿望，即在后续的派生类当中共享虚基类的同一份实例，什么样的类能够作为虚基类并没有特殊规定
- 支持向基类的常规类型转换
    - 无论基类是不是虚基类，派生类对象都能被可访问积累的指针或引用操作
    ```cpp
    void dance(const Bear&);
    void rummage(const Raccoon&);
    ostream& operator<<(ostream&, const ZooAnimal&);
    Panda ying_yang;
    dance(ying_yang); // 把一个 Panda 对象当成 Bear 传递
    rummage(ying_yang); // 把一个 Panda 对象当成 Raccoon 传递
    cout << ying_yang; // 把一个 Panda 对象当成 ZooAnimal 传递
    ```
- 虚基类成员的可见性
    - 在每个共享的虚基类中只有唯一一个共享的子对象，所以该基类的成员可以被直接访问，并且不会产生二义性
    - 如果虚基类的成员只被一条派生路径覆盖，则我们仍然可以直接访问这个被覆盖的成员，但是如果成员被多余一个基类覆盖，则一般情况下派生类必须为该成员自定义一个新的版本
    - 假定类 B 定义了一个名为 x 的成员，D1 和 D2 都是从 B 虚继承得到的，D 继承了 D1 和 D2，则在 D 的作用域中，x 通过 D 的两个基类都是可见的，如果我们通过 D 的对象使用 x，有三种可能性
        - 如果在 D1 和 D2 中都没有 x 的定义，则 x 将被解析为 B 的成员，此时不粗壮乃二义性，一个 D 的对象只含有 x 的一个实例
        - 如果 x 是 B 的成员，同时是 D1 和 D2 中某一个的成员，则同样没有二义性，派生类的 x 比虚基类 B 的 x 优先级更高
        - 如果在 D1 和 D2 中都有 x 的定义，则直接访问 x 将产生二义性问题
    - 解决此问题最好的办法是在派生类中为成员自定义新的实例

### 18.3.5 构造函数与虚继承
在虚派生中，虚基类是由最底层的派生类初始化的  
继承体系中的每个类都可能在某个时刻成为最底层的派生类  
只要我们能创建虚基类的派生类对象，该派生类的狗i早函数就必须初始化它的虚基类
- 虚继承的对象的构造方式
    - 首先使用提供给最低层派生类构造函数的初始值初始化该对象的虚基类子部分
    - 接下来按照基类在派生列表中出现的次序依次对其进行初始化
    - 虚基类总是先于非虚基类构造，与他们在继承体系中的次序和位置无关
- 析构函数与析构函数的次序
    - 一个类可以有多个虚基类，这些虚的子对象按照他们在派生列表中出现的顺序从左向右一次构造