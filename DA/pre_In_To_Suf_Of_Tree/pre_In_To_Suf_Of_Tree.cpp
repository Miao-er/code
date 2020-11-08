#include<iostream>
using namespace std;
void to_prefix(int *in,int *suf,int length)
{
    if(!length)return;
    int num=suf[length-1];
    int index=0;
    for(index;in[index]!=num;index++);
    cout<<num<<" ";
    to_prefix(in,suf,index);
    to_prefix(in+index+1,suf+index,length-index-1);
}
int main()
{
    int infix[65536];
    int suffix[65536];
    cin>>infix[0];
    int num,i=0,j=0;
    while(cin>>num&&num!=infix[0])
        infix[++i]=num;
    suffix[0]=num;
    while(j<i&&cin>>num)
        suffix[++j]=num;
    to_prefix(infix,suffix,j+1);


}