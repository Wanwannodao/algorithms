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
// cf. http://www.prefield.com/algorithm/graph/graph.html
class Edge {
public:
    int u, v; // (u,v)
    int cost;
    Edge(int u, int v, int cost):
        u(u), v(v), cost(cost) {}
    bool operator < (const Edge& e) {
        return cost != e.cost ? cost < e.cost : 
            u != e.u ? u < e.u : v < e.v;
    }
};
using Edges = vector<Edge>;
using Graph = vector<Edges>;

/* Union-Find Tree */
class UnionFind {
public:
    vector<int> p,r; // parent, rank
    UnionFind(int n) {
        p.resize(n); r.resize(n);
        iota(p.begin(), p.end(), 0);
        fill(r.begin(), r.end(), 0);
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        int x = find(a), y = find(b);
        if (x == y) return;
        if(r[x] > r[y]) p[y] = x;
        else if (r[x] < r[y]) p[x] = y;
        else { p[y] = x; ++r[x]; } 
    }
    bool same(int x, int y) { return find(x) == find(y); }
};

/* Kruskal's Algorithm */
pair<int,Edges> kruskal(Graph& G, int V, int E)
{
    Edges edg, A;
    int sum = 0;
    UnionFind uf(V);

    rep(i,V) for(auto& e:G[i]) edg.pb(e);
    
    // sort w.r.t weights 
    sort(edg.begin(), edg.end());

    for(auto& e:edg) {
        if (!uf.same(e.u, e.v)) {
            A.pb(e);
            sum += e.cost;
            uf.unite(e.u, e.v);
        }
    }

    return pair<int,Edges>(sum, A);
}

int main()
{
    int V,E; cin>>V>>E;
    Graph G(V);
    
    rep(i,E){
        int u,v,c; cin>>u>>v>>c;
        G[u].pb(Edge(u,v,c));
    }

    pair<int,Edges> MST = kruskal(G,V,E);
    cout << MST.first << endl;
}

