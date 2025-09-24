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

const int N = 3e5 + 7;

int n, m;
vector<int> to[N], re[N];

bool vis[N];
int dis[N], pre[N], temp[N];

void solve() {
    n = read(), m = read();
    for (int i = 1, u, v; i <= m; i ++) {
        u = read(), v = read();
        to[u].push_back(v);
        to[v].push_back(u);
        re[u].push_back(v);
    }

    for (int i = 1; i <= n; i ++)
        vis[i] = 0, dis[i] = 2e9;
    dis[1] = 0, vis[1] = 1;
    queue<int> q; q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : to[u]) {
            if (vis[v]) continue;
            vis[v] = 1, dis[v] = dis[u] + 1;
            pre[v] = u, q.push(v);
        }
    }

    if (dis[n] < 5) {
        cout << dis[n] << '\n';
        vector<int> ans; int now = n;
        while (now) {
            ans.push_back(now);
            now = pre[now];
        }
        for (int i = (int) ans.size() - 1; i >= 0; i --)
            cout << ans[i] << ' ';
        cout << '\n';
        return ;
    }

    for (int x : to[1]) temp[x] = 1;
    for (int x : to[1])
        for (int y : to[x])
            if (y != 1 && !temp[y]) {
                cout << "4\n1 " << x << ' ' << y << ' ' << 1 << ' ' << n << '\n';
                return ;
            }
    for (int x : to[1]) temp[x] = 0;

    for (int x : to[1]) {
        for (int y : to[x]) temp[y] = 1;
        for (int y : to[x]) if (1 != y)
            for (int z : re[y]) if (1 != z && z != x)
                if (!temp[z]) {
                    cout << "5\n1 " << x << ' ' << y << ' ' << z << ' ' << x << ' ' << n << '\n';
                    return ;
                }
        for (int y : to[x]) temp[y] = 0;
    }

    cout << "-1\n";
}

signed main() {
    int t = 1;
    while (t --) solve();
    return 0;
}
