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
