#include <iostream>
using namespace std;
int main()
{
    int n = 9, m = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 2 * i; j <= n; j++)
            m = m + 1;
    cout << m;
    return 0;
}