
#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std ;
const int Maxn = 1001;
const int INF = 0x3f3f3f3f ;

int child[Maxn][4], _prev[Maxn], ncount ;
bool isdanger[Maxn];
int dp[Maxn][Maxn], n ;
string str, mStr ;
 
inline int transform (char ch){
    if (ch == 'A') return 0 ;
    if (ch == 'C') return 1 ;
    if (ch == 'G') return 2 ;
    return 3 ;
}
 
void bulid_tree(){
    int len = str.size() ;
    int root = 0 ;
    for (int i = 0; i < len; i++){
        int id = transform(str[i]) ;
        if (!child[root][id]) 
            child[root][id] = ++ncount ;
        root = child[root][id] ;
    }
    isdanger[root] = true;
}
 
void add_prev (){
    queue < int > que ;
    for (int i = 0; i < 4; i++){
        if (child[0][i]) {
            _prev[child[0][i]] = 0 ;
            que.push(child[0][i]) ;
        }
    }
    while (!que.empty()){
        int root = que.front() ;
        que.pop();
        if (isdanger[_prev[root]]) isdanger[root] = true ;
        for (int i = 0; i < 4; i++){
            if (child[root][i]){
                _prev[child[root][i]] = child[_prev[root]][i] ;
                que.push(child[root][i]) ;
            }
            else child[root][i] = child[_prev[root]][i] ;
        }
    }
}
 
void search(){
    int len = mStr.size();
    for (int i = 0; i <= len; i++){
        for (int j = 0; j < ncount; j++){
            dp[i][j] = INF ;
        }
    }
    dp[0][0] = 0 ;
    for (int i = 0; i < len; i++){
        for (int j = 0; j < ncount; j++){
            if (dp[i][j] >= INF) continue ;
            for (int k = 0; k < 4; k++){
                int u = child[j][k] ;
                if (isdanger[u]) continue ;
                int value ;
                value = k == transform(mStr[i])? dp[i][j]: dp[i][j] + 1;
                dp[i + 1][u] = min(dp[i + 1][u], value) ;
            }
        }
    }
    int ans = INF ;
    for (int i = 0; i < ncount; i++) ans = min(dp[len][i], ans) ;
    if (ans == INF) cout << -1 << endl ;
    else cout << ans << endl ;
}
 
int main (){
    int Cas = 0 ;
    while (cin >> n && n){
        ncount = 0 ;
        memset(child,0 ,sizeof(child)) ;
        memset(_prev, 0, sizeof(_prev)) ;
        memset(isdanger, 0, sizeof(isdanger)) ;
        for (int i = 0; i < n; i++){
            cin >> str ;
            bulid_tree() ;
        }
        add_prev() ;
        cin >> mStr ;
        cout << "Case " << ++Cas << ": " ;
        search() ;
    }
    return 0;
}
 