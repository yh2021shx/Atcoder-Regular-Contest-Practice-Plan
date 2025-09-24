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

const int N = 1e5 + 7;

int n, a[N];
vector<int> b[107];

int res[N], temp[N], m;

void solve() {
    n = read();
    for (int i = 1; i <= n; i ++) {
        a[i] = read(), b[__lg(a[i])].push_back(a[i]);
        dbg(a[i], __lg(a[i]));
    }
    for (int i = 60; i >= 0; i --) {
        if (b[i].empty()) continue;
        int tot = 1, j = 1;
        temp[tot] = b[i][0];
        for (int l = 1; l <= m; l ++) {
            temp[++ tot] = res[l];
            if (((res[l] >> i) & 1) && j < (int) b[i].size())
                temp[++ tot] = b[i][j ++];
        }
        if (j < (int) b[i].size()) {
            cout << "No\n";
            return ;
        }
        m = tot;
        for (int j = 1; j <= m; j ++)
            res[j] = temp[j];
    }
    cout << "Yes\n";
    for (int i = 1; i <= m; i ++)
        cout << res[i] << ' ';
    cout << '\n';
}

signed main() {
    int t = 1;
    while (t --) solve();
    return 0;
}
