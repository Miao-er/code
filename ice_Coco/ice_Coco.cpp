#include<iostream>
using namespace std;
int parent[50005];
bool has[50005];
int getRoot(int i)
{
    if(parent[i]!=i)
        parent[i]=getRoot(parent[i]);
     return parent[i];
}
void merge(int x,int y)
{
    int px=getRoot(x);
    int py=getRoot(y);
    if(px==py)
    {
        cout<<"Yes"<<endl;
        cout<<"已经在同一杯"<<endl;
        return;
    }
    else cout<<"No"<<endl<<"倒入同一杯"<<endl;
    parent[py]=px;
    has[py]=false;
    has[px]=true;
}
int main()
{
    for(int i=1;i<=50000;i++)
    {
        parent[i]=i;
        has[i]=true;
    }
    int m,n;
    while(cin>>n>>m)
    {
        for(int i=1;i<=n;i++)
        {
            parent[i]=i;
            has[i]=true;
        }
        int x,y;
        while(m--)
        {
            cin>>x>>y;
            merge(x,y);
        }
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            if(has[i])sum++;
        }
        cout<<sum<<endl;
        for(int i=1;i<=n;i++)
        {
            if(has[i])
            {
                sum--;
                if(sum)
                    cout<<i<<" ";
                else cout<<i<<endl;
            }
        }
    }

}