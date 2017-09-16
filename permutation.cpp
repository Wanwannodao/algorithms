#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>
#include <stack>

using namespace std;

typedef long long ll;

#define FOR(i, n) for (int i=0;i<n;++i)
#define INF(bit) (1 << bit)

void dfs(ll pos, ll n, vector<bool>& used)
{
    if (pos == n) { cout << endl; return;} 
    FOR(i, n) if (!used[i]) {
        used[i] = true;
       
        cout << i << " ";
        
        dfs(pos+1, n, used);
        used[i] = false;
    }
}
    

// permutation enumeration
int main()
{
    ll n;
    cin>>n;

    vector<ll> a(n);

    // initialization
    FOR(i,n) a[i] = i;

    vector<bool> used(n, false);
    // Depth First Search (reccurent)
    dfs(0, n, used);

    // STL
    do {
        for (auto e:a) cout << e << " "; cout << endl;
    } while( next_permutation(a.begin(), a.end()));
}
