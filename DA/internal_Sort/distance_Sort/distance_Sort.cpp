/*bubble sort*/
#include <math.h>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;
struct Node
{
    int x, y, z;
} node[11];
struct Edge
{
    Node fir, sec;
    double dist;
} edge[50];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> node[i].x >> node[i].y >> node[i].z;
    int index = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            edge[index].fir = node[i];
            edge[index].sec = node[j];
            edge[index].dist = sqrt((node[i].x - node[j].x) * (node[i].x - node[j].x) + (node[i].y - node[j].y) * (node[i].y - node[j].y) + (node[i].z - node[j].z) * (node[i].z - node[j].z));
            index++;
        }
    for (int i = 0; i < index - 1; i++)
        for (int j = index - 1; j > i; j--)
        {
            if (edge[j].dist > edge[j - 1].dist)
                swap(edge[j], edge[j - 1]);
        }
    for (int i = 0; i < index; i++)
    {
        cout << "(" << edge[i].fir.x << "," << edge[i].fir.y << "," << edge[i].fir.z << ")-"
             << "(" << edge[i].sec.x << "," << edge[i].sec.y << "," << edge[i].sec.z << ")="
             << fixed << setprecision(2) << edge[i].dist << endl;
    }
}
