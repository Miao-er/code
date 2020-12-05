#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define M 1005
int low[M],dfn[M],head[M],vis[M],cut[M];//cut记录割点
int n,cnt,num,t,root,root_son,textcase;
struct E
{
    int to,next;
}edg[M*20];

void init()
{
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(cut,0,sizeof(cut));
    cnt=0;
    textcase++;
    num=1;
    n=-1;
}

void addedge(int u,int v)
{
    edg[cnt].to=v;
    edg[cnt].next=head[u];
    head[u]=cnt++;
}

void Tarjan(int u)
{
    low[u]=dfn[u]=num++;
    for(int i=head[u];i!=-1;i=edg[i].next)
    {
        int v=edg[i].to;
        if(!dfn[v])
        {
            Tarjan(v);
            if(u==root)//若k为深搜树的根Root，当且仅当k的儿子数（分支数）>=2时k为割点；
                root_son++;
            else//若k为搜索树的中间结点（即k既不为根也不为叶），那么k必然有father和son，若low[son]>= dfn[k]，则k必然为割点。
            {
                if(low[u]>low[v])
                    low[u]=low[v];
                if(low[v]>=dfn[u])
                    cut[u]=1;
            }

        }
        else if(low[u]>dfn[v])
            low[u]=dfn[v];
    }
}

void dfs(int u)
{
    vis[u]=1;
    for(int k=head[u];k!=-1;k=edg[k].next)
    {
        int v=edg[k].to;
        if(!vis[v])
        {
            vis[v]=1;
            dfs(v);
        }

    }
}

int main()
{
    int u,v;
    textcase=0;
    while(scanf("%d",&u),u)
    {
        init();
        n=max(n,u);
        scanf("%d",&v);
        n=max(n,v);
        addedge(u,v);
        addedge(v,u);
        while(scanf("%d",&u),u)
        {
            n=max(n,u);
            scanf("%d",&v);
            n=max(n,v);
            addedge(u,v);
            addedge(v,u);
        }
        root=1;
        root_son=0;
        int flag=0;
        Tarjan(root);
        if(root_son>1)
            cut[root]=1;
        printf("Network #%d\n",textcase);
        for(int i=1;i<=n;i++)
        {
            if(cut[i])
            {
                flag=1;
                memset(vis,0,sizeof(vis));
                vis[i]=1;
                int son=0;
                for(int j=head[i];j!=-1;j=edg[j].next)
                {
                    int v=edg[j].to;
                    if(!vis[v])
                    {
                        dfs(v);
                        son++;
                    }
                }
                printf("  SPF node %d leaves %d subnets\n",i,son);
            }
        }
        if(!flag)
            printf("  No SPF nodes\n");
        printf("\n");
    }
    return 0;
}