/*******************************
| Author:  DE_aemmprty
| Remember:
    * Read the question carefully!!!!!!
    * If you don't make progress on a question within five minutes, it's very likely that you are going in the wrong direction.
    * Don't rush to write code. Take your time.
    * If Div.2D is not made, it indicates that you have been defrauded.
*******************************/
#include <bits/stdc++.h>
using namespace std;

#define DBG_MACRO_FORCE_COLOR

#ifdef DE_aemmprty
#include "C:\dbg-macro\dbg.h"
#else
#define dbg(...)
#endif

template < typename T, typename...V > void chkMn(T &x, T y) { x = (x < y ? x : y); }
template < typename T, typename...V > void chkMx(T &x, T y) { x = (x < y ? y : x); }

long long read() {
    char c = getchar();
    long long x = 0, p = 1;
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') p = -1, c = getchar();
    while (c >= '0' && c <= '9')
        x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return x * p;
}

const int N = 107;
const int mod = 1e9 + 7;

int n, x[N];
long long f[N][N][N];

void solve() {
    n = read();
    for (int i = 1; i <= n; i ++)
        x[i] = read();

    for (int i = 1; i <= n + 1; i ++)
        for (int v = 0; v <= n; v ++)
            f[i][i - 1][v] = 1;

    for (int i = n; i >= 1; i --)
        for (int j = i; j <= n; j ++)
            for (int v = 1; v <= n; v ++)
                for (int p = i; p <= j; p ++)
                    (f[i][j][v] += f[i][p - 1][min(v, x[p])] * f[p + 1][j][min(v, x[p]) - 1] % mod) %= mod;

    cout << f[1][n][n] << '\n';
}

signed main() {
    int t = 1;
    while (t --) solve();
    return 0;
}
