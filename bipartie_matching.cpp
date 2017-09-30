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
#define INF (1e9+1e9)

class Edge{
public:
    int u, v, cost;
    Edge(int u, int v, int cost=1):
        u(u), v(v), cost(cost) {}
    bool operator < (const Edge& e) const {
        return cost != e.cost ? cost > e.cost : // for min-priority queue
            u != e.u ? u < e.u : v < e.v;
    }
};
using Edges = vector<Edge>;
using Graph = vector<Edges>;

/* Bipartie Matching using Ford-Fulkerson with DFS */
// DFS
// vertex u is always in L
bool dfs(Graph& G, int u, vector<bool>& visited, vector<int>& to)
{
    if (u == -1) return true; // augmenting path
    for(auto& e:G[u]) if(!visited[e.v]) {
        visited[e.v] = true; // vertex e.v is always in R
        if (dfs(G,to[e.v],visited,to)) { // we always traverse the matched edge (e.v, to[e.v])
            to[e.v] = u, to[u] = e.v;    // new matching
            return true; 
        }
    }
    return false; // no augmenting path 
}

int matching(Graph& G, int X, Edges& M)
{
    int V = G.size(), m = 0;
    vector<int> to(V,-1); // to[src] = dst
    
    rep(i,X) {
        vector<bool> visited(V,false);
        if (dfs(G,i,visited,to)) m++; // augmenting path found
    }

    //rep(i,X) if (to[i] != -1) M.pb(Edge(i, to[i]));
    return m;
}

int main()
{
    int X,Y,E; cin>>X>>Y>>E;
    Graph G(X+Y);
    rep(i,E) {
        int u,v; cin>>u>>v;
        G[u].pb(Edge(u,v+X));
        G[v+X].pb(Edge(v+X,u));
    }
    
    Edges M;
    int m = matching(G,X,M);
    cout << m << endl;
}
