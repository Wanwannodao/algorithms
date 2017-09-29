#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <queue>
#include <stack>
using namespace std;

typedef long long ll;
#define pb push_back

#define rep(i, n) for (int i=0;i<(n);++i)
#define rep2(i, s, n) for (int i=s;i<(n);++i)
#define INF (1e9)

/* Transitive Closure */
int main()
{
    ll V,E; cin>>V>>E;
    vector<vector<bool> > d(V, vector<bool>(V, false));

    rep(i,V) d[i][i] = true;
    rep(i,E) { ll u,v; cin>>u>>v; d[u][v] = true;}

    rep(k,V) rep(i,V) rep(j,V) d[i][j] = d[i][j] | (d[i][k] & d[k][j]);

    rep(i,V) { rep(j,V) cout << d[i][j] << " "; cout << endl;} 
}
    
