#include <iostream>
#include<map>
using namespace std;

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int coe,index,times=0;
        map<int,int> poly;
        while(cin>>coe>>index)
        {
            if(index<0)
            {
                if(++times==2)
                    break;
                continue;
            }
            auto ins= poly.insert(make_pair(index,coe));
            if(!ins.second)
                ins.first->second+=coe;
        }
        map<int,int>::reverse_iterator iter;
        for(iter=poly.rbegin();iter!=poly.rend();iter++)
        {
            if(iter->second)
                cout<<"[ "<<iter->second <<' '<<iter->first<<" ] ";
        }
        cout<<endl;
    }
    system("pause");
    return 0;
}