#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Node
{
    int index, weight;
    Node() {}
    Node(int i, int w)
    {
        index = i;
        weight = w;
    }
};
struct Edge
{
    int start, end, weight;
    Edge() {}
    Edge(int s, Node n)
    {
        start = s;
        end = n.index;
        weight = n.weight;
    }
    bool operator<(const Edge &e) const
    {
        return weight > e.weight;
    }
};
int prim(vector<vector<Node>> graph, int n, int v0)
{
    bool *visit = new bool[n];
    for (int i = 0; i < n; i++)
        visit[i] = false;
    priority_queue<Edge> q;
    int v = v0, num = 0, sum = 0;
    visit[v] = true;
    Edge e;
    while (num < n - 1)
    {
        for (int i = 0; i < graph[v].size(); i++)
            if (visit[graph[v][i].index] == false)
                q.push(Edge(v, graph[v][i]));
        while (!q.empty())
        {
            e = q.top();
            q.pop();
            if (visit[e.end] == false)
                break;
        }
        num++;
        v = e.end;
        visit[v] = true;
        sum += e.weight;
    }
    return sum;
}
int main()
{
    int n;
    cin >> n;
    vector<vector<Node>> graph(26);
    char ch;
    int num;
    int line = 0;
    while (line < n - 1)
    {
        line++;
        cin >> ch >> num;
        int index = ch - 'A';
        char c;
        int m;
        while (num--)
        {
            cin >> c >> m;
            graph[index].push_back(Node(c - 'A', m));
            graph[c - 'A'].push_back(Node(index, m));
        }
    }
    cout << prim(graph, n, 0);
}