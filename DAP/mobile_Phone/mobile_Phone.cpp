#include<iostream>
using namespace std;
int c[1025][1025];
int cacu(int i,int j)
{
    int ii=i,jj=j,sum=0;
    while(ii)
    {
        while(jj)
        {
            sum+=c[ii][jj];
            jj-=(jj&(-jj));
        }
        ii-=(ii&(-ii));
        jj=j;
    }
    return sum;
}
int main()
{
    int instr,s;
    int x,y,a;
    int l,b,r,t;
    cin>>instr>>s;
    for(int i=1;i<=s;i++)
    {
        for(int j=1;j<=s;j++)
        {
            c[i][j]=0;
        }
    }
    while(cin>>instr)
    {
        if(instr==3)
            break;
        if(instr==1)
        {
            cin>>x>>y>>a;
            int xi=++x;
            int yi=++y;
            while(xi<=s)
            {
                while(yi<=s)
                {
                    c[xi][yi]+=a;
                    yi+=(yi&(-yi));
                }
                xi+=(xi&(-xi));
                yi=y;
            }
        }
        else if(instr==2)
        {
            cin>>l>>b>>r>>t;
            int sum=cacu(r+1,t+1)-cacu(r+1,b)-cacu(l,t+1)+cacu(l,b);
            printf("%d\n",sum);
        }
    }
}