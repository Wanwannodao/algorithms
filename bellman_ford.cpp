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
        return cost != e.cost ? cost < e.cost :
            u != e.u ? u < e.u : v < e.v;
    }
};
using Edges = vector<Edge>;
using Graph = vector<Edges>;

/* Bellman Ford algorithm */
bool bellman_ford(Graph& G, vector<int>& d, vector<int>& p, int s)
{
    int V = G.size();
    d[s]  = 0;
    rep(k,V-1) rep(i,V) for(auto& e:G[i]) if (d[e.u] != INF && d[e.v] > d[e.u] + e.cost) {
            d[e.v] = d[e.u] + e.cost;
            p[e.v] = e.u;
            if (k == V-1) return true;
        }
    return false;
    /* naive
    rep(k,V-1) rep(i,V) for(auto& e:G[i]) if(d[e.u] != INF && d[e.v] > d[e.u] + e.cost) {
            d[e.v] = d[e.u] + e.cost;
            p[e.v] = e.u;
        }
    rep(i,V) for(auto e:G[i]) if(d[e.u] != INF && d[e.v] > d[e.u] + e.cost) return true;
    return false;
    */
}
/* AOJ GRL1 */
int main()
{
    int V,E,s; cin>>V>>E>>s;
    Graph G(V);
    rep(i,E) {
        int u,v,c; cin>>u>>v>>c;
        G[u].pb(Edge(u,v,c));
    }

    vector<int> d(V,INF), p(V,-1);
    bool neg_cycle = bellman_ford(G,d,p,s);

    if(neg_cycle) cout << "NEGATIVE CYCLE" << endl;
    else rep(i,V)
             if(d[i] == INF) cout << "INF" << endl;
             else cout << d[i] << endl;   
}
