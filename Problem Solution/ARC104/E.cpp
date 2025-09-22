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

// #define DBG_MACRO_FORCE_COLOR

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

#define int long long

const int N = 7;
const long long mod = 1e9 + 7;

int n, M, a[N], tmp[N];
long long fac[N], ifac[N];

long long ksm(long long x, long long y = mod - 2) {
    long long res = 1;
    for (; y; y >>= 1, (x *= x) %= mod)
        if (y & 1) (res *= x) %= mod;
    return res;
}

long long C[N][N];

long long binom(long long x, long long y) {
    if (tmp[x] - tmp[x - 1] < y || y < 0) return 0;
    return C[x][y];
}

long long f[N][N], id[N], pos[N], ans;

long long dp[N];

bool check() {
    long long mx = 0;
    for (int i = 1; i <= n; i ++)
        chkMx(mx, id[i]);
    for (int i = 1; i <= mx; i ++) {
        bool flg = 0;
        for (int j = 1; j <= n; j ++)
            if (id[j] == i) flg = 1;
        if (!flg) return false;
    }
    return true;
}

void go_work() {
    for (int i = 1; i <= n; i ++)
        pos[i] = i, dp[i] = 1;
    long long riseLen = 0;
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j < i; j ++)
            if (id[j] < id[i]) chkMx(dp[i], dp[j] + 1);
        chkMx(riseLen, dp[i]);
    }

    sort(pos + 1, pos + n + 1, [&](int x, int y) {
        return id[x] < id[y];
    });

    for (int i = 0; i <= n; i ++)
        for (int j = 0; j <= n; j ++)
            f[i][j] = 0;
    f[0][0] = 1;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= M; j ++) {
            int len = tmp[j] - tmp[j - 1], cnt = 0;
            for (int l = i; l >= 1; l --) {
                if (l == i || id[pos[l]] < id[pos[l + 1]])
                    cnt ++;
                if (a[pos[l]] < j) break;
                long long ret = binom(j, cnt);
                if (id[pos[l - 1]] < id[pos[l]])
                    for (int pj = 0; pj < j; pj ++)
                        (f[i][j] += f[l - 1][pj] * ret) %= mod;
            }
        }
    }

    for (int j = 1; j <= M; j ++)
        (ans += f[n][j] * riseLen % mod) %= mod;
}

void dfs(int x) {
    if (x > n) {
        if (check())
            go_work();
        return ;
    }
    for (int i = 1; i <= n; i ++) {
        id[x] = i;
        dfs(x + 1);
    }
}

void solve() {
    n = read(); long long mul = 1;
    for (int i = 1; i <= n; i ++)
        a[i] = tmp[i] = read(), (mul *= a[i]) %= mod;
    sort(tmp + 1, tmp + n + 1);
    M = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= n; i ++)
        a[i] = lower_bound(tmp + 1, tmp + M + 1, a[i]) - tmp;

    fac[0] = 1;
    for (int i = 1; i <= n; i ++) fac[i] = fac[i - 1] * i % mod;
    for (int i = 0; i <= n; i ++) ifac[i] = ksm(fac[i]);

    for (int i = 1; i <= M; i ++) {
        C[i][0] = 1;
        for (int j = 1; j <= n; j ++)
            C[i][j] = C[i][j - 1] * (tmp[i] - tmp[i - 1] - j + 1) % mod * ksm(j) % mod;
    }

    dfs(1);
    cout << ans * ksm(mul) % mod << '\n';
}

signed main() {
    int t = 1;
    // t = read();
    while (t --) solve();
    return 0;
}
