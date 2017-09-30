#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

typedef long long ll;
#define pb push_back

#define rep(i, n) for (int i=0;i<(n);++i)
#define rep2(i, s, n) for (int i=s;i<(n);++i)
#define rev(i, n) for (int i=(n);i>0;--i)
#define INF (1e9+1e9)

/* SegTree 
   http://codeforces.com/blog/entry/18051
*/
class SegTree
{
public:
    vector<int> t;
    int n;
    SegTree(int n) : n(n){
        t.resize(n<<1); fill(t.begin(),t.end(),INT_MAX);
        build();
    }

    void build() { rev(i,n-1) t[i] = min(t[i<<1], t[i<<1|1]); }
    void modify(int p, int value) {
        for(t[p += n] = value; p > 1; p >>= 1) t[p>>1] = min(t[p], t[p^1]);
    }
    int query(int l, int r) { // [l,r)
        int res = INT_MAX;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = min(res, t[l++]);
            if (r&1) res = min(res, t[--r]);
        }
        return res;
    }
};

int main() {
    int N,Q; cin>>N>>Q;

    SegTree st(N);

    vector<int> C,X,Y;
    rep(i,Q) {
        int c,x,y; cin>>c>>x>>y;
        C.pb(c); X.pb(x); Y.pb(y);
    }

    rep(i,Q)
        if (C[i] == 0) st.modify(X[i], Y[i]);
        else cout << st.query(X[i], Y[i]+1) << endl;
}

 
