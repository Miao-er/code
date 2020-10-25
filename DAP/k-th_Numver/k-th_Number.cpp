#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX 100000
vector<int> sorted_vec[4*MAX + 10];   
int m,n;
int a[MAX+10];

void bulid_tree(int root, int l, int r)
{
    if (r - l == 1) {
        sorted_vec[root].push_back(a[l]); 
        return;
    }
    int left_child = root<<1, right_child =root<<1|1;
    bulid_tree(left_child, l, (l + r)>>1);
    bulid_tree(right_child, (l + r)>>1, r);
    sorted_vec[root].resize(r - l);
    merge(sorted_vec[left_child].begin(), sorted_vec[left_child].end(),
         sorted_vec[right_child].begin(), sorted_vec[right_child].end(),
         sorted_vec[root].begin());
}

int query(int i, int j, int x, int root, int l, int r)
{
    if (j <= l || r <= i)
        return 0;
    else if (i <= l&&r <= j)
    {
        return upper_bound(sorted_vec[root].begin(), sorted_vec[root].end(), x) - sorted_vec[root].begin();
    }
    else 
    {
        int left_cnt = query(i, j, x, root<<1 , l, (l + r)>>1);
        int right_cnt = query(i, j, x, root<<1|1, (l + r)>>1, r);
        return left_cnt + right_cnt;
    }
}
 
int find(int x, int y, int k)
{
    int l = -1000000000 - 1;
    int r = -l;
    while (l < r)
    {
        int mid = (l + r)>>1;
        int num = query(x, y+1, mid, 1, 1, n+1);
        if (k <= num) r = mid;
        else{
            l = mid + 1;
        }
    }
    return l;
}
 
int main()
{
    int l,r,x;
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= n; i++)
    {
       scanf("%d", a + i);
    }
    bulid_tree(1, 1, n + 1);

    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &l, &r, &x);
        printf("%d\n", find(l, r, x));
    }
    return 0;
}