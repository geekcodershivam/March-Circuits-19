#include <bits/stdc++.h>
using namespace std;
int n, k, uu, vv, ww;
vector<int> v[502], e[502], g[502], w[502];
int dp[502][502][2], seen[502][502][2];
void dfs(int pos, int par) {
    for (int i=0; i < v[pos].size(); i++) {
        int x = v[pos][i];
        int y = e[pos][i];
        if (x == par) {
            continue;
        }
        
        dfs(x,pos);
        
        g[pos].push_back(x);
        w[pos].push_back(y);
    }
}
int solve(int pos, int par, int it, int dep, int isRoot) {
    int &res = dp[pos][dep][isRoot];
    if (seen[pos][dep][isRoot] == 1) {
        return res;
    }
    
    seen[pos][dep][isRoot] = 1;
    res = 1e9;
    
    if (isRoot) {
        if (g[pos].size() == 0) {
            res = 0;
        }
        else {
            res = solve(g[pos][0],pos,0,k,0);
        }
    }
    else {
        res = 1;
        res += solve(pos, par, it, k, 1);
        res += (it+1 == g[par].size()) ? 0 : solve(g[par][it+1], par, it+1, dep, 0);
        for (int i=w[par][it]; i<=dep; i++) {
            int nxt = (it+1 == g[par].size()) ? 
                            0 : solve(g[par][it+1],par,it+1,min(dep,k-i),0);
            int cost = nxt;
            cost += (g[pos].size() == 0) ? 0 : 
                                solve(g[pos][0],pos,0,i-w[par][it],0);
            
            
            res = min(res, cost);
        }
    }
    
    return res;
}
int main () {
    cin >> n >> k;
    
    //the description of the tree
    for (int i = 1; i < n; i++) {
        
        cin >> uu >> vv >> ww;
        v[uu].push_back(vv);
        v[vv].push_back(uu);
        e[uu].push_back(ww);
        e[vv].push_back(ww);
    }
    dfs(1,0);
    int res = 1+solve(1,0,0,k,1);
    printf("%d\n", res);
    return 0;
}