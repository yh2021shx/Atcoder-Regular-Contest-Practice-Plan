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

const int N = 2.5e5 + 7;

struct Node {
    int v, siz;
    bool operator < (const Node &x) const {
        return siz < x.siz;
    }
};

int n, siz[N], b[N];
vector<int> to[N], path[N];
priority_queue<Node> pq_odd, pq_even;

int tx[N], rt;

void findWeight(int u, int fa) {
    tx[u] = -2e9; siz[u] = 1;
    for (int v : to[u]) {
        if (v == fa) continue;
        findWeight(v, u);
        chkMx(tx[u], siz[v]);
        siz[u] += siz[v];
    }
    chkMx(tx[u], n - siz[u]);
    if (rt == 0 || tx[rt] > tx[u])
        rt = u;
}

void init(int u, int fa) {
    siz[u] = 1;
    for (int v : to[u]) {
        if (v == fa) continue;
        init(v, u);
        siz[u] += siz[v];
    }
    b[u] = (siz[u] & 1);
}

int cnt[N];

void go_work(int u, int fa, int tp) {
    int hs = 0;
    if (b[u] == 0) {
        for (int v : to[u])
            if (v != fa && b[v])
                hs = v;
        go_work(hs, u, tp);
    }
    for (int v : to[u])
        if (v != fa && v != hs)
            go_work(v, u, tp);
    path[tp].push_back(u);
}

void solve() {
    n = read();
    for (int i = 1; i <= n; i ++)
        to[i].clear(), path[i].clear(), cnt[i] = 0;
    for (int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].push_back(v);
        to[v].push_back(u);
    }
    rt = 0;
    findWeight(1, 0);
    init(rt, 0);

    while (!pq_odd.empty()) pq_odd.pop();
    while (!pq_even.empty()) pq_even.pop();
    for (int v : to[rt]) {
        go_work(v, rt, v);
        if (b[v] == 0) pq_even.push({v, siz[v]});
        else pq_odd.push({v, siz[v]});
    }

    while (!pq_odd.empty() && !pq_even.empty()) {
        auto [x, sizx] = pq_odd.top(); pq_odd.pop();
        auto [y, sizy] = pq_even.top(); pq_even.pop();
        cout << path[x][cnt[x] ++] << ' ' << path[y][cnt[y] ++] << '\n';
        if (cnt[x] < (int) path[x].size()) pq_even.push({x, sizx - 1});
        if (cnt[y] < (int) path[y].size()) pq_odd.push({y, sizy - 1});
    }

    int lst = (pq_odd.empty() ? pq_even.top().v : pq_odd.top().v);
    cout << lst << ' ' << rt << '\n';
}

signed main() {
    int t = 1;
    while (t --) solve();
    return 0;
}
