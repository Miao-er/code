# DEBUG中出现的问题
---
## 1.Segmentation Fault
    段错误一般发生在递归导致的栈溢出或这数组溢出，还有就是if语句中可能出错，比如一个链表结构：
```C++
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
```
    在链表指针指向为空的时候，它就不可能存在val值，这时候，如果你的if中存在p->val就会出现段错误。
    动态内存分配，这样开辟的是空间充裕的堆内存，而不是仅有几个M的栈内存

>本次我们遇到的问题是在解决[不好办的最长上升子序列](DAP/super_LIS/super_LIS.cpp)时，由于结构体Node数组占用栈内存过大，导致的异常，因此改为堆内存动态分配，解决了问题。

## 2.openjudge-Runtime Error
    运行时错误一般出现在数组越界，数据存储结构未判断是否为空或溢出导致的非法访问异常，因此针对stl标准库，要善用empty函数，针对数组链表，要注意尾指针是否为null,以及下表是否超过数组长度

>本次我们遇到的问题是在解决[中缀表达式求值](DA/nifix_Expression/nifix_Expression.cpp)时，针对以下代码，没有考虑while循环中的pop操作会使oper栈为空的情况，导致读取top函数栈顶元素时出现错误:
```C++
    while(level(oper.top())>=level(a[0]))//错误在此处
    {
        char ch=oper.top();
        oper.pop();
        int n1=num.top();
        num.pop();
        int n2=num.top();
        num.pop();
        num.push(cacu(n1,n2,ch));
    }
```
>修改如下：
```C++
    while(!oper.empty()&&level(oper.top())>=level(a[0]))
    {
        char ch=oper.top();
        oper.pop();
        int n1=num.top();
        num.pop();
        int n2=num.top();
        num.pop();
        num.push(cacu(n1,n2,ch));
    }
```
## 3.Time Limited Exceed
    有时遇到TLE的问题，可能是因为某些式子重复计算，或者有些运算使用了更复杂更费时的形式，这时就需要考虑使用一些优化，例如输入输出函数改为scanf和printf，乘法除法使用位运算，某些多次用到的表达式赋值给一个变量，多次调用这个变量，比多次计算表达式更为省时等等。

>本次我们遇到的问题是在解决[求指定区间第k小的元素下标](DAP/k-th_Numver/k-th_Number.cpp)时，由于数据量过大而导致超时，按照上述途径修改后时间大减，因为递归过程包含了大量次数的上述运算。