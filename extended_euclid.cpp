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
// (d', x', y') = extgcd(b, a mod b)
// return (d', y', x' - floor(a/b)*y')
// x <-> y', y <-> x'
int extgcd(int a, int b, int& x, int & y) {
    int gcd;
    if (b == 0) gcd = a, x = 1, y = 0;
    else gcd = extgcd(b, a%b, y, x), y -= a/b*x;

    return gcd;
}

int main() {

    int a,b; cin>>a>>b;
    int x,y;
    int g = extgcd(a, b, x, y);
    cout << x << " " << y << endl;
}
