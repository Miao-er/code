/*
模拟出栈入栈
*/

#include<iostream>
#include<stack>
#include<vector>
#include<cstring>
using namespace std;

bool islegal(vector<int> a,int n)
{
    //int*b =new int[n+1];
    //memset(b,0,sizeof(b));
    vector<int> b(n+1);
    if(a.size()!=n)//序列长度
        return false;
    for(int i=0;i<a.size();i++)//序列内容
    {
        if(a[i]<=0||a[i]>n||b[a[i]])
            return false;
        b[a[i]]=1;
    }
    for(int i=1;i<=n;i++)
    {
        if(!b[i])
            return false;
    }
    int i=0,j=0;
    stack<int> sta;
    while(i<n)//模拟出栈，假如当前元素应该出栈，则出栈并下标后移，假如刚好能模拟出给定序列的出栈顺序，所有元素均能按照该顺序出栈，则说明合法。
    {
        sta.push(++i);
        while(j<n&&!sta.empty()&&sta.top()==a[j])
        {
            sta.pop();
            j++;
        }
    }
    return sta.empty();
}
int main()
{
    int n;
    cin>>n;
    vector<int> a;
    for(int i=0;i<n;i++)
    {
        int k;
        cin>>k;
        a.push_back(k);
    }
    if(!islegal(a,n))
    {
        cout<<"NO\n";
        return 0;
    }
    int i=0,j=0;
    stack<int> sta;
    while(i<n)
    {
        sta.push(++i);
        cout<<"PUSH "<<i<<endl;
        while(j<n&&!sta.empty()&&sta.top()==a[j])
        {
            sta.pop();
            cout<<"POP "<<a[j]<<endl;
            j++;
        }
    }
}