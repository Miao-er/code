#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 103
#define eps 1e-7
#define inf 1e9
#define pi acos(-1)
using namespace std;
int sgn(double x)
{
  if (fabs(x) < eps)
    return 0;
  return x < 0 ? -1 : 1;
}
struct Node
{
  double x, y;
  Node(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
    Node operator+(Node A)
  {
    return Node(x + A.x, y + A.y);
  }
  Node operator-(Node A)
  {
    return Node(x - A.x, y - A.y);
  }
  Node operator*(double p)
  {
    return Node(x * p , y * p);
  }
    double operator*(Node A)
  {
    return x * A.x + y * A.y;
  }
  double operator^(Node A)
  {
    return x * A.y - y * A.x;
  }
  double length()
  {
    return sqrt(x*x+y*y);
  }
  Node rotate(double rad)
  {
    return Node(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
  }
  Node unit()
  {
    return Node(x/length(),y/length());
  }
}p[N], tmp[N], node[N];
struct Line
{
  Node start, end;
  Line(){}
  Line(Node s,Node e):start(s),end(e){}
} line[N];
Node intersect(Line line, Node upper,Node bottom)
{
  double area1 = (line.end-line.start)^(upper-line.start);
  double area2 = (line.end-line.start)^(bottom-line.start);
  double x=upper.x + area1 / (area1 - area2) * (bottom.x - upper.x);
  double y=upper.y + area1 / (area1 - area2) * (bottom.y - upper.y);
  return Node(x,y);
}
int m, n;
void cut(Line line)
{
  int cnt = 0;
  memset(tmp, 0, sizeof(tmp));
  for (int i = 0; i < m; i++)
  {
    double value1 = (line.end - line.start) ^ (p[i] - line.start);
    double value2 = (line.end - line.start) ^ (p[(i + 1) % m] - line.start);
    if (sgn(value1) >= 0)
      tmp[cnt++] = p[i];
    if (sgn(value1) * sgn(value2) < 0)
      tmp[cnt++] = intersect(line,p[i], p[(i + 1) % m]);
  }
  m = cnt;
  for (int i = 0; i < cnt; i++)
    p[i] = tmp[i];
}
bool move(double x)
{
  for (int i = 2; i <= n + 1; i++)
  {
    Node v = node[i] - node[i - 1];
    Node u = v.rotate(pi / 2).unit();
    u = u * x;
    line[i - 1].end = node[i] + u ;
    line[i - 1].start = node[i-1] + u;
  }
  m = n;
  for(int i=0;i<m;i++)
    p[i]=node[i+1];
  for (int i = 1; i <= n; i++)
  {
    cut(line[i]);
    if (!m)
      return false;
  }
    return true;
}
int main()
{
  while (cin >> n && n)
  {
    for (int i = 1; i <= n; i++)
      cin >> node[i].x >> node[i].y;
    node[n + 1] = node[1];
    double l = 0, r = 10000, ans = 0;
    while (r - l > eps)
    {
      double mid = (l + r) / 2;
      if (move(mid))
      {
        l = mid;
        ans=mid;
      }
      else
        r = mid;
    }
    printf("%.6lf\n", ans);
  }
}