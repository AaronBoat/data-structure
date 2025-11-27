#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
const int LOG = 20;

vector<int> G[MAXN];
int depth[MAXN];
int parent0[MAXN];
int parent_table[LOG][MAXN];
int up[MAXN], color[MAXN];

int find_up(int u) {
    if (u == 0) return 0;
    if (up[u] != u) up[u] = find_up(up[u]);
    return up[u];
}

void bfs(int n) {
    queue<int> q;
    q.push(1);
    depth[1] = 0;
    parent0[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : G[u]) {
            if (v == parent0[u]) continue;
            parent0[v] = u;
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
    for (int i = 1; i <= n; i++) {
        parent_table[0][i] = parent0[i];
    }
}

void preprocess_lca(int n) {
    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j <= n; j++) {
            int p = parent_table[i-1][j];
            parent_table[i][j] = (p ? parent_table[i-1][p] : 0);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOG; i++) {
        if (diff & (1 << i)) {
            u = parent_table[i][u];
        }
    }
    if (u == v) return u;
    for (int i = LOG-1; i >= 0; i--) {
        if (parent_table[i][u] != parent_table[i][v]) {
            u = parent_table[i][u];
            v = parent_table[i][v];
        }
    }
    return parent_table[0][u];
}

void paint_path(int x, int y, int c) {
    int a = lca(x, y);
    x = find_up(x);
    while (x != 0 && depth[x] >= depth[a]) {
        color[x] = c;
        up[x] = parent0[x];
        x = find_up(up[x]);
    }
    y = find_up(y);
    while (y != 0 && depth[y] > depth[a]) {
        color[y] = c;
        up[y] = parent0[y];
        y = find_up(up[y]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    bfs(n);
    preprocess_lca(n);

    for (int i = 1; i <= n; i++) {
        up[i] = i;
        color[i] = 0;
    }

    struct Op { int x, y, c; };
    vector<Op> ops(q);
    for (int i = 0; i < q; i++) {
        cin >> ops[i].x >> ops[i].y >> ops[i].c;
    }

    for (int i = q-1; i >=0; i--) {
        paint_path(ops[i].x, ops[i].y, ops[i].c);
    }

    for (int i = 1; i <= n; i++) {
        cout << color[i];
        if (i < n) cout << ' ';
    }
    cout << '\n';

    return 0;
}