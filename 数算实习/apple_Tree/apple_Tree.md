# Apple Tree

**总时间限制:  2000ms 内存限制: 65536kB**

## 描述

> There is an apple tree outside of kaka's house. Every autumn, a lot of apples will grow in the tree. Kaka likes apple very much, so he has been carefully nurturing the big apple tree.The tree has *N*forks which are connected by branches. Kaka numbers the forks by 1 to *N*and the root is always numbered by 1. Apples will grow on the forks and two apple won't grow on the same fork. kaka wants to know how many apples are there in a sub-tree, for his study of the produce ability of the apple tree.The trouble is that a new apple may grow on an empty fork some time and kaka may pick an apple from the tree for his dessert. Can you help kaka?![img](http://media.openjudge.cn/images/g3523/3321_1.gif)

## 输入

> The first line contains an integer *N* (*N* ≤ 100,000) , which is the number of the forks in the tree. The following *N* - 1 lines each contain two integers *u* and *v*, which means fork *u* and fork *v* are connected by a branch. The next line contains an integer *M* (*M* ≤ 100,000). The following *M* lines each contain a message which is either "**C *x***" which means the existence of the apple on fork *x* has been changed. i.e. if there is an apple on the fork, then Kaka pick it; otherwise a new apple has grown on the empty fork. or "**Q *x***" which means an inquiry for the number of apples in the sub-tree above the fork **x**, including the apple (if exists) on the fork x Note the tree is full of apples at the beginning

## 输出

> For every inquiry, output the correspond answer per line.

## 样例输入

> 3
> 	1 2
> 	1 3
> 	3
> 	Q 1
> 	C 2
> 	Q 1

## 样例输出

> 3
> 2