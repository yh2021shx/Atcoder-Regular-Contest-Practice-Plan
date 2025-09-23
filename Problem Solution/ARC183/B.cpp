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

const int N = 2.5e5 + 7;

int n, k;
int a[N], b[N], tmp[N];
vector<int> to[N];

void solve() {
    n = read(), k = read(); map<int, int> AAA;
    for (int i = 1; i <= n; i ++) a[i] = read(), AAA[a[i]] ++;
    for (int i = 1; i <= n; i ++) b[i] = read();
    for (int i = 1; i <= n; i ++) to[i].clear();

    bool flg = 1;
    for (int i = 1; i <= n; i ++) {
        flg &= (a[i] == b[i]);
        if (!AAA.count(b[i])) {
            cout << "No\n";
            return ;
        }
    }
    if (flg) {
        cout << "Yes\n";
        return ;
    }

    if (k == 1) {
        int m = 1; tmp[1] = b[1];
        for (int i = 2; i <= n; i ++)
            if (b[i] != b[i - 1]) tmp[++ m] = b[i];

        int s = 0;
        for (int i = 1; i <= n; i ++)
            if (s < m && a[i] == tmp[s + 1]) s ++;
        cout << (s == m ? "Yes\n" : "No\n");
        return ;
    }

    for (int i = 1; i <= n; i ++)
        to[b[i]].push_back(i);
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j < (int) to[i].size(); j ++)
            if (to[i][j] - to[i][j - 1] <= k) {
                cout << "Yes\n";
                return ;
            }
    cout << "No\n";
}

signed main() {
    int t = 1;
    t = read();
    while (t --) solve();
    return 0;
}
