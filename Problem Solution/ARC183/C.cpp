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

const int N = 507;
const int M = 1e5 + 7;
const int mod = 998244353;

int n, m, px[N][N];
int l[M], r[M], x[M];
int chk[N][N];
long long f[N][N], c[N][N];

void solve() {
    n = read(), m = read();
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++)
            px[i][j] = 2e9;
    for (int i = 1; i <= m; i ++) {
        l[i] = read(), r[i] = read(), x[i] = read();
        chkMn(px[l[i]][x[i]], r[i]);
    }

    for (int i = 0; i <= n + 1; i ++)
        for (int j = 1; j <= n; j ++)
            chk[i][j] = 2e9;
    for (int i = n; i >= 1; i --)
        for (int j = 1; j <= n; j ++)
            chk[i][j] = min(chk[i + 1][j], px[i][j]);

    c[0][0] = 1;
    for (int i = 1; i <= n; i ++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j ++)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }

    for (int i = 1; i <= n + 1; i ++)
        f[i][i - 1] = 1;
    for (int i = 1; i <= n; i ++)
        f[i][i] = (chk[i][i] <= i ? 0 : 1);

    for (int i = n; i >= 1; i --)
        for (int j = i + 1; j <= n; j ++)
            for (int p = i; p <= j; p ++)
                if (chk[i][p] > j)
                    (f[i][j] += f[i][p - 1] * f[p + 1][j] % mod * c[j - i][p - i] % mod) %= mod;
    cout << f[1][n] << '\n';
}

signed main() {
    int t = 1;
    // t = read();
    while (t --) solve();
    return 0;
}
