#include <iostream>
using namespace std;
int a[41][41];
int main()
{
    int N;
    cin >> N;
    int num = 0;
    int i = 0, j = N - 1;
    int sum = (2 * N - 1) * (2 * N - 1);
    while (num++ < sum)
    {
        a[i][j] = num;
        int ri= (i - 1 + 2 * N - 1) % (2 * N - 1);
        int rj= (j + 1) % (2 * N - 1);
        int di= (i + 1) % (2 * N - 1);
        if ((i == 0 && j == 2 * N - 2)||a[ri][rj])
            i=di;
        else
        {
            i=ri;
            j=rj;
        }
    }
    for(int i=0;i<2*N-1;i++)
    {
        for(int j=0;j<2*N-1;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
}