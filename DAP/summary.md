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