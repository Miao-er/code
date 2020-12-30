/*merge_Sort*/
#include <iostream>
#include <cstring>
using namespace std;
long arr[500005], tmp_arr[500005];
long merge(int start, int middle, int end)
{
    long sum = 0;
    for (int i = start; i <= end; i++)
        tmp_arr[i] = arr[i];
    int i = start, j = middle + 1, k = start;
    while (i <= middle && j <= end)
    {
        if (tmp_arr[i] > tmp_arr[j])
        {
            sum += middle + 1 - i;
            arr[k++] = tmp_arr[j++];

        }
        else
            arr[k++] = tmp_arr[i++];
    }
    while (i <= middle)
        arr[k++] = tmp_arr[i++];
    while (j <= end)
        arr[k++] = tmp_arr[j++];
    return sum;
}
long merge_Sort(int start, int end)
{
    long sum = 0;
    if (start == end)
        return 0;
    int middle = (start + end) / 2;
    sum += merge_Sort(start, middle);
    sum += merge_Sort(middle + 1, end);
    sum += merge(start, middle, end);
    return sum;
}
int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        int i = 0;
        for (i; i < n; i++)
            cin >> arr[i];
        cout<<merge_Sort(0,n-1)<<endl;
    }
}