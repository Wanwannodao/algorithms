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
    bool operator < (const Edge& e) const {
        //return cost != e.cost ? cost < e.cost : // vector sort
        return cost != e.cost ? cost > e.cost : // min priority queue
            u != e.u ? u < e.u : v < e.v;
    }
};
using Edges = vector<Edge>;
using Graph = vector<Edges>;

/* Prim's Algorithm */
pair<int,Edges> prim(Graph& G, int V, int r = 0)
{
    vector<bool> visited(V, false);
    priority_queue<Edge> q;
    int sum = 0;
    Edges A;

    q.push(Edge(-1,r,0)); // root 
    while(!q.empty()){
        Edge e = q.top(); q.pop();
        if(!visited[e.v]) { // add v
            sum += e.cost;
            visited[e.v] = true;
            A.pb(e);
            for(auto& adj: G[e.v]) if (!visited[adj.v]) q.push(adj); 
        }
    }
    return pair<int, Edges>(sum, A);
}

int main()
{
    int V,E; cin>>V>>E;
    Graph G(V);

    rep(i,E) {
        int u,v,c; cin>>u>>v>>c;
        G[u].pb(Edge(u,v,c));
    }

    pair<int,Edges> MST = prim(G,V);
    cout << MST.first << endl;
}


