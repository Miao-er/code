#include <iostream>
using namespace std;
int main()
{
    int n;
    cout<<"输入n:";
    cin>>n;
    int* a=new int[n];
    int cnt=0;
    int item;
    cout<<"输入item:";
    cin>>item;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i]==item)
            cnt++;
        else
        {
            a[i-cnt]=a[i];
        }
    }
    cout<<"重复元素个数："<<cnt<<endl;
    cout<<"输出数组：\n";
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
}