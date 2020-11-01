# Computer Virus on Planet Pandora

**总时间限制: 2000ms 内存限制: 65536kB**
## 描述
>Aliens on planet Pandora also write computer programs like us. Their programs only consist of capital letters (‘A’ to ‘Z’) which they learned from the Earth. On planet Pandora, hackers make computer virus, so they also have anti-virus software. Of course they learned virus scanning algorithm from the Earth. Every virus has a pattern string which consists of only capital letters. If a virus’s pattern string is a substring of a program, or the pattern string is a substring of the reverse of that program, they can say the program is infected by that virus. Give you a program and a list of virus pattern strings, please write a program to figure out how many viruses the program is infected by.
## 输入
>There are multiple test cases. The first line in the input is an integer T ( T <= 10) indicating the number of test cases.

>For each test case:

>The first line is a integer n( 0 < n <= 250) indicating the number of virus pattern strings.

>Then n lines follows, each represents a virus pattern string. Every pattern string stands for a virus. It’s guaranteed that those n pattern strings are all different so there are n different viruses. The length of pattern string is no more than 1,000 and a pattern string at least consists of one letter.

>The last line of a test case is the program. The program may be described in a compressed format. A compressed program consists of capital letters and “compressors”. A “compressor” is in the following format:

>$[qx]$

>q is a number( 0 < q <= 5,000,000)and x is a capital letter. It means q consecutive letter xs in the original uncompressed program. For example, [6K] means ‘KKKKKK’ in the original program. So, if a compressed program is like:

$AB[2D]E[7K]G$

>It actually is ABDDEKKKKKKKG after decompressed to original format.
>The length of the program is at least 1 and at most 5,100,000, no matter in the compressed format or after it is decompressed to original format.
## 输出
>For each test case, print an integer K in a line meaning that the program is infected by K viruses.
## 样例输入
```
3
2
AB
DCB
DACB
3
ABC
CDE
GHI
ABCCDEFIHG
4
ABB
ACDEE
BBB
FEEE
A[2B]CD[4E]F
```
## 样例输出
```
0
3
2
```