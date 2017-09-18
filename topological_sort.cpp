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
typedef pair<int,int> edge;
#define to   first
#define cost second

/* DFS-based Topological Sort */
void dfs(vector<edge> G[], int u, char visited[], vector<int>& L)
{
    visited[u] = 1;
    for(auto v:G[u]) if(!visited[v.to]) dfs(G, v.to, visited, L);
    L.insert(L.begin(), u);
}

void tsort(vector<edge> G[], int V, vector<int>& L)
{
    char visited[V];
    memset(visited, 0, sizeof(visited));
    FOR(i,V) if(!visited[i]) dfs(G,i,visited,L);
}
    
int main()
{
    int V,E; cin>>V>>E;
    vector<edge> G[V];
    vector<int> L;

    FOR(i,E) {
        int u,v; cin>>u>>v; 
        G[u].pb(edge(v,1));
    }
    tsort(G,V,L);

    for(auto e:L) cout << e << " ";
    cout << endl;
}
/* Ex. input

8 8 
3 7 
3 4 
2 7 
1 4 
1 6 
7 0 
7 5 
4 5 

*/
