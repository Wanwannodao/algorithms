#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>
#include <cstdlib>
using namespace std;

typedef long long ll;

#define FOR(i, n) for (int i=0;i<n;++i)
#define FOR2(i, s, n) for (int i=s;i<n;++i)

class UnionFind {
public:
    vector<int> p, r; // parent, rank
    UnionFind(int n) {
        // MakeSet
        p.resize(n); r.resize(n);
        // FOR(i,n) p[i] = i;  // POJ: iota cases compile error  
        iota(p.begin(), p.end(), 0);
        fill(r.begin(), r.end(), 0);
    }
    int find(int x) {
        if (p[x] == x) return x;
        else return p[x] = find(p[x]); // path compression
    }
    void unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if( xr == yr ) return; 
        // union by rank
        if (r[xr] > r[yr]) p[yr] = xr;
        else if (r[xr] < r[yr]) p[xr] = yr;
        else if (xr != yr) { p[yr] = xr; ++r[xr]; } // xr.rank == yr.rank && xr in A and yr in A' A!=A'
    }
    bool same(int x, int y) { return find(x) == find(y); }
};


/* Ex: POJ 1182 Food Chain */
int main()
{
    int n, k;
    cin >> n >> k;
    // x   : x as an element of A
    // x+n : x as an element of B
    // x+2n: x as an element of C
    UnionFind uf(3*n);
    
    int cnt = 0;

    // construct three pattern of "consistent" sets
    FOR(i,k) {
        int d,x,y;
        scanf("%d %d %d", &d, &x, &y); x--; y--;
        //cin >> d >> x>> y; x--; y--;

        if (x>=n || y>=n || x < 0 || y < 0){ cnt++; continue; }

        if (d==1) {
            // one of inconsistent pattern
            if ( uf.same(x,y+n) || uf.same(x, y+2*n) ) cnt++; // x in A, y in B or x in A, y in C
            else FOR(j,3) uf.unite(x+j*n, y+j*n);
        } else if(d==2) {
            // one of inconsistent pattern
            if ( uf.same(x, y) || uf.same(x, y+2*n) ) cnt++; // x in A, y in A or x in A, y in C
            else { // three consistent patterns
                uf.unite(x, y+n);
                uf.unite(x+n, y+2*n);
                uf.unite(x+2*n, y);
            }
        }
    }
    cout << cnt << endl;
}
