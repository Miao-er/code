#include<iostream>
using namespace std;
int modThree(int x) {
    int s=x>>31;
    int flag,value;
    int neg=~0;
    int inf=1<<31;
    int k=0;
    int j=~(inf>>15);//0000ffff
    int i;//获取高16位
    x=((~s)&x)|(s&(~x+1));
    i=(x>>16)&j;
    x=i+(x&j);//
    k=(x>>16)&1;
    j=255;//000000ff
    i=(x>>8)&j;//获取高8位
    x=i+(x&j);
    k+=(x>>8)&1;

    j=15;//0000000f
    i=(x>>4)&j;//获取高4位
    x=i+(x&j);
    k+=x>>4&1;

    j=3;//00000003
    i=(x>>2)&j;//获取高2位
    x=i+(x&j);
    k+=x>>2&1;

    x=x&3;
    k=k+x;
    i=(k>>2)&3;
    k=i+(k&3);

    value=k+(~2);
    flag=!value;
    k=((flag+neg)&k)|((~flag+1)&value);
    return ((~s)&k)|(s&(~k+1));
}
 
int main()
{
    int x;
    while(cin>>x)
    cout<<modThree(x);
}