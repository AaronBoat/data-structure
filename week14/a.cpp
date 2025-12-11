#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    double l, s;
};

inline bool hasNegativeCycle(const vector<Edge>& edges, int n, double lambda) {
    vector<double> dist(n, 0.0); // super source initialization

    // Perform n-1 relaxation rounds
    for (int i = 0; i < n - 1; ++i) {
        bool updated = false;
        for (const auto& e : edges) {
            double newDist = dist[e.u] + e.s - lambda * e.l;
            if (newDist < dist[e.v] - 1e-12) {
                dist[e.v] = newDist;
                updated = true;
            }
        }
        if (!updated) return false; // no negative cycle
    }

    // One more round to detect negative cycle
    for (const auto& e : edges) {
        if (dist[e.u] + e.s - lambda * e.l < dist[e.v] - 1e-12)
            return true;
    }
    return false;
}

inline bool hasDirectedCycle(int n, const vector<Edge>& edges) {
    vector<int> indeg(n, 0);
    vector<vector<int>> adj(n);
    for (const auto& e : edges) {
        adj[e.u].push_back(e.v);
        ++indeg[e.v];
    }
    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (indeg[i] == 0) q.push(i);
    int visited = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ++visited;
        for (int v : adj[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return visited != n;
}

string ratingFromRatio(double ratio) {
    if (ratio >= 140.0) return "A+";
    if (ratio >= 120.0) return "A";
    if (ratio >= 110.0) return "B";
    if (ratio >= 90.0)  return "C";
    if (ratio >= 70.0)  return "D";
    return "E";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<Edge> edges;
        edges.reserve(m);
        double maxRatio = 0.0;

        for (int i = 0; i < m; ++i) {
            int u, v;
            double l, s;
            cin >> u >> v >> l >> s;
            --u; --v;
            edges.push_back({u, v, l, s});
            if (l > 1e-9) {
                maxRatio = max(maxRatio, s / l);
            }
        }

        // If no directed cycle, IQ = +inf → A+
        if (!hasDirectedCycle(n, edges)) {
            cout << "A+\n";
            continue;
        }

        // Safeguard: if all l are zero (unlikely), set a large hi
        if (maxRatio < 1e-9) maxRatio = 1e9;

        double lo = 0.0, hi = maxRatio;
        // 50 iterations give ~1e-15 precision, more than enough
        for (int it = 0; it < 50; ++it) {
            double mid = (lo + hi) * 0.5;
            if (hasNegativeCycle(edges, n, mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }

        cout << ratingFromRatio(hi) << '\n';
    }
    return 0;
}