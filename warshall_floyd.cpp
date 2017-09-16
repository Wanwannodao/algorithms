#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>

using namespace std;

typedef long long ll;

#define FOR(i, n) for (int i=0;i<n;++i)
#define INF(bit) (1 << bit)

// O(V^3)
int main()
{
    ll n;
    cin >> n;

    vector<vector<ll> > d(n, vector<ll>(n, INF(29)));

    // initialization
    FOR(i,n) {
        FOR(j,n) {
            ll e; cin >> e; d[i][j] = e;
        }
    }

    // calc
    FOR(k,n) FOR(i,n) FOR(j,n) if (d[i][j] > d[i][k] + d[k][j]) d[i][j] = d[i][k] + d[k][j];
}
