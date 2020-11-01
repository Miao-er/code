# DNA repair
**总时间限制: 2000ms 内存限制: 65536kB**
## 描述
>Biologists finally invent techniques of repairing DNA that contains segments causing kinds of inherited diseases. For the sake of simplicity, a DNA is represented as a string containing characters 'A', 'G' , 'C' and 'T'. The repairing techniques are simply to change some characters to eliminate all segments causing diseases. For example, we can repair a DNA "AAGCAG" to "AGGCAC" to eliminate the initial causing disease segments "AAG", "AGC" and "CAG" by changing two characters. Note that the repaired DNA can still contain only characters 'A', 'G', 'C' and 'T'.

>You are to help the biologists to repair a DNA by changing least number of characters.

## 输入
>The input consists of multiple test cases. Each test case starts with a line containing one integers N (1 ≤ N ≤ 50), which is the number of DNA segments causing inherited diseases.
>The following N lines gives N non-empty strings of length not greater than 20 containing only characters in "AGCT", which are the DNA segments causing inherited disease.
>The last line of the test case is a non-empty string of length not greater than 1000 containing only characters in "AGCT", which is the DNA to be repaired.
>The last test case is followed by a line containing one zeros.


## 输出
>For each test case, print a line containing the test case number( beginning with 1) followed by the
>number of characters which need to be changed. If it's impossible to repair the given DNA, print -1.
## 样例输入
```
2
AAA
AAG
AAAG    
2
A
TG
TGAATG
4
A
G
C
T
AGT
0
```
## 样例输出
```
Case 1: 1
Case 2: 4
Case 3: -1
```