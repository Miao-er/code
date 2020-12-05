#include<iostream>
#include<cstring>
#include<string>
#include<stack>
#include<vector>
using namespace std;
#define lineSize 20
struct Node
{
	string s;
	Node*father;
	vector<Node*>Child;
};
vector<Node*>T;
stack<Node*>father;
char line[lineSize];
void Delete(Node*root)
{
	if(root==NULL)return;
	for(int i=0;i<root->Child.size();++i)
	{
		Delete(root->Child[i]);
	}
	delete root;
}
void Search(Node*root,char*s,bool &is_find,Node**target)
{
	if(strcmp(s,root->s.c_str())==0)
	{
		is_find=true;
		*target=root;
		return;
	}
	for(int i=0;i<root->Child.size();++i)
	{
		Search(root->Child[i],s,is_find,target);
	}
}
int main()
{
	int n;
	cin>>n;
	cin.get();
	while(n--)
	{
		for(int i=0;i<T.size();++i)
	    {
		    Delete(T[i]);
	    }
	    T.clear();
	    while(!father.empty())
		    father.pop();
		Node*fa;
		Node*pre;
		while(true)
		{
			cin.getline(line,lineSize,'\n');
			int len=strlen(line);
			if(len==0)break;		
			if(line[0]=='{')
			{
				father.push(pre);
				continue;
			}
			if(line[0]=='}')
			{
				father.pop();
				continue;
			}
			fa=new Node();
			fa->s=line;
			if(father.empty())
			{
				fa->father=NULL;
				T.push_back(fa);
			}
			else
			{
				fa->father=father.top();
				fa->father->Child.push_back(fa);	
			}
			pre=fa;
		}
 
		cin.getline(line,lineSize,'\n');		
		bool is_find=false;
		Node*target=NULL;
		for(int i=0;i<T.size();++i)
		{
			Search(T[i],line,is_find,&target);
			if(is_find)break;
		}	
		if(!is_find)cout<<"No"<<endl;
		else
		{
			fa=target->father;
			int i;
			for(i=0;i<fa->Child.size();++i)
			{
				if(strcmp(line,fa->Child[i]->s.c_str())==0)break;
			}
			
			if(i+1==target->Child.size())cout<<"";
			else
			{
				for(int j=i+1;j<fa->Child.size();++j)
				{
					cout<<fa->Child[j]->s;
				}
			}
			cout<<endl;
		}
		cin.getline(line,lineSize,'\n');
		cin.getline(line,lineSize,'\n');
	}
	return 0;
}