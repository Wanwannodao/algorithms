#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>

using namespace std;

typedef long long ll;

#define FOR(i, n) for (int i=0;i<n;++i)
#define FOR2(i, s, n) for (int i=s;i<n;++i)
#define RFOR(i, n) for(int i=n;i>=0;--i)
#define INF(bit) (1 << bit)

/* Gaussian-Elimination
   
   x1 - 2x2 + 3x3 - 4x4 = 5
 -2x1 + 5x2 + 8x3 - 3x4 = 9
  5x1 + 4x2 + 7x4 +  x4 = -1
  9x1 + 7x2 + 3x3 + 5x4 = 4

 */
int main()
{
    // extended coeff. mat.
    ll n = 4, m = 4+1;
    double a[n][m] = {{ 1.0, -2.0, 3.0, -4.0, 5.0 },
                      {-2.0,  5.0, 8.0, -3.0, 9.0 },
                      { 5.0,  4.0, 7.0,  1.0,-1.0 },
                      { 9.0,  7.0, 3.0,  5.0, 4.0 }};
             
    // forward elimination
    FOR(k, n) {
        const double ipivot  = 1/a[k][k];
        FOR2(i, k+1, m) a[k][i] *= ipivot;
        FOR2(i, k+1, n) FOR2(j, k+1, m) a[i][j] -= a[i][k]*a[k][j];
    }    
    // back substitution
    RFOR(i,n-1) FOR2(j,i+1,n) a[i][m-1] -= a[i][j]*a[j][m-1];

    // solutions
    FOR(i,n) cout << a[i][m-1] << " "; cout << endl;
}
