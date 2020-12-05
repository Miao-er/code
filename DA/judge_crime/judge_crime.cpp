#include<iostream>
#include<cstring>
using namespace std;
#define N 100005
int parent[N];
bool relation[N];

int find_root(int i)
{
    int root=i;
    if(parent[i]!=root)
    {
        root=find_root(parent[i]);
        relation[i]=relation[i]^relation[parent[i]];
        parent[i]=root;  
    }
    
    return root;
}
int main()
{
    int cas;
    cin>>cas;
    while(cas--)
    {
        int n,m;
        cin>>n>>m;
        for(int i=0;i<=n;i++)
        {
            parent[i]=i;
            relation[i]=0;
        }
        while(m--)
        {
            char ch;
            int a,b;
            cin>>ch>>a>>b;
            if(ch=='D')
            {
                int pa=find_root(a);
                int pb=find_root(b);
                if(pa!=pb)
                {
                     relation[pb]=relation[b]^relation[a]^1;
                    parent[pb]=pa;
                }
            }
            else if(ch=='A')
            {
                int pa=find_root(a);
                int pb=find_root(b);
                if(pa!=pb)
                 {
                    printf("Not sure yet.\n");
                    continue;
                }
                if(relation[a]!=relation[b])
                    printf("In different gangs.\n");
                else printf("In the same gang.\n");
            }
        }
    }
}