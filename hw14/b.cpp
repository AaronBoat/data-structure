#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

using ll = long long;

struct City {
    ll x, y;      // 坐标
    ll buildCost; // 在该城市建电站的花费 c_i
    ll connectRate; // 连接线路的单位费率 k_i
};

struct Edge {
    int u, v;
    ll weight;
    
    // 为 sort 提供比较函数（可选，也可用 lambda）
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

const int MAXN = 2005;
City city[MAXN];
vector<Edge> edges;
int parent[MAXN];

// 并查集：带路径压缩
int findRoot(int x) {
    if (x == parent[x]) return x;
    return parent[x] = findRoot(parent[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 读入坐标
    for (int i = 1; i <= n; ++i) {
        cin >> city[i].x >> city[i].y;
    }

    // 读入建电站成本 c_i
    for (int i = 1; i <= n; ++i) {
        cin >> city[i].buildCost;
    }

    // 读入连接费率 k_i
    for (int i = 1; i <= n; ++i) {
        cin >> city[i].connectRate;
    }

    // 虚拟节点 0：代表“建电站”
    // 从虚拟点 0 到城市 i 的边权 = 在 i 建电站的花费
    for (int i = 1; i <= n; ++i) {
        edges.push_back({0, i, city[i].buildCost});
    }

    // 城市 i 与 j 之间建电网的花费
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            ll manhattanDist = llabs(city[i].x - city[j].x) + llabs(city[i].y - city[j].y);
            ll cost = (city[i].connectRate + city[j].connectRate) * manhattanDist;
            edges.push_back({i, j, cost});
        }
    }

    // 按边权升序排序（Kruskal）
    sort(edges.begin(), edges.end());

    // 初始化并查集：0 ~ n 共 n+1 个节点
    for (int i = 0; i <= n; ++i) {
        parent[i] = i;
    }

    ll totalCost = 0;
    int edgesUsed = 0;

    // Kruskal 算法：选最小生成树
    for (const auto& edge : edges) {
        int rootU = findRoot(edge.u);
        int rootV = findRoot(edge.v);
        if (rootU != rootV) {
            parent[rootU] = rootV;
            totalCost += edge.weight;
            ++edgesUsed;

            // 最小生成树需要 n 条边（n+1 个节点：0,1,...,n）
            if (edgesUsed == n) {
                cout << totalCost << '\n';
                return 0;
            }
        }
    }

    // 理论上不会走到这里（图一定连通）
    cout << totalCost << '\n';
    return 0;
}