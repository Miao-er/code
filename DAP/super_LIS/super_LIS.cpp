#include<iostream>
#include<algorithm>
using namespace std;

struct Node
{
    long value;
    int pos;
};
bool cmp(Node x,Node y)
{
    if(x.value!=y.value)
        return x.value<y.value;
    return x.pos>y.pos;
}
//注意排序式相同元素按从大到小的位置即逆序排列
int main()
{
    int n;
    cin>>n;
    Node *_list=new Node[300001];
    int c[300001];
    for(int i=1;i<=n;i++)
    {
        cin>>_list[i].value;
        _list[i].pos=i;
        c[i]=0;
    }
    sort(_list+1,_list+n+1,cmp);
    int cur_lis;
    for(int i=1;i<=n;i++)
    {
        int k=_list[i].pos;
        cur_lis=0;
        while(k)
        {
            if(c[k]>cur_lis)
                cur_lis=c[k];
            k-=(k&(-k));
        }
        k=_list[i].pos;
        cur_lis++;
        while(k<=n)
        {
            if(c[k]<cur_lis)
            c[k]=cur_lis;
            k+=(k&(-k));
        }
    }
    cur_lis=0;
    for(int i=n;i;i-=(i&(-i)))
    {
        if(c[i]>cur_lis)
            cur_lis=c[i];
    }
    cout<<cur_lis;
}