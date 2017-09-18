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

/* Adjacent List */
using Edge = pair<int,int>;
using Edges = vector<Edge>;
#define to   first
#define cost second

/* DFS-based Topological Sort */
void dfs(Edges G[], int u, char visited[], vector<int>& L)
{
    visited[u] = 1;
    for(auto v:G[u]) if(!visited[v.to]) dfs(G, v.to, visited, L);
    L.insert(L.begin(), u);
}

void tsort(Edges G[], int V, vector<int>& L)
{
    char visited[V];
    memset(visited, 0, sizeof(visited));
    rep(i,V) if(!visited[i]) dfs(G,i,visited,L);
}

int main()
{
    int V,E; cin>>V>>E;
    Edges G[V];
    vector<int> L;

    rep(i,E) {
        int u,v; cin>>u>>v; 
        G[u].pb(Edge(v,1));
    }
    tsort(G,V,L);

    for(auto e:L) cout << e << endl;
}
