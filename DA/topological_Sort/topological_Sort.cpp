#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int*indegree;
void TopologicalSort(vector<vector<int>>graph,int n)
{
	priority_queue<int,vector<int>,greater<int>>q;
	for(int i=1;i<=n;i++)
		if(!indegree[i])
			q.push(i);
	while(!q.empty())
	{
		int index=q.top();
		q.pop();
		cout<<"v"<<index<<" ";
		for(int i=0;i<graph[index].size();i++)
		{
			indegree[graph[index][i]]--;
			if(!indegree[graph[index][i]])
				q.push(graph[index][i]);
		}
	}
}
int main()
{
	int n,m,i=0;
	cin>>n>>m;
	int start,end;
	vector<vector<int>>graph(n+1);
	indegree=new int[n+1];
	for(int i=0;i<=n;i++)
		indegree[i]=0;
	while(i<m)
	{
		cin>>start>>end;
		graph[start].push_back(end);
		indegree[end]++;
		i++;
	}
	TopologicalSort(graph,n);

}