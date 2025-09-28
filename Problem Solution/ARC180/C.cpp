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
const int M = 2007;
const int mod = 1e9 + 7;

int n, a[N];
long long f[N][M], g[M];

void solve() {
    n = read(); long long ans = 0;
    for (int i = 1; i <= n; i ++)
        a[i] = read();

    const int V = 1000;
    f[0][V] = 1;
    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j <= V * 2; j ++) {
            (f[i][j] += f[i - 1][j]) %= mod;
            if (j != V) {
                (f[i][j + a[i]] += f[i - 1][j]) %= mod;
                (f[i][j + a[i]] += g[j]) %= mod;
            }
        }
        g[V + a[i]] = f[i - 1][V];
    }
    for (int j = 0; j <= V * 2; j ++)
        (ans += f[n][j]) %= mod;
    cout << ans << '\n';
}

signed main() {
    int t = 1;
    // t = read();
    while (t --) solve();
    return 0;
}
