#include<iostream>
using namespace std;

void mod(double& y)
{
    y=0.0;
    cout<<y<<" ";
}
 
int main()
{
    int x=1010;
    mod(x);
    cout<<x;
}