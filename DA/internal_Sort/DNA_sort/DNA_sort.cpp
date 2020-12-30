#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct Cnt
{
    int cnt;
    string str;
}s[105];
int cnt_reverse(string str,int len)
{
    int num=0;
    for(int i=0;i<len-1;i++)
        for(int j=i+1;j<len;j++)
        {
            if(str[i]>str[j])
                num++;
        }
    return num;
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        cin>>s[i].str;
        s[i].cnt=cnt_reverse(s[i].str,n);
    }
    for(int i=0;i<m-1;i++)
        for(int j=m-1;j>i;j--)
        {
            if(s[j].cnt<s[j-1].cnt)
                swap(s[j],s[j-1]);
        }
    for(int i=0;i<m;i++)
        cout<<s[i].str<<endl;
}