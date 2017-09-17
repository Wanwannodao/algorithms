#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>

using namespace std;

typedef long long ll;

#define FOR(i, n) for (int i=0;i<n;++i)
#define FOR2(i, s, n) for (int i=s;i<n;++i)
#define INF(bit) (1 << bit)

/* Simplex method

Subject to:
   2x1 + x2 <= 4
   x1 +  2x2 <= 3
   x1,x2    >= 0
Maximize:
  z = x1 + x2

 */

int main()
{
    ll n = 3, m = 5;

    // coeff. mat.
    //                  x1  x2  s1  s2   
    double a[n][m] = {{-1.,-1., 0., 0., 0. },
                      { 2., 1., 1., 0., 4.},
                      { 1., 2., 0., 1., 3. }};

    while(true) {
        // entering variable
        double en = INF(19);
        ll e;
        FOR(i,m-1) if (en > a[0][i]) { e = i; en = a[0][i]; }
        if(en >= 0) break;
        
        // leaving variable
        // select the row with min ratio ( rhs/(en. var. coeff.))
        ll l = 0;
        double ratio = INF(19);
        FOR2(i,1,n)
            if (a[i][e] >= 0 && ratio > a[i][m-1] / a[i][e]) { l = i; ratio = a[i][m-1] / a[i][e]; }

        // pivoting
        const double ipivot = 1/a[l][e];
        FOR(i,m) a[l][i] *= ipivot;
        FOR(i,n) if (i != l) {
            double c = a[i][e];
            FOR(j,m) a[i][j] -= c*a[l][j];
        }
    }
    FOR(i,m-1) {
        ll sum = 0;
        FOR2(j,1,n) sum += a[j][i];
        if (sum == 1) 
            FOR2(j,1,n) if(a[j][i] == 1.)
                { cout << "x" << i << " = " << a[j][m-1] << endl; break; }
    }
    cout << "Max:" << a[0][m-1] << endl;
}
