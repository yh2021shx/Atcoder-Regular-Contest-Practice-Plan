// From Luogu ID 小超手123
#include<bits/stdc++.h>
#define int long long
#define N 300005
using namespace std;

int n, Q;
int a[N], L[N], R[N], ans[N];

struct Tree1 { //区间加; 区间min 
    int c[N * 4], tag[N * 4];
    
    void clear() {
        memset(c, 0, sizeof(c));
        memset(tag, 0, sizeof(tag));
    }
    void pushup(int u) {
        c[u] = min(c[u * 2], c[u * 2 + 1]);
    }
    void maketag(int u, int x) {
        c[u] += x;
        tag[u] += x; 
    }
    void pushdown(int u) {
        if(!tag[u]) return;
        maketag(u * 2, tag[u]);
        maketag(u * 2 + 1, tag[u]);
        tag[u] = 0;
    }
    
    void update(int u, int L, int R, int l, int r, int x) {
        if(l <= L && R <= r) {
            maketag(u, x);
            return;
        }
        if(R < l || r < L) return;
        int mid = (L + R) / 2;
        pushdown(u);
        update(u * 2, L, mid, l, r, x);
        update(u * 2 + 1, mid + 1, R, l, r, x);
        pushup(u);
    }
    
    int query(int u, int L, int R, int l, int r) {
        if(l <= L && R <= r) return c[u];
        if(r < L || R < l) return 1e15;
        int mid = (L + R) / 2;
        pushdown(u);
        return min(query(u * 2, L, mid, l, r), query(u * 2 + 1, mid + 1, R, l, r));
    }
}t1;


struct node {
    int id, Max;
    friend node operator + (node A, node B) {
        if(A.Max > B.Max) return A;
        else if(A.Max < B.Max) return B;
        else return ((node){min(A.id, B.id), A.Max});
    }
};

struct Tree2 { //区间max 
    node c[N * 4];
    void pushup(int u) {
        c[u] = c[u * 2] + c[u * 2 + 1];
    }
    void build(int u, int L, int R) {
        if(L == R) {
            c[u].id = L;
            c[u].Max = a[L];
            return;
        }
        int mid = (L + R) /2;
        build(u * 2, L, mid);
        build(u * 2 + 1, mid + 1, R);
        pushup(u);
    }
    node query(int u, int L, int R, int l, int r) {
        if(l <= L && R <= r) return c[u];
        if(r < L || R < l) return (node){0, (int)-1e15};
        int mid = (L + R) / 2;
        return query(u * 2, L, mid, l, r) + query(u * 2 + 1, mid + 1, R, l, r);
    }
}t2;

vector<int>p[N];
int S[N], top;
void Sol1() { //解决 A=mx 或 C=mx 的问题 
    t1.clear();
    S[0] = 1; top = 0;
    for(int i = 1; i <= n; i++) p[i].clear();
    for(int i = 1; i <= Q; i++) p[R[i]].push_back(i);
    for(int i = 1; i <= n; i++) {
        while(top && a[i] >= a[S[top]]) {
            t1.update(1, 1, n, S[top - 1], S[top] - 1, -a[S[top]] + a[i]);
            top--;
        }
        S[++top] = i;
        if(i > 1) t1.update(1, 1, n, i - 1, i - 1, a[i - 1] + a[i]);
        for(auto Pos : p[i]) {
            node Get = t2.query(1, 1, n, L[Pos], R[Pos]);
            int x = Get.id;
            //cout << Get.Max << endl;
            //for(int z = x + 1; z <= i - 1; z++) cout << z << " : " << t1.query(1, 1, n, z, z) << endl;
            if(x + 1 <= i - 1) ans[Pos] = min(ans[Pos], Get.Max + t1.query(1, 1, n, x + 1, i - 1));
        }
    }
}


void Sol2() { //解决 B=mx 的问题 

    for(int i = 1; i <= Q; i++)
        ans[i] = min(ans[i], a[L[i]] + a[R[i]] + t2.query(1, 1, n, L[i] + 1, R[i] - 1).Max);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> Q;  
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= Q; i++) {
        cin >> L[i] >> R[i];
        ans[i] = 1e18;
    }
    
    
    t2.build(1, 1, n);
    
    Sol1();
    
    Sol2();
    
    reverse(a + 1, a + n + 1);
    for(int i = 1; i <= Q; i++) {
        int l = L[i], r = R[i];
        L[i] = n - r + 1;
        R[i] = n - l + 1;
    }
    t2.build(1, 1, n);
    Sol1();
    
    for(int i = 1; i <= Q; i++) cout << ans[i] << endl;
    return 0;
}
/*
5 1
4 3 1 1 4
1 5
*/

/*
7 1
4 3 1 1 4 5 2
1 7
*/
