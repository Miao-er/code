# 堆栈基本操作

**总时间限制: 1000ms 内存限制: 65535kB**
## 描述
>依次读入序列元素1,2,...,n进栈，每进一个元素，机器可要求下一个元素进栈或弹栈，如此进行。给定一个输入序列，判断栈空时弹出的元素构成的序列是否可能等于给定的序列，如果是则输出栈的操作过程，否则输出“NO”。

## 输入
>输入分两行
>第一行为n的值（即序列元素个数）
>第二行为给定的输入序列（序列元素均为整型）
## 输出
>如果输入序列能够由题目规定的操作得到，则输出对栈的操作过程
>否则直接输出“NO”
## 样例输入
>7
>4 5 3 6 2 7 1
## 样例输出
>PUSH 1
>PUSH 2
>PUSH 3
>PUSH 4
>POP 4
>PUSH 5
>POP 5
>POP 3
>PUSH 6
>POP 6
>POP 2
>PUSH 7
>POP 7
>POP 1
### 提示
>给定序列中有可能有不在1...n之间的数字