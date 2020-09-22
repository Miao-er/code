#include<iostream>
using namespace std;
int relation[50005];
int parent[50005];
int sum=0;
int N,K;
int getRoot(int i)
{
    if(parent[i]!=i){
        int t = getRoot(parent[i]);
        int re=relation[i]+relation[parent[i]];
        if(re==2)
            relation[i]=-1;
        else if(re==-2)
            relation[i]=1;
        else 
            relation[i]=re;
        parent[i]=t;
    }
    return parent[i];
}
void merge(int i,int x,int y)
{
    if(x>N||y>N)
    {
        sum++;
        return;
    }
    if(i==1)
    {
        int px=getRoot(x);
        int py=getRoot(y);
        if(px==py)
       {
            if(relation[x]!=relation[y])
                sum++;
       }
        else
        {
            parent[py]=x;
            relation[py]=-relation[y];
        }
   }
   else if(i==2)
   {
       if(x==y)
       {
           sum++;
           return;
       }
        int px=getRoot(x);
        int py=getRoot(y);
        if(px==py)
       {
            if((relation[x]+3)%3-1!=relation[y])sum++;
       }
        else
        {
            parent[py]=x;
            relation[py]=1-(relation[y]+2)%3;
        }

   }
}
int main()
{
    //relation
    //0 同类
    //1 吃
    //-1 被吃
    cin>>N>>K;
    for(int j=1;j<=N;j++)
    {
        relation[j]=0;
        parent[j]=j;
    }
   
    while(K--)
    {
        int D,X,Y;
       
        cin>>D>>X>>Y;
        merge(D,X,Y);
    }
    cout<<sum;
    system("pause");
}