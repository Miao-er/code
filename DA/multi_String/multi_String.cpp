#include<iostream>
#include<cstring>
using namespace std;
int _next[1000005];
char str[1000005];
void get_next(int size)
{
    int i=0,j=-1;
    _next[0]=-1;
    while(i<size)
    {
        while(j>=0&&str[j]!=str[i])
            j=_next[j];
        i++;
        j++;
            _next[i]=j;
    }
}
int main()
{
    while(scanf("%s",str))
    {
        if(str[0]=='.')
            break;
        int size=strlen(str);
        get_next(size);
        if(size%(size-_next[size])==0)
            printf("%d\n",size/(size-_next[size]));
        else
        {
            printf("1\n");
        }
        
    }
}