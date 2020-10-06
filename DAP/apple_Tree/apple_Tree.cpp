#include<iostream>
#include<vector>
using namespace std;
int left_node[100001],right_node[100001],exist[100001],c[100001];
vector<int> sons[100001];
int node;
void make_tree(int i)
{
    node++;
    left_node[i]=node;
    for(int j=0;j<sons[i].size();j++)
        make_tree(sons[i][j]);
    right_node[i]=node;
}
int main()
{
    int n;
    cin>>n;
    int u,v;
    char ch;
    int num;
    node=0;
    for(int i=1;i<n;i++)
    {
        cin>>u>>v;
        sons[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
    {
        exist[i]=1;
        c[i]=i&(-i);
    }
    node=0;
    make_tree(1);
    int m;
    cin>>m;
    while(m--)
    {
        cin>>ch>>num;
        if(ch=='C')
        {
            exist[num]=1-exist[num];
            int r=left_node[num];
            while(r<=n)
            {
                c[r]+=2*exist[num]-1;
                r+=(r&(-r));
            }
        }
        else
        {
            int sum_r=0;
            int r =right_node[num];
            while(r)
            {
                sum_r+=c[r];
                r-=(r&(-r));
            }
            r=left_node[num]-1;
            while(r)
            {
                sum_r-=c[r];
                r-=(r&(-r));
            }
            printf("%d\n",sum_r);
        }
        
    }
}