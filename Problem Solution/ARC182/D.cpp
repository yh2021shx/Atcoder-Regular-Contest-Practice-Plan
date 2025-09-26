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

int n, m;
int a[N], b[N], c[N];

void solve() {
    n = read(), m = read();
    for (int i = 1; i <= n; i ++) {
        a[i] = read();
        if (a[i - 1] > a[i])
            a[i] += (a[i - 1] - a[i] + m - 1) / m * m;
    }
    for (int i = 1; i <= n; i ++) {
        b[i] = read();
        if (b[i - 1] > b[i])
            b[i] += (b[i - 1] - b[i] + m - 1) / m * m;
    }
    if (m == 2) {
        cout << -(a[1] != b[1]) << endl;
        return ;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) c[i] = a[i] - b[i];
    sort(c + 1, c + n + 1);

    int mid = floor(1.0 * c[n / 2 + 1] / m);
    for (int i = 1; i <= n; i ++)
        ans += abs(a[i] - b[i] - mid * m);
    long long res = 0;
    mid = floor(1.0 * c[n / 2 + 1] / m) + 1;
    for (int i = 1; i <= n; i ++)
        res += abs(a[i] - b[i] - mid * m);
    cout << min(ans, res);
}

signed main() {
    int t = 1;
    // t = read();
    while (t --) solve();
    return 0;
}
