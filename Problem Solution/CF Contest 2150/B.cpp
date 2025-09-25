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

#define int long long

const int N = 2e5 + 7;
const long long mod = 998244353;

int n, a[N];
long long fac[N];

long long ksm(long long x, long long y = mod - 2) {
    long long res = 1;
    for (; y; y >>= 1, (x *= x) %= mod)
        if (y & 1) (res *= x) %= mod;
    return res;
}

long long binom(long long x, long long y) {
    if (x < y || y < 0) return 0;
    return fac[x] * ksm(fac[y] * fac[x - y] % mod) % mod;
}

void solve() {
    n = read();
    for (int i = 1; i <= n; i ++)
        a[i] = read();
    fac[0] = 1;
    for (int i = 1; i <= n; i ++)
        fac[i] = fac[i - 1] * i % mod;
    int sum = 0;
    for (int i = 1; i <= n; i ++)
        sum += a[i];
    if (sum != n) {
        cout << 0 << '\n';
        return ;
    }

    bool flg = 1;
    for (int i = (n + 1) / 2 + 1; i <= n; i ++)
        flg &= (a[i] == 0);
    if (!flg) {
        cout << 0 << '\n';
        return ;
    }

    long long ans = 1;
    int num = 0;
    for (int i = (n + 1) / 2; i >= 1; i --) {
        num += (i * 2 > n ? 1 : 2);
        (ans *= binom(num, a[i])) %= mod;
        num -= a[i];
    }
    cout << ans << '\n';
}

signed main() {
    int t = 1;
    t = read();
    while (t --) solve();
    return 0;
}
