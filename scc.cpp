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
using Edge  =  pair<int,int>;
using Edges = vector<Edge>;
#define to   first
#define cost second

/* Kosaraju's SCC algorithm */
void dfs(Edges G[], int u, char visited[], stack<int>& st)
{
    visited[u] = 1;
    for(auto& v:G[u]) if (!visited[v.to]) dfs(G, v.to, visited, st);
    st.push(u);
}
void dfs_scc(Edges G[], int u, char visited[], vector<int>& scc)
{
    visited[u] = 1;
    scc.pb(u);
    for(auto& v:G[u]) if(!visited[v.to]) dfs_scc(G, v.to, visited, scc);
}

void kosaraju(Edges G[], int V, vector<vector<int> >& scc)
{
    Edges G_t[V];
    // DFS
    stack<int> st;
    char visited[V]; memset(visited, 0, sizeof(visited));
    rep(i,V) if(!visited[i]) dfs(G, i, visited, st);
    
    // transpose G
    rep(i,V) for(auto v:G[i]) G_t[v.to].pb(Edge(i,1));
    
    // SCC
    memset(visited, 0, sizeof(visited));
    while(!st.empty()) {
        int v = st.top(); st.pop();
        if(!visited[v]) {
            scc.pb(vector<int>());
            dfs_scc(G_t, v, visited, scc.back());
        }
    }

    // printing
    //for(auto& c:scc) {
    //    cout << "SCC: ";
    //    for(auto& v:c) cout << v << " ";
    //    cout << endl;
    //}
}

/* AOJ GRL3 */
int main()
{
    int V,E; cin>>V>>E;
    Edges G[V];
    vector<vector<int> > scc;
    
    rep(i,E){
        int u,v; cin>>u>>v;
        G[u].pb(Edge(v,1));
    }

    kosaraju(G, V, scc);

    int Q; cin>>Q;
    vector<int> ans;
    rep(i,Q) {
        int u,v; cin>>u>>v;
        bool sc = false;
        for(auto& c:scc)
            if((c.end() != find(c.begin(), c.end(), u))
               && (c.end() != find(c.begin(), c.end(), v))) sc = true;
        
        if(sc) ans.pb(1);
        else ans.pb(0);
    }

    for(auto& a:ans) cout << a << endl;
}
