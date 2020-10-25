#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#define maxn 100000
using namespace std;
 
vector<int> dat[4*maxn + 50];    //线段树的数据
int a[maxn + 50];
int n, q;
 
//构建线段树
//k是节点的编号，和区间[l, r)对应
void build(int k, int l, int r)
{
    if (r - l == 1) {
        dat[k].push_back(a[l]); return;
    }
    int lc = k << 1, rc = k << 1 | 1;
    build(lc, l, (l + r) / 2);
    build(rc, (l + r) / 2, r);
    dat[k].resize(r - l);
    //利用STL的merge函数把两个儿子的数列合并
    merge(dat[lc].begin(), dat[lc].end(), dat[rc].begin(), dat[rc].end(),dat[k].begin());
}
 
//计算[i, j)中不超过x的数的个数
//k是节点的编号，和区间[l, r)对应
int query(int i, int j, int x, int k, int l, int r)
{
    if (j <= l || r <= i)
        //完全不相交
        return 0;
    else if (i <= l&&r <= j){
        //完全包含在里面
        return upper_bound(dat[k].begin(), dat[k].end(), x) - dat[k].begin();
    }
    else {
        //对儿子递归地计算
        int lcnt = query(i, j, x, k << 1, l, (l + r) / 2);
        int rcnt = query(i, j, x, k << 1 | 1, (l + r) / 2, r);
        return lcnt + rcnt;
    }
}
 
int search(int x, int y, int k)
{
    int l = -1000000000 - 1;
    int r = -l + 2;
    while (l < r){
        int mid = (l + r) >> 1;
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
    while (cin >> n >> q)
    {
        for (int i = 1; i <= n; i++){
            scanf("%d", a + i);
        }
        build(1, 1, n + 1);
        int li, ri, ki;
        for (int i = 0; i < q; i++){
            scanf("%d%d%d", &li, &ri, &ki);
            printf("%d\n", search(li, ri, ki));
        }
    }
    return 0;
}