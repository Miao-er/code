#include<queue>
#include<iostream>
#include<vector>
using namespace std;
int arr[101];
int main()
{
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        priority_queue<int,vector<int>,greater_equal<int>> que;
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
            que.push(arr[i]);
        }
        int sum=0;
        while(que.size()!=1)
        {
            int num1=que.top();
            que.pop();
            int num2=que.top();
            que.pop();
            int num=num1+num2;
            sum+=num;
            que.push(num);
        }
        cout<<sum<<endl;


    }
}