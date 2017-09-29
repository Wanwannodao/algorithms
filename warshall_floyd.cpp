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

/* Warshall-Floyd Algorithm */  
// O(V^3)
int main()
{
    ll V,E; cin>>V>>E;
    vector<vector<ll> > d(V, vector<ll>(V, INF));
    
    // initialization
    rep(i,V) d[i][i] = 0;
    rep(i,E) { ll u,v,c; cin>>u>>v>>c; d[u][v] = c; }
    // calc
    rep(k,V) rep(i,V) rep(j,V) if (d[i][j] > d[i][k] + d[k][j]) d[i][j] = d[i][k] + d[k][j];

    rep(i,V) {
        rep(j,V) { if (d[i][j] == INF) cout << "INF"; else cout << d[i][j]; if(j!=V-1) cout << " ";}
        cout << endl;
    }
}
