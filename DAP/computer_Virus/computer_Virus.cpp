#include <iostream>
#include <string.h>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;
const int maxn = 255;
char line[5100005];
int T_num, n, sum = 0, ncount,len;
struct node {
    node*next[26];
    node*prev;
    int count;
    node() {
        memset(next, 0, sizeof(next));
        prev = NULL;
        count = 0;
    }
}tree[maxn * 1000];

void build_tree() {
  for (int i = 0; i < 26; i++)
    tree[0].next[i] = tree + 1;
    tree[0].prev = NULL;
    tree[1].prev = tree;
  queue<node*>q;
  q.push(tree + 1);
  while (!q.empty()) {
      node*now = q.front();
      q.pop();
      for (int i = 0; i < 26; i++) {
          node*child = now->next[i];
          if (child) {
              node*prev = now->prev;
              while (prev->next[i] == NULL)
                     prev = prev->prev;
                 child->prev = prev->next[i];
                 q.push(child);
             }
         }
     }
 }

int search(char *str) {
    int ans = 0;
    node*first = tree + 1;
    for (int i = 0; str[i] != '\0'; i++) {
        while (first->next[str[i] - 'A'] == NULL&&first!=(tree+1))
            first = first->prev;
        if (first->next[str[i] - 'A'])
            first = first->next[str[i] - 'A'];
        node*tmp = first;
        while (tmp != NULL && tmp->count != -1) {
            ans += tmp->count;
            tmp->count = -1;
            tmp = tmp->prev;
        }
    }
    return ans;
}

void insert(node*root, char* line) {
    int len = strlen(line);
    for (int i = 0; i < len; i++) {
        if (root->next[line[i] - 'A'] == NULL) {
            root->next[line[i] - 'A'] = tree + ncount;
            ncount++;
        }
        root = root->next[line[i] - 'A'];
    }
    root->count++;
}

void decompressed() {
    char ch;
    scanf("\n");
    while (scanf("%c", &ch)) {
        if (ch == '\n')
            break;
        if (ch == '[') {
            int c;
            scanf("%d", &c);
            scanf("%c", &ch);
            for (int i = 1; i <= c; i++)line[len++] = ch;
            scanf("%c", &ch);
        }
        else
            line[len++] = ch;
    }
    line[len] = '\0';
}

int main()
{   
  scanf("%d", &T_num);
    while (T_num--) {
        memset(tree, 0, sizeof(tree));
        sum = 0, ncount = 2,len=0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s",line);
            insert(tree + 1, line);
        }
        build_tree();
        decompressed();
        sum=search(line);
        reverse(line,line+len);
        sum+=search(line);
        printf("%d\n", sum);
    }
    return 0;
}