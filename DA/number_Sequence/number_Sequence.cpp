#include<iostream>
using namespace std;
long num[31269];
long str[31269];
long line[31269];
int cacu(int i)
{
    int len=0;
    while(i)
    {
        i=i/10;
        len++;
    }
    return len;
}
int main()
{
    for(int i=1;i<=31268;i++)
    {
        num[i]=cacu(i);
        str[i]=str[i-1]+num[i];
        line[i]=line[i-1]+str[i];
    }
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int i=0;
        for(i=1;i<=31268;i++)
        {
            if(line[i]>=n)
                break;
        }
        n=n-line[i-1];//在第i个str里2
        int j=0;
        for(j=1;j<=i;j++)
        {
            if(str[j]>=n)
                break;
        }
        n=n-str[j-1];//在第j个num里
        n=num[j]-n+1;
        int re=0;
        while(n--)
        {
            re=j%10;
            j=j/10;
        }
        cout<<re<<endl;
    }

}