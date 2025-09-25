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

int n, v[N];
int a[N], b[N];
int pos[N];
long long mx[N << 2], tag[N << 2];

void pushUp(int x) {
    mx[x] = max(mx[x * 2], mx[x * 2 + 1]);
}

void hard(int x, int k) {
    mx[x] += k;
    tag[x] += k;
}

void pushDown(int x) {
    if (tag[x]) {
        hard(x * 2, tag[x]);
        hard(x * 2 + 1, tag[x]);
        tag[x] = 0;
    }
}

void Build(int x, int l, int r) {
    mx[x] = tag[x] = 0;
    if (l == r) {
        mx[x] = -2e18;
        return ;
    }
    int mid = l + r >> 1;
    Build(x * 2, l, mid);
    Build(x * 2 + 1, mid + 1, r);
    pushUp(x);
}

void update(int x, int l, int r, int L, int R, int k) {
    if (L <= l && r <= R) {
        hard(x, k);
        return ;
    }
    int mid = l + r >> 1; pushDown(x);
    if (L <= mid) update(x * 2, l, mid, L, R, k);
    if (mid < R)  update(x * 2 + 1, mid + 1, r, L, R, k);
    pushUp(x);
}

void update2(int x, int l, int r ,int p, int k) {
    if (l == r) {
        mx[x] = k;
        return ;
    }
    int mid = l + r >> 1; pushDown(x);
    if (p <= mid) update2(x * 2, l, mid, p, k);
    else update2(x * 2 + 1, mid + 1, r, p, k);
    pushUp(x);
}

int query(int x, int l, int r, int L, int R) {
    if (L <= l && r <= R) return mx[x];
    int mid = l + r >> 1;
    pushDown(x); int res = -2e18;
    if (L <= mid) res = query(x * 2, l, mid, L, R);
    if (mid < R) chkMx(res, query(x * 2 + 1, mid + 1, r, L, R));
    return res;
}


void solve() {
    n = read();
    for (int i = 1; i <= n; i ++)
        v[i] = read();
    for (int i = 1; i <= n; i ++) a[i] = read();
    for (int i = 1; i <= n; i ++) b[i] = read(), pos[b[i]] = i;

    Build(1, 0, n + 1);
    update2(1, 0, n + 1, n + 1, 0);
    for (int i = n; i >= 1; i --) {
        int val = pos[a[i]];
        update(1, 0, n + 1, 0, val - 1, v[a[i]]);
        int res = query(1, 0, n + 1, val, n + 1);
        update2(1, 0, n + 1, val, res + v[a[i]]);
    }
    cout << query(1, 0, n + 1, 0, n + 1) << '\n';
}

signed main() {
    int t = 1;
    t = read();
    while (t --) solve();
    return 0;
}
