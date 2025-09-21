#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static ll readInt() {
    int c = getchar();
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    int sign = 1;
    if (c == '-') { sign = -1; c = getchar(); }
    ll x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x * sign;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = (int)readInt();
    int m = 2 * n;
    vector<int> a(n+1), b(n+1);

    // La[pos] = person index whose A == pos (or 0)
    // Rb[pos] = person index whose B == pos (or 0)
    vector<int> La(m+1, 0), Rb(m+1, 0);

    for (int i = 1; i <= n; ++i) {
        a[i] = (int)readInt();
        b[i] = (int)readInt();
        if (a[i] != -1) {
            if (La[a[i]] != 0) { cout << "No\n"; return 0; }
            La[a[i]] = i;
        }
        if (b[i] != -1) {
            if (Rb[b[i]] != 0) { cout << "No\n"; return 0; }
            Rb[b[i]] = i;
        }
        if (a[i] != -1 && b[i] != -1 && a[i] >= b[i]) {
            cout << "No\n"; return 0;
        }
    }
    // If same floor is recorded once as someone's A and once as someone's B,
    // they must refer to the same person (otherwise impossible).
    for (int pos = 1; pos <= m; ++pos) {
        if (La[pos] != 0 && Rb[pos] != 0 && La[pos] != Rb[pos]) {
            cout << "No\n"; return 0;
        }
    }

    vector<char> f(m+1, 0);
    f[0] = 1;

    auto check = [&](int l, int r)->bool {
        int end = 2*r - l - 1;
        if (l < 1 || r > m || end > m) return false;
        for (int k = l; k < r; ++k) {
            int pl = k;
            int pr = k - l + r;
            if (La[pl] != 0) {
                int idx = La[pl];
                if (b[idx] != -1 && b[idx] != pr) return false;
            }
            if (Rb[pr] != 0) {
                int idx = Rb[pr];
                if (a[idx] != -1 && a[idx] != pl) return false;
            }
            // **关键**：如果左端和右端都记录着（La != 0 且 Rb != 0），
            // 它们必须是同一个人编号，否则该对会强制把两个不同人的端点合并 —— 不允许。
            if (La[pl] != 0 && Rb[pr] != 0 && La[pl] != Rb[pr]) return false;
        }
        // 左半段不能有已知的下车点
        for (int k = l; k < r; ++k)
            if (Rb[k] != 0) return false;
        // 右半段不能有已知的上车点
        for (int k = r; k <= end; ++k)
            if (La[k] != 0) return false;
        return true;
    };

    for (int i = 0; i < m; ++i) {
        if (!f[i]) continue;
        int l = i + 1;
        for (int r = i + 1; r <= m; ++r) {
            int end = 2*r - l - 1;
            if (end > m) break;
            if (check(l, r)) f[end] = 1;
        }
    }

    cout << (f[m] ? "Yes\n" : "No\n");
    return 0;
}
