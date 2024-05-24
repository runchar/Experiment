## UINT

### 功能

- 多种类型的初始化与转换
- 基本的'+','-','*','/','%'运算
  * 除法的实现是带余除法 
- 从十进制字符串的流式输入输出

### 一些特性

- 处理流式输出,受限于操作数位置,只能将重载`<<`作为友元函数处理,但是声明为友元函数则
无法直接重写以实现多态,考虑使用虚成员函数`OstreamString`为流式输出提供字符串
通过重写`OstreamString`间接实现多态
- 相较于`const char *`使用了`std::string`,一方面后者功能更完备,二则`std::string`的转换比较灵活
使用`const char *`容易出现未定义行为

### 坑
- `const_iterator`

  实现加法的时候,为了安全考虑使用了`cbegin`作为迭代器开头进行遍历,但是出现了以下报错
```
message": "invalid conversion from 'const BitSet::bits<500>::storage_type*' {aka 'const long long unsigned int*'} to 'BitSet::bit_iterator<BitSet::bits<500>, true>::storage_pointer' {aka 'long long unsigned int*'} [-fpermissive]",
```
在
```cpp

        const_iterator make_iter(size_t p)const {
            return bit_iterator<bits<N>, true>(bitset + p / length, p % length);
        }
```
反复检查模板,is_const并没有错,后来发现:
```cpp
//      using storage_pointer = typename std::conditional_t<is_const, 
//      const typename origin::storage_pointer, typename origin::storage_pointer>;
        using storage_pointer = typename std::conditional_t<is_const,
		typename origin::const_storage_pointer, typename origin::storage_pointer>;

```
如果是注释那种写法就会上面那个错,原因是上一种写法编译器会认为这个指针本身是const的,而非指向const,将不能被转换为指向const内容的指针

这里需要注意的是`typename`关键字作用是告诉编译器后面接的是一个类型名而不是静态成员,所以前一种写法与`const origin::storage_pointer`
意义完全不同

附上git仓库修订号:`cd174cb63d5f7ef7d4ba253b1400b36768c56627`

- illegal instruction

在实现uint乘法过程中,运行程序时程序崩溃,显示错误为`illegal instruction`

首先尝试通过捕获异常确定错误,发现异常捕获失败,查询得知`illegal instruction`会直接终止程序
后经过逐步调试发现错误来自于以下代码(大概?)
```cpp
        uint operator +(const uint & y) const{
            uint tmp;
            auto it=tmp.begin();
            auto itx=this->cbegin();
            auto ity=y.cbegin();
            bool CarryBit=false;
            for(auto end=tmp.end();it!=end;it++,itx++,ity++)
            {
                bool val_x=static_cast<bool>(*itx);
                bool val_y=static_cast<bool>(*ity);
                (*it)=(bool)(val_x^val_y^CarryBit);
                CarryBit=(val_x&val_y)||(val_x&CarryBit)||(CarryBit&val_y);
            }
        }

```
在c++23版本下,上述代码没有编译错误,而且调试发现程序崩溃在这一行
```cpp
 for(auto end=tmp.end();it!=end;it++,itx++,ity++)
```
于是前后检查了很多遍运算符重载,迭代器,无果

最后瞪眼法发现一个明显的错误:

这个函数没有返回值!!!(加上return之后可以正常运行)

一般而言,声明有返回值的函数缺少返回值编译器会报错才对,但是这个错误却没有,猜测为未定义行为>_<

- `const char *`
```cpp
        x.to_number("dec");
        ...
        std::string to_number( const char *op ) const {
        if(op=="dec"){
			//
        }
        if(op=="bin"){
		    //
        }
        if(op=="hex"){
			//
        }   
} 
```
当时使用的是clion,调试时跳到了一大串汇编代码里,报的错意思与上一个相似,于是开始寻找是否遗漏返回值
,没有发现一遗漏,但是调试时发现,` if(op=="dec"){`没有进入选择,仔细看警告信息发现字面常量字符串
之间比较实际上是在比较地址,但是这是一个未定义行为,gcc,clang 等编译器会比较字符串而得出正确答案,而
msvc则不会,故错误,这也是之后选择std::string的原因
PS:当时还在奇怪为什么一样的代码前几天还好端端的(用的VScode),突然就崩了