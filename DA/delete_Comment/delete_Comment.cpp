#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>
using namespace std;
int main()
{
    //freopen("out.txt","w",stdout);
    string line;
    bool left_quote=false;
    bool left_comment=false;
    bool right_end=false;
    while(getline(cin,line))
    {
        for(int i=0;i<line.length();i++)
        {
            if(i+1<line.length()&&line[i+1]=='*'&&line[i]=='/')
            {
                if(!left_comment&&!left_quote)
                {
                    left_comment=true;
                    i++;
                }
            }
            else if(i+1<line.length()&&line[i]=='*'&&line[i+1]=='/')
            {
                if(left_comment&&!left_quote)
                {    
                    left_comment=false;
                    right_end=true;
                    i++;
                }
            }
            else if(line[i]=='\"')
            {
                if(i&&line[i-1]=='\\');
                else if(!left_quote&&!left_comment)
                    left_quote=true;
                else if(left_quote&&!left_comment)
                    left_quote=false;  
            }
            if(!left_comment&&!right_end)
                cout<<line[i];
            if(right_end)
                right_end=false;
        }
        if(!left_comment)cout<<"\n";
    }
}
