# DEBUG中出现的问题
---
## 1.**segmentation fault**
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
<font color=blue size=4>SOLUTION:</font>

    动态内存分配，这样开辟的是空间充裕的堆内存，而不是仅有几个M的栈内存

本次我们遇到的问题是在解决[不好办的最长上升子序列](super_LIS/super_LIS.cpp)时，由于结构体Node数组占用栈内存过大，导致的异常，因此改为堆内存动态分配，解决了问题。

