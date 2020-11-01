#include<iostream>
#include<string>
using namespace std;
int* _next=NULL;
string to_lower(string str)
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]<='Z'&&str[i]>='A')
            str[i]=tolower(str[i]);
    }
    return str;
}
int* cac_next(string str)
{
    int len=str.length();
    _next=new int[len];
    _next[0]=-1;
    int i=0,k=-1;
    while(i<len-1)
    {
        while(k>=0&&str[k]!=str[i])
            k=_next[k];
        i++;
        k++;
        if(str[i]==str[k])
            _next[i]=_next[k];
        else _next[i]=k;
    } 
    return _next;
}
bool KMP(string str,string std_str)
{
    _next=cac_next(str);
    int len_str=str.length(),len_std=std_str.length();
    if(len_str==0&&len_std!=0)
        return false;
    if(len_str>len_std)return false;
    int i=0,j=0;
    while(i<len_str&&j<len_std)
    {
        if(i==-1||str[i]==std_str[j])
        {
            i++;
            j++;
        }
        else i=_next[i];
    }
    if(i==len_str)
        return true;
    return false;
}
bool pre_prc(string str,string std_str)
{
    int len_str=str.length(),len_std=std_str.length();
    int i=0,j=0;
    if(len_str>len_std-2)
        return false;
    while(std_str[i]!='[')
    {
        if(str[i]!=std_str[i])
            return false;
        i++;
    }
    while(std_str[len_std-j-1]!=']')
    {
        if(str[len_str-j-1]!=std_str[len_std-j-1])
            return false;
        j++;
    }
    return KMP(str.substr(i,len_str-j-i),std_str.substr(i+1,len_std-j-i-2));
}
int main()
{
    int n;
    string str[50];
    string std_str;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>str[i];
    cin>>std_str;
    std_str=to_lower(std_str);
    for(int i=0;i<n;i++)
    {
        if(pre_prc(to_lower(str[i]),std_str))
            cout<<i+1 <<" "<<str[i]<<endl;
    }
}