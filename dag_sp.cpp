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

/* DAG Shortest Paths */
void dfs(Graph& G, int u, bool visited[], stack<int>& st)
{
    visited[u] = true;
    for(auto e:G[u]) if(!visited[e.v]) dfs(G, e.v, visited, st);
    st.push(u);         
}

void dag_sp(Graph& G, vector<int>& d, vector<int>& p, int s)
{
    int V = G.size();
    stack<int> st;
    bool visited[V]; memset(visited, false, sizeof(visited));
    /* Topological sort */
    rep(i,V) if(!visited[i]) dfs(G,i,visited,st);

    d[s] = 0;
    while(!st.empty()) {
        int u = st.top(); st.pop();
        for(auto& e:G[u]) if(d[e.u] != INF && d[e.v] > d[e.u] + e.cost) {
                d[e.v] = d[e.u] + e.cost;
                p[e.v] = e.u;
            }
    }
}

using Edges = vector<Edge>;
using Graph = vector<Edges>;

/*
ex. input
6 10 1
0 1 5
0 2 3
1 3 6
1 2 2
2 3 7
2 4 4
2 5 2
3 4 -1
3 5 1
4 5 -2

output
INF
0
2
6
5
3
*/

int main()
{
    int V,E,s; cin>>V>>E>>s;
    Graph G(V);
    rep(i,E) {
        int u,v,c; cin>>u>>v>>c;
        G[u].pb(Edge(u,v,c));
    }

    vector<int> d(V,INF), p(V,-1);
    dag_sp(G,d,p,s);

    rep(i,V)
        if(d[i] == INF) cout << "INF" << endl;
        else cout << d[i] << endl;
}
    
