#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include<map>
#define inf 0x3f3f3f3f
using namespace std;
map<string, int> si;
map<int, string> is;
 
struct dist
{
	int len;
	int pre;
};
dist D[30][30];
void Floyd(int p)
{
	int i, j, g;
 	for (g = 0; g < p; g++)
		for (i = 0; i < p; i++)	
			for (j = 0; j < p; j++)
				if (D[i][g].len + D[g][j].len < D[i][j].len)
				{
					D[i][j].len = D[i][g].len + D[g][j].len;
					D[i][j].pre = D[g][j].pre;
				}
}
void print(int f, int  t)
{
	if (f == t)
	{
		cout << is[f];
		return;
	}
	print(f, D[f][t].pre);
	cout << "->" << '(' << D[D[f][t].pre][t].len << ')' << "->" << is[t];
}
int main()
{	int p;
	cin >>p ;
	for (int i = 0; i < p; i++)
	{	string place;
		cin >> place;
		si.insert(pair<string, int>(place, i));
		is.insert(pair<int, string>(i, place));
	}
	for (int i = 0; i < p; ++i)
		for (int j = 0; j < p; ++j)
		{
			if (i != j){
				D[i][j].len = inf; 
				D[i][j].pre = -1; 
			}
			else{
				D[i][j].len = 0;
				D[i][j].pre = i;
			}
		}
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i)
	{	string from, to;
		int far;
		cin >> from >> to >> far;
		if (D[si[from]][si[to]].len > far) {
			D[si[from]][si[to]].len = far;
			D[si[from]][si[to]].pre = si[from];
			D[si[to]][si[from]].len = far;
			D[si[to]][si[from]].pre = si[to];
		}
	}
	Floyd(p);
	int r;
	cin >> r;
	for (int i = 0; i < r; ++i)
	{	string a, b;
		cin >> a >> b;
		print(si[a], si[b]);
		cout << endl;
	}
	return 0;
}