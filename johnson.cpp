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

/* Johnson Alogrithm */
bool johnson(Graph& G, vector<vector<int> >& d, vector<vector<int> >& p)
{
    int V = G.size();

    vector<int> h(V,0); 
    // Bellman-Ford
    rep(k,V) rep(i,V) for(auto& e:G[i]) if (h[e.v] > h[e.u] + e.cost) {
            h[e.v] = h[e.u] + e.cost;
            if (k == V-1) return true; // negative cycle
        }

    // reweighting
    rep(i,V) for(auto& e:G[i]) e.cost += h[e.u] - h[e.v];

    rep(s, V) {
        // Dijkstra
        priority_queue<Edge> Q;
        d[s][s] = 0;
        Q.push(Edge(s,s,0));
        while(!Q.empty()) {
            Edge e = Q.top(); Q.pop();
            if(d[s][e.v] == INF) continue;
            for(auto& f:G[e.v]) if(d[s][f.v] > d[s][f.u] + f.cost) {
                    d[s][f.v] = d[s][f.u] + f.cost;
                    p[s][f.v] = f.u;
                    Q.push(Edge(f.u, f.v, d[s][f.u] + f.cost));
                }
        }
        // re-calculating
        rep(i,V) if(d[s][i] != INF) d[s][i] += h[i] - h[s];
    }
    return false;
}

int main()
{
    int V,E; cin>>V>>E;
    Graph G(V);
    rep(i,E) {
        int u,v,c; cin>>u>>v>>c;
        G[u].pb(Edge(u,v,c));
    }

    vector<vector<int> > d(V,vector<int>(V,INF)), p(V,vector<int>(V,-2));
    bool neg_cycle = johnson(G,d,p);

    if(neg_cycle) cout << "NEGATIVE CYCLE" << endl;
    else rep(i,V) {
            rep(j,V) {
                if (d[i][j] == INF) cout << "INF";
                else cout << d[i][j];
                if(j != V-1) cout << " ";
            }
            cout << endl;
        }
}
