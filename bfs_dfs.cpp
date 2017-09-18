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

#define FOR(i, n) for (int i=0;i<n;++i)
#define FOR2(i, s, n) for (int i=s;i<n;++i)
#define INF (1e9)

/* Adjacent List */
//template <typename T, typename U>
//using edge = pair<T, U>;
typedef pair<int,int> edge;
#define to   first
#define cost second

/* Breadth First Search */
void bfs(vector<edge> G[], int s, char visited[])
{
    queue<int> q;
    visited[s] = 1;
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for(auto v: G[u]) if (!visited[v.to]) {
                cout << "visitting:" << v.to << endl;
                visited[v.to] = 1;
                q.push(v.to);
            }
    }
}

/* Depth First Search */
// reccurent
void dfs(vector<edge> G[], int u, char visited[])
{
    visited[u] = 1;
    cout << "visitting:" << u << endl;
    for(auto v: G[u]) if (!visited[v.to]) dfs(G, v.to, visited);
}
void dfs2(vector<edge> G[], int s, char visited[])
{
    stack<int> st;
    visited[s] = 1;
    st.push(s);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for(auto v: G[u]) if (!visited[v.to]) {
                cout << "visitting:" << v.to << endl;
                visited[v.to] = 1;
                st.push(v.to);
            }
    }
}

int main()
{
    int V, E; cin>>V>>E;
    vector<edge> G[V];
    char visited[V];
    
    FOR(i,E) {
        int u,v,c; cin>>u>>v>>c;  // edge (u,v) with cost c 
        // Undirected Graph
        G[u].pb(edge(v, c));
        G[v].pb(edge(u, c));
        // Directed Graph
        //G[u].pb(Edge<ll,ll>(v,c));
    }
    FOR(i,V) for(auto p:G[i]) cout << "(" << i << "," << p.to << ")" << "@" << p.cost << endl;

    memset(visited, 0, sizeof(visited));
    cout << "BFS" << endl;
    bfs(G, 0, visited);
    
    memset(visited, 0, sizeof(visited));
    cout << "DFS" << endl;
    dfs(G, 0, visited);
    
    memset(visited, 0, sizeof(visited));
    cout << "DFS2" << endl;
    dfs2(G, 0, visited);    
}
