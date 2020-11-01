#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <deque>
using namespace std;
int ncount = 2;
struct Node
{
	int child[2],pprev;
	bool danger,visited;
	Node()
	{
		for (int i = 0; i < 2; i++)
			child[i] = 0;
		pprev = 0;
		danger = false;
		visited = false;
	}
}tree[30002];
void build_tree(string s)
{
	int l = s.size(),cur=1;
	for (int i = 0; i < l; i++)
	{
		if (tree[cur].child[s[i] - '0'] == 0)
		{
			tree[cur].child[s[i] - '0'] = ncount;
			ncount++;
		}
		cur=tree[cur].child[s[i] - '0'];
	}
	tree[cur].danger = true;
}
void add_prev()
{
	for (int i = 0; i < 2; i++)
	{
		tree[0].child[i] = 1;
	}
	tree[1].pprev = 0;
	deque<int> q;
	q.push_back(1);
	while (!q.empty())
	{
		int root = q.front();
		q.pop_front();
		for (int i = 0; i < 2; i++)
		{
			int child = tree[root].child[i];
			if (child)
			{
				tree[child].pprev = tree[root].pprev;
				while (!tree[tree[child].pprev].child[i])
					tree[child].pprev = tree[tree[child].pprev].pprev;
				tree[child].pprev = tree[tree[child].pprev].child[i];
				if (tree[tree[child].pprev].danger == true)
					tree[child].danger = true;
				q.push_back(child);
			}
		}
	}
}
bool flag=false;
void search(int root)
{
	if (flag)
		return;
	if (tree[root].danger)
		return;
	if (tree[root].visited)
	{
		flag = true;
		return;
	}
	tree[root].visited = true;
	for (int i = 0; i < 2; i++)
	{
		if (tree[root].child[i])
		{
			search(tree[root].child[i]);
		}
		else
		{
			int pre = tree[root].pprev;
			while (tree[pre].child[i] == 0)
				pre = tree[pre].pprev;
			search(tree[pre].child[i]);
		}
	}
	tree[root].visited = false;//这一句保证进入不同子节点递归时不产生相互影响，本质是DFS
}

int main()
{
	int n;
    string s;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		build_tree(s);
	}
	add_prev();
	search(1);
	if (flag)
		cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
	return 0;
}
