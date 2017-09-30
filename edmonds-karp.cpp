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
    Edge(int u, int v, int cost):
        u(u), v(v), cost(cost) {}
    bool operator < (const Edge& e) const {
        return cost != e.cost ? cost > e.cost : // for min-priority queue
            u != e.u ? u < e.u : v < e.v;
    }
};
using Edges = vector<Edge>;
using Graph = vector<Edges>;

/* Edmonds-Karp Algorithm */
int edmonds_karp(Graph& G, int s, int t)
{
    int V = G.size();
    // residual network, capacity
    // as for (u,v), c_f(u,v) = c(u,v) - f(u,v) (when both (u,v) in E and not in E on G)
    // this is because if (u,v) in E on G, f(v,u) = -f(u,v), c(v,u) = 0
    vector<vector<int> > f(V, vector<int>(V,0)), c(V, vector<int>(V,0));
    rep(i,V) for(auto& e:G[i]) c[e.u][e.v] = e.cost;
    
    int flow = 0;
    while(1) {
        // find an augmenting path (BFS)
        queue<int> Q; Q.push(s);
        vector<int> p(V, -1); p[s] = s;
        while(!Q.empty() && p[t] == -1) {
            int u = Q.front(); Q.pop();
            for(auto& e: G[u]) if (p[e.v] == -1 && c[u][e.v]-f[u][e.v] > 0){ // not visited && reachable
                    p[e.v] = u;
                    Q.push(e.v);
                }
        }
        if (p[t] == -1) return flow; // no augmenting path found
        
        // residual capacity of p
        int inc = INF;
        for(int i = t; i != s; i = p[i])
            inc = min(inc, c[p[i]][i] - f[p[i]][i]);
        // augmentation by f_p
        for(int i = t; i != s; i = p[i])
            f[p[i]][i] += inc, f[i][p[i]] -= inc;
           
        flow += inc; // |f↑ f_p| = |f| + |f_p|
    }
}
   

int main()
{
    int V,E; cin>>V>>E;
    Graph G(V);
    rep(i,E) {
        int u,v,c; cin>>u>>v>>c;
        G[u].pb(Edge(u,v,c));
    }

    int flow = edmonds_karp(G, 0, V-1);
    cout << flow << endl;
}
