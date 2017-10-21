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

// euclid
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
// gcd * lcm = ab
int lcm(int a, int b) {
    return a*b / gcd(a, b);
}

int lcms(vector<int>& num) {
    int l = num[0];
    rep2(i,1,num.size())
        l = lcm(l,num[i]);
    return l;
}

int main() {

    int n; cin >> n;
    vector<int> num(n);
    rep(i,n) {
        int a; cin >> a;
        num[i] = a;
    }

    cout << lcms(num) << endl;
}
