# 1:物质分解记录

**总时间限制: 60000ms 单个测试点时间限制: 6000ms 内存限制: 131064kB**
## 描述

>对 物质分解记录 的结构进行统计分析。
>例如：
>给出一份 物质分解记录。
```
Material_1
{
Material_2
{
Material_3
                Material_4
Material_5
                {
                Material_6
                Material_7
                }
                Material_8
}
Material_9
Material_10
}
Material_11
{
Material_l3
Material_7
Material_2
{
Material_3
                Material_4
Material_5
                {
             Material_6
             Material_7
                }
                Material_8
}
Material_13
}
```

>上述记录的含义是，Material_1分解为 Material_2、Material_9和Material_10，Material_2又分解为Material_3、Material_4、Material_5和Material_8。以此类推，大括号外书写特定物质名称，括号内表示此特定物质分解出来的子物质名称，每个子物质还可再分解。

>现输入一个物质名称R，要求输出所有和物质R在记录中属于同一层次且位置在R之后的物质名称。
>比如R=“Material_1” ，则应该输出“Material_11”；
>比如R=“Material_9” ，则应该输出“Material_10”
>如果R在代码中出现了多次，则以其第一次出现为准，即仅输出与第一次出现的R属于同一层次且位置在R之后的语句内容。
>比如R=“Material_2” ，则应该输出
```
        Material_9
Material_10
```

## 输入
>输入包含多组数据。第一行是物质分解记录的份数，仅用一个整数表示。从第二行开始，每组数据包括 物质分解记录 和 所需查找的物质R 两部分，物质分解记录样式如描述中所示，R的内容和物质分解记录之间有一行空行，下一份记录与上一个R之间有两行空行。
>若输入！则表示输入结束。
>为简单起见，物质分解记录中每一行的内容为“{”或者“}”或者一个物质名称，不会有其他情况（比如空行）出现。同时每行文字前不会有任何缩进。物质名称是英文字母、数字和下划线组成的字符串。

## 输出
>对每组数据输出一行，如果R在记录中找到，则输出所有与R在同一层次且位置在R之后的物质名称，名称之间无需添加空格，紧密连接即可；否则输出No。若R是其所在层次中最后一个物质，则输出"",即输出一个空字符。

## 样例输入
```
3
Material_1
{
Material_2
{
Material_3
Material_4
Material_5
{
Material_6
Material_7
}
Material_8
}
Material_9
Material_10
}

Material_2


Material_1
{
Material_2
{
Material_3
Material_4
Material_5
{
Material_6
Material_7
}
Material_8
}
Material_9
Material_10
}
Material_11
{
Material_3
Material_7
Material_2
{
Material_3
Material_4
Material_5
{
Material_6
Material_7
}
Material_8
}
Material_13
}

Material_2


Material_1
{
Material_2
{
Material_3
Material_4
Material_5
{
Material_6
Material_7
}
Material_8
}
Material_9
Material_10
}

Material_20


！
```
## 样例输出
```
Material_9Material_10
Material_9Material_10
No
```
## 提示
>读入数据时，需采用如下方式进行读取。
>例：若要读取一行输入内容，则
```
cin.getline(line, lineSize, '\n');
sscanf(line, "%s", tmp);
```
>其中line和tmp为数组指针，类型为char* ，linesize为line所指向的数组的规模，为int型。
>所需读取的内容最终是存储在tmp数组中。之后如需对读取的内容进行操作，就对tmp进行操作即可，读到空行时tmp长度即为0。
采用其他方法读取可能会出现WA以及RE，TLE。