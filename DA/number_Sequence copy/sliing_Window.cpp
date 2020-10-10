/*
双端单调队列，控制开头元素为最大值/最小值并保证容纳元素始终不超过K
*/

#include<iostream>
#include<deque>
using namespace std;
struct node
{
    int max;
    int min;
};
int main()
{
    int n;
    int k;
    cin>>n>>k;
    int* a=new int[n+1];
    node m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(i==1)
        {
            m.max=a[i];
            m.min=a[i];
        }
        else if(a[i]>m.max)
            m.max=a[i];
        else if(a[i]<m.min)
            m.min=a[i];
    }
    if(n<=k)
        cout<<m.min<<endl<<m.max<<endl;
    else
    {
        node *M=new node[n-k+2];
        deque<int> um,dm;
        for(int i=1;i<=n;i++)
        {
            while(!um.empty()&&a[um.back()]<a[i])
                um.pop_back();
            while(!dm.empty()&&a[dm.back()]>a[i])
                dm.pop_back();
            um.push_back(i);
            dm.push_back(i);
            if(um.front()<=i-k)
                um.pop_front();
            if(dm.front()<=i-k)
                dm.pop_front();
            if(i>=k)
            {
                M[i-k+1].max=a[um.front()];
                M[i-k+1].min=a[dm.front()];
            }
        }
        for(int i=1;i<=n-k+1;i++)
            cout<<M[i].min<<" ";
            cout<<endl;
        for(int i=1;i<=n-k+1;i++)
            cout<<M[i].max<<" ";        
    }
}