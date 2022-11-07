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