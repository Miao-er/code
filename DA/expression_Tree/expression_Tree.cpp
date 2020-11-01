#include<iostream>
#include<stack>
#include<map>
#include<cstring>
using namespace std;
map<char,int>var_val;
char graph[20][101];
struct Node
{
    char ch;
    Node* lc,*rc;
    int value;
    Node(char c)
    {
        lc=rc=NULL;
        ch=c;
        if(isalpha(ch))
            value=var_val[ch];
    }
};
int level(char ch)
{
    if(ch=='+'||ch=='-')
        return 1;
    if(ch=='*'||ch=='/')
        return 2;
    return ch==')'?3:0;
}
char* fun(char* a)
{
    char *b=new char[55];
    int k=0;
    stack<char>oper;
    while(a[0]!='\0')
    {
        switch(a[0])
        {
            case '+':case '-':case '*':case '/':
                if(oper.empty()||level(a[0])>level(oper.top()))
                    oper.push(a[0]);
                else 
                {
                    while(!oper.empty()&&level(oper.top())>=level(a[0]))
                    {
                        char ch=oper.top();
                        b[k++]=ch;
                        oper.pop();
                    }
                    oper.push(a[0]);
                }
                break;
            case '(':
                oper.push(a[0]);break;
            case ')':
                while(oper.top()!='(')
                {
                    char ch=oper.top();
                    b[k++]=ch;
                    oper.pop();
                }
                oper.pop();break;
            default:
                b[k++]=a[0];
        }
        a=a+1;
    }
    while(!oper.empty())//字符串读取完毕后需要将栈内剩下的操作符运算完成
    {
        char ch=oper.top();
        b[k++]=ch;
        oper.pop();
    }
    b[k]='\0';
    return b;
}
int cacu(int n1,int n2,char ch)
{
    switch(ch)
    {
        case '+':return n2+n1;break;
        case '-':return n2-n1;break;
        case '*':return n2*n1;break;
        case '/':return n2/n1;break;
    }
    return 0;
}
Node* make_tree(char* a)
{
    stack<Node*>val;
    while(a[0]!='\0')
    {
        Node* root=new Node(a[0]);
        switch(a[0])
        {
            case '+':case '-':case '/':case '*':
            {
                root->rc=val.top();
                val.pop();
                root->lc=val.top();
                val.pop();
                root->value=cacu(root->rc->value,root->lc->value,a[0]);
                val.push(root);
                break;
            }
            default:
                val.push(root);
        }
        a=a+1;
    }
    return val.top();
}
int count(Node* root)
{
    if(!root)return 0;
    int l=count(root->lc);
    int r=count(root->rc);
    return l>r?(l+1):(r+1);
}
void graph_tree(Node* root,int x1,int x2,int y)
{
    int mid=(x1+x2)/2;
    graph[y][mid]=root->ch;
    if(root->lc)
    {
        graph[y+1][mid-1]='/';
        graph_tree(root->lc,x1,mid-1,y+2);
    }
    if(root->rc)
    {
        graph[y+1][mid+1]='\\';
        graph_tree(root->rc,mid+1,x2,y+2);
    }
}
int main()
{
    char a[55],ch;
    scanf("%s",a);
    char *b=fun(a);
    cout<<b<<endl;
    int num,val;
    cin>>num;
    while(num--)
    {
        cin>>ch>>val;
        var_val.insert(make_pair(ch,val));
    }
    Node* root=make_tree(b);
    int layer=count(root);
    memset(graph,' ',sizeof(graph));
    graph_tree(root,0,(1<<layer)-2,0);
    for(int i=0;i<(layer<<1)-1;i++)
    {
        int j=100;
        while(graph[i][j]==' '&&j>0)j--;
            graph[i][j+1]=0;
        cout<<graph[i]<<endl;
    }
    cout<<root->value;
}