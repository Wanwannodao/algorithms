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

/* Dijkstra Algorithm */
void dijkstra(Graph& G, vector<int>& d, vector<int>& p, int s)
{
    int V = G.size();
    priority_queue<Edge> Q;

    d[s] = 0;
    Q.push(Edge(-2,s,0)); // Edge.cost as d
    while(!Q.empty()) {
        Edge e = Q.top(); Q.pop();
        if(d[e.v] == INF) continue;
        for(auto& f:G[e.v]) if(d[f.v] > d[f.u] + f.cost) {
                d[f.v] = d[f.u] + f.cost;
                p[f.v] = f.u;
                Q.push(Edge(f.u, f.v, d[f.u] + f.cost));
            }
    }
}

int main()
{
    int V,E,s; cin>>V>>E>>s;
    Graph G(V);
    rep(i,E) {
        int u,v,c; cin>>u>>v>>c;
        G[u].pb(Edge(u,v,c));
    }

    vector<int> d(V,INF), p(V,-1);
    
    dijkstra(G,d,p,s);
    
    rep(i,V)
        if(d[i] == INF) cout << "INF" << endl;
        else cout << d[i] << endl;
}
