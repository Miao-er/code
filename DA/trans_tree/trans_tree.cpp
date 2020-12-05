#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 20005
char str[N];
int main()
{   
    int count=0;
    while(cin>>str&&str[0]!='#')
    {
        count++;
        int h1=0,h2=0;
        int curlay1=0,curlay2=0;
        int lay[N/2];
        int len=strlen(str);
        for(int i=0;i<len/2;i++)
            lay[i]=0;
        lay[0]=1;
        for(int i=0;i<len;i++)
        {
            if(str[i]=='d')
            {
                curlay1++;
                h1=max(h1,curlay1);
                if(i==0||str[i-1]=='d')
                    lay[curlay1]=1;
                else lay[curlay1]++;
                curlay2=curlay2+lay[curlay1];
                h2=max(h2,curlay2);
            }
            else if(str[i]=='u')
            {
                curlay2=curlay2-lay[curlay1];
                curlay1--;
            }
        }
        printf("Tree %d: %d => %d\n",count,h1,h2);
    }
}