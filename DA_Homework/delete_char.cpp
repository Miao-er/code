/*
请设计一个删除字符串中的“b”和“ac”的算法， 要求满足如下的条件：
1) 字符串只能遍历一次；
2) 不能够使用额外的空间，即 O(1)的空间。
例如： acbac ==> ""； ababac ==> aa； bbbbd ==> d； aaccac
==> “”
*/
#include<iostream>
using namespace std;
int main()
{
    char a[100];
    cin>>a;
    int i=0,j=0;
    while(a[j]!='\0')
    {
        if(a[j]=='b')
            j++;
        else if(a[j]=='c'&&a[i-1]=='a')
        {
            i--;
            j++;
        }
        else 
        {
            a[i]=a[j];
            i++;
            j++;
        }
    }
    a[i]='\0';
    cout<<a;
}