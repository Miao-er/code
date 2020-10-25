//d 区间内的块数 
//len 区间覆盖长度 
//s 区间覆盖标记 
//l,r  区间控制的是pos_y[l]~pos_y[r] 
//l_cover,r_cover  左右端点是否被覆盖 
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

#define N 5000
int n,total=0;
int pos_y[4*N];
struct Line{
    int x,y1,y2,down;
};
Line line[2*N+1];
struct Node{
    int num,len,cover,l,r,l_cover,r_cover;
}tree[16*N+1];

bool cmp(const Line &l1,const Line &l2) 
{
    return l1.x<l2.x||(l1.x==l2.x&&l2.down<l1.down);
    }

void update(int root)
{
    int left_child=root<<1;
    int right_child=root<<1|1;
    if (tree[root].cover>0)
    {
        tree[root].len=pos_y[tree[root].r+1]-pos_y[tree[root].l];
        tree[root].l_cover=tree[root].r_cover=1;
        tree[root].num=1;
    }
    else
    {
        if (tree[root].l==tree[root].r)
        {
            tree[root].num=0;
            tree[root].len=0;
            tree[root].l_cover=tree[root].r_cover=0;
        } else {
            tree[root].len=tree[left_child].len+tree[right_child].len;
            tree[root].num=tree[left_child].num+tree[right_child].num-tree[left_child].r_cover*tree[right_child].l_cover;
            tree[root].l_cover=tree[left_child].l_cover; 
            tree[root].r_cover=tree[right_child].r_cover;   
        }
    }
}

void build_tree(int root,int l,int r)
{
    tree[root].num=0; 
    tree[root].len=0;
    tree[root].cover=0;
    tree[root].l=l; tree[root].r=r;
    tree[root].l_cover=tree[root].r_cover=0;
    if (l==r) return;
    int mid=(l+r)>>1;
    build_tree(root<<1,l,mid);
    build_tree(root<<1|1,mid+1,r);
}

void insert(int root,int l,int r,int down)
{
    if (tree[root].l>=l&&tree[root].r<=r)
    {
        tree[root].cover+=down;       //覆盖标记 
        update(root);
        return;
    }
    int mid=(tree[root].l+tree[root].r)>>1;
    if (l<=mid) insert(root<<1,l,r,down);
    if (r>mid) insert(root<<1|1,l,r,down);
    update(root);
}

int main()
{
    scanf("%d",&n);
    int num=0;
    for (int i=1;i<=n;i++)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        total++; 
        pos_y[++num]=y1;  
        line[total].x=x1; 
        line[total].y1=y1; 
        line[total].y2=y2; 
        line[total].down=1;
        total++; 
        pos_y[++num]=y2;
        line[total].x=x2; 
        line[total].y1=y1; 
        line[total].y2=y2; 
        line[total].down=-1;
    }
    sort(pos_y+1,pos_y+num+1);
    num=unique(pos_y+1,pos_y+1+num)-(pos_y+1);
    sort(line+1,line+1+total,cmp);
    build_tree(1,1,num);

    int x,y;    
    int result=0,cur_x=0,cur_num=0;
    for (int i=1;i<=total;i++)
    {
        x=lower_bound(pos_y+1,pos_y+1+num,line[i].y1)-pos_y;
        y=lower_bound(pos_y+1,pos_y+1+num,line[i].y2)-pos_y;
        insert(1,x,y-1,line[i].down);
        if (i>1) result+=cur_num*2*(line[i].x-line[i-1].x);
        result+=abs(tree[1].len-cur_x); 
        cur_x=tree[1].len;
        cur_num=tree[1].num;
    }
    printf("%d",result);
    return 0;
}