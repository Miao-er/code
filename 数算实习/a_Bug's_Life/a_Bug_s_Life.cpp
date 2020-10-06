#include<iostream>
using namespace std;
int parent[2005];
int relation[2005];
int getRoot(int i)
{
    if(parent[i]!=i)
    {
        int t=getRoot(parent[i]);
        relation[i]=relation[i]^relation[parent[i]];
        parent[i]=t;
    }
    return parent[i];
}
bool merge(int id_1,int id_2)
{
    int r1=getRoot(id_1);
    int r2=getRoot(id_2);
    if(r1==r2)
    {
        if(relation[id_1]==relation[id_2])
            return false;
    }
    else
    {
        parent[r2]=id_1;
        relation[r2]=1-relation[id_2];
    }
    return true;
}
int main()
{
    int N,i=0;
    cin>>N;
    int num,times;
    while(i++<N)
    {
        scanf("%d %d",&num,&times);
        int id_1,id_2;
        for(int i=1;i<=num;i++)
        {
            parent[i]=i;
            relation[i]=0;
        }
        bool result=true;
        while(times--)
        {
            scanf("%d %d",&id_1,&id_2);
            result=result&&merge(id_1,id_2);
        }
        if(result)
            cout<<"Scenario #"<<i<<":\n"
                <<"No suspicious bugs found!\n\n";
        else 
            cout<<"Scenario #"<<i<<":\n"
                <<"Suspicious bugs found!\n\n";
    }
    system("pause");
}