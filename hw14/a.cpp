#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
using ll = long long;

struct DSU
{
    vector<int> parent;
    vector<int> size;

    DSU(int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    void reset(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            return false;
        }
        if (size[x] < size[y])
        {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        return true;
    }
};

struct edge
{
    int u, v, a, b;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, S, T;
    cin >> n >> m >> S >> T;

    vector<edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].a >> edges[i].b;
    }

    ll ans = LLONG_MAX;

    // 策略1: 按 a 排序，维护按 b 有序的边集合
    {
        // 按 a 排序
        sort(edges.begin(), edges.end(), [](const edge &x, const edge &y)
             { return x.a < y.a; });

        vector<edge> active_edges; // 维护按 b 有序的边集合
        DSU dsu(n);

        for (int i = 0; i < m; i++)
        {
            int a_max = edges[i].a;

            // 二分插入，保持 active_edges 按 b 有序
            int pos = lower_bound(active_edges.begin(), active_edges.end(),
                                  edges[i],
                                  [](const edge &x, const edge &y)
                                  {
                                      return x.b < y.b;
                                  }) -
                      active_edges.begin();
            active_edges.insert(active_edges.begin() + pos, edges[i]);

            // 如果边数不够，跳过
            if ((int)active_edges.size() < n - 1)
                continue;

            // 用 active_edges（已按 b 排序）构建 MST
            dsu.reset(n);
            int merge = 0;
            int b_max = 0;

            for (const auto &e : active_edges)
            {
                if (dsu.unite(e.u, e.v))
                {
                    merge++;
                    b_max = e.b;
                    if (merge == n - 1)
                    {
                        break;
                    }
                }
            }

            if (merge == n - 1)
            {
                ll cost = 1LL * a_max * S + 1LL * b_max * T;
                ans = min(ans, cost);
            }
        }
    }

    if (ans == LLONG_MAX)
    {
        cout << -1 << '\n';
    }
    else
    {
        cout << ans << '\n';
    }

    return 0;
}