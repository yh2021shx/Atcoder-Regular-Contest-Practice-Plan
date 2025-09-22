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

int n, k, m;
long long f[N][N * N * N];

void solve() {
    n = read(), k = read(), m = read();
    f[0][0] = 1; int sum = 0;
    for (int i = 1; i <= n; i ++) {
        sum += i * k;
        for (int j = 0; j <= sum; j ++) {
            f[i][j] = f[i - 1][j];
            if (j >= i) (f[i][j] += f[i][j - i]) %= m;
        }
        for (int j = sum; j >= 0; j --)
            if (j >= i * (k + 1))
                f[i][j] = (f[i][j] - f[i][j - i * k - i] + m) % m;
    }
    for (int x = 1; x <= n; x ++) {
        long long ans = 0;
        for (int s = 0; s <= sum; s ++)
            (ans += f[x - 1][s] * f[n - x][s] % m * (k + 1) % m) %= m;
        cout << (ans + m - 1) % m << '\n';
    }
}

signed main() {
    int t = 1;
    // t = read();
    while (t --) solve();
    return 0;
}
