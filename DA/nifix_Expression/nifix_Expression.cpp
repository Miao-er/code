#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
const int Low=1;
const int High=2;
int level(char ch)
{
    if(ch=='+'||ch=='-')
        return Low;
    if(ch=='*'||ch=='/')
        return High;
    if(ch==')')
    return Low+High;

    return 0;
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
int fun(char* a)
{
    stack<int>num;
    stack<char>oper;
    while(a[0]!='\0')
    {
        switch(a[0])
        {
            case '+':
            case '-':
            case '*':
            case '/':
                if(oper.empty()||level(a[0])>level(oper.top()))//优先级高于栈顶元素则先压入栈中
                    oper.push(a[0]);
                else 
                {
                    while(!oper.empty()&&level(oper.top())>=level(a[0]))//当前操作符优先级不高于栈顶元素，则栈内元素可以计算
                    {
                        char ch=oper.top();
                        oper.pop();
                        int n1=num.top();
                        num.pop();
                        int n2=num.top();
                        num.pop();
                        num.push(cacu(n1,n2,ch));
                    }
                    oper.push(a[0]);
                }
                a=a+1;
                break;
            case '(':
                oper.push(a[0]);//左括号直接压入
                a=a+1;
                break;
            case ')'://右括号匹配左括号，之间所有操作符可以直接运算
                while(oper.top()!='(')
                {
                    char ch=oper.top();
                    oper.pop();
                    int n1=num.top();
                    num.pop();
                    int n2=num.top();
                    num.pop();
                    num.push(cacu(n1,n2,ch));
                }
                oper.pop();
                a=a+1;
                break;
            default:
                int index=0;
                char temp[16];
                while(a[index]!='\0'&&isdigit(a[index]))
                {
                    temp[index]=a[index];
                    index++;
                }
                a=a+index;
                temp[index]='\0';
                int n=atoi(temp);
                //cout<<n<<endl;
                num.push(n);
        }
    }
    while(!oper.empty())//字符串读取完毕后需要将栈内剩下的操作符运算完成
    {
        char ch=oper.top();
        oper.pop();
        int n1=num.top();
        num.pop();
        int n2=num.top();
        num.pop();
        num.push(cacu(n1,n2,ch));
    }
    return num.top();
}
int main()
{
    int n;
    cin>>n;
    char a[601];
    while(n--)
    {
        cin>>a;
        cout<<fun(a)<<endl;

    }
}