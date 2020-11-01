#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
    int n,m;
    const int MAXN=1001;
    char str[MAXN];
    const int LETTERS=26;
    int nNodesCount=2;
    struct CNode
    {
        CNode* pChilds[LETTERS];
        CNode* pPrev;
        bool bBadNode;
        CNode()
        {
            memset(pChilds,0,sizeof(pChilds));
            bBadNode=false;
            pPrev=NULL;
        }
    }Tree[120005];
    void build_tree(CNode *pRoot,char* s)
    {
        for(int i=0;s[i];i++)
        {
            int index=s[i]-'a';
            if(pRoot->pChilds[index]==NULL)
            {
                pRoot->pChilds[index]=Tree+nNodesCount;
                nNodesCount++;
            }
            pRoot=pRoot->pChilds[index];
        }
        pRoot->bBadNode=true;
    }
    void add_prev()
    {
        for(int i=0;i<LETTERS;i++)
            Tree[0].pChilds[i]=Tree+1;
        Tree[0].pPrev=NULL;
        Tree[1].pPrev=Tree;
        queue<CNode*>q;
        q.push(Tree+1);
        while(!q.empty())
        {
            CNode* pRoot=q.front();
            q.pop();
            for(int i=0;i<LETTERS;i++)
            {
                CNode* p=pRoot->pChilds[i];
                if(p)
                {
                    CNode* pPrev=pRoot->pPrev;
                    while(pPrev->pChilds[i]==NULL)
                        pPrev=pPrev->pPrev;
                    p->pPrev=pPrev->pChilds[i];
                    if(p->pPrev->bBadNode)
                        p->bBadNode=true;
                    q.push(p);
                }
                
            }
        }
    }
    bool search(char* s)
    {
        CNode *p=Tree+1;
        for(int i=0;s[i];i++)
        {
            int index=s[i]-'a';
            while(p->pChilds[index]==NULL)
                p=p->pPrev;
            p=p->pChilds[index];
            if(p->bBadNode)
                return true;
        }
        return false;
    }
    int main()
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",str);
            build_tree(Tree+1,str);
        }
        add_prev();
        scanf("%d",&m);
        for(int i=0;i<m;i++)
        {
            scanf("%s",str);
            if(search(str))
                printf("YES\n");
            else
                printf("NO\n");
        }
        return 0;
    }
