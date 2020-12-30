/*priority_queue*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Cow
{
    int index;
    long ai, bi;
    Cow(int i, long a, long b) : index(i), ai(a), bi(b) {}
    Cow() {}
};
struct cmp_ai
{
    bool operator()(Cow a, Cow b)
    {
        return a.ai < b.ai;
    }
};
struct cmp_bi
{
    bool operator()(Cow a, Cow b)
    {
        return a.bi < b.bi;
    }
};
 int main()
{
    priority_queue<Cow, vector<Cow>, cmp_ai> q1;
    priority_queue<Cow, vector<Cow>, cmp_bi> q2;
    int index = 0, n, k;
    cin >> n >> k;
    long ai, bi;
    while (n--)
    {
        cin >> ai >> bi;
        Cow cow(++index,ai,bi);
        q1.push(cow);
    }
    while(k--)
    {
        Cow cow=q1.top();
        q1.pop();
        q2.push(cow);
    }
    if(!q2.empty())
    {
        Cow cow = q2.top();
        cout<<cow.index;
    }
}