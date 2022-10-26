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