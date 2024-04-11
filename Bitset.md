## Design 1  Bitset
---
### constructor 
#### 创建与初始化

* 提供默认,通过`unsigned long long`,字符串构造共三种构造函数
    * 默认构造函数将会创建一个空的 bitset
    * `ULL`构造函数,将会将高位0作为数据存储
    * 字符串构造函数通过字符串创建一个`bitset`,其中的所有`zero`字符会被视作0,所有`one`字符会被视作1出现非法字符(包括`\0`!)会抛出`invalid_arguments`,当传入字符串长度与参数`n`不符合时,会抛出`wrong_length`,避免意外的数据丢失

* 提供析构函数,可以释放分配在堆上的资源

#### 运算符与函数
* 提供了以下函数
    * `test()`:返回p位置的比特
    `bool BitSet::bits::test(size_t p)`

    * `count()`:返回所有比特中 1 的个数
    `size_t BitSet::bits::count()`

    * `size()`:返回总共占用的内存大小(Byte),包括对象本身和动态分配的内存
    `size_t BitSet::bits::size()`

    *  `all()`: 返回是否所有位置均为1
    `bool BitSet::bits::all()`

    * `any()`:返回是否存在位置为1
    `bool BitSet::bits::any()`

    * `none`: 返回是否全为0
    `bool BitSet::bits::none()`

    * `filp()`反转函数
        * `BitSet::bits &BitSet::bits::filp()`: 将所有bit反转,返回得到bits的引用
        * `BitSet::bits &BitSet::bits::filp(size_t p)`: 将位置p的比特反转,返回得到的bits的引用
    * `set`与`reset`置位与复位函数
        * `BitSet::bits &BitSet::bits::set()`:将所有比特设为1,返回得到的bits的引用
        * `BitSet::bits &BitSet::bits::reset()`:将所有比特设为0,返回得到的bits的引用
    * `compare`:比较两个相同长度的bits是否相同,数位不同时会抛出`different_size`
    `BitSet::bits::compare(const BitSet::bits &y)`
所有涉及位置的函数均存在位置检查,如果访问/修改位置超界,会抛出`beyond`
* 重载了`[]`运算符,功能相当于`test()`,也有超界检查