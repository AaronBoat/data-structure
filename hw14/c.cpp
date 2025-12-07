#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

struct Edge {
    int u, v;
    ll weight;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

const int MAXN = 200005;
ll nodeValue[MAXN];       // 原数组 a[i]
int parent[MAXN];

// 并查集（带路径压缩）
int findRoot(int x) {
    if (x == parent[x]) return x;
    return parent[x] = findRoot(parent[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    ll globalMin = 1e18;   // 全局最小 a[i]
    int globalMinIdx = 1;  // 全局最小值的下标

    for (int i = 1; i <= n; ++i) {
        cin >> nodeValue[i];
        if (nodeValue[i] < globalMin) {
            globalMin = nodeValue[i];
            globalMinIdx = i;
        }
    }

    vector<Edge> edges;
    edges.reserve(m + n);

    // 读入原始 m 条边
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    // 关键建模：添加“通过全局最小点间接连接”的虚拟边
    // 任意两点 i, j 可通过 minIdx 中转，成本为 a[i] + a[j]
    // 但为避免 O(n²) 建边，我们只连 i -> globalMinIdx，权重 = a[i] + globalMin
    for (int i = 1; i <= n; ++i) {
        if (i != globalMinIdx) {
            edges.push_back({i, globalMinIdx, nodeValue[i] + globalMin});
        }
    }

    // 按边权升序排序（Kruskal）
    sort(edges.begin(), edges.end());

    // 初始化并查集（1 ~ n）
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }

    ll totalCost = 0;
    int edgesUsed = 0;

    // Kruskal 算法
    for (const auto& edge : edges) {
        int rootU = findRoot(edge.u);
        int rootV = findRoot(edge.v);
        if (rootU != rootV) {
            parent[rootU] = rootV;
            totalCost += edge.weight;
            ++edgesUsed;

            if (edgesUsed == n - 1) {
                cout << totalCost << '\n';
                return 0;
            }
        }
    }

    // 理论上图一定连通（因为加了星形虚拟边）
    cout << totalCost << '\n';
    return 0;
}