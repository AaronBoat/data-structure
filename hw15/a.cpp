#include <iostream>
#include <vector>
using namespace std;
int T, n, m;

const int MAXN = 3005;

// int state[MAXN];//0 , 1=这次访问过 ， 2 = 已经结束访问，不可能成环
struct E
{
    int to, s, l;
    E(int _to, int _s, int _l)
    {
        to = _to;
        s = _s;
        l = _l;
    }
    /* data */
};

bool dfs_cycle(int at, vector<vector<E>> &edge, vector<int> &state)
{
    state[at] = 1;
    for (E e : edge[at])
    {
        if (state[e.to] == 0)
        {
            if (dfs_cycle(e.to, edge, state))
            {
                return true;
            }
        }
        if (state[e.to] == 1)
        {
            return true;
        }
    }
    state[at] = 2;
    return false;
}

int main()
{
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        vector<vector<E>> edge(m + 1);
        vector<int> state(n + 1);
        bool nocycle = true;
        for (int i = 0; i < m; i++)
        {
            int u, v, l, s;
            cin >> u >> v >> l >> s;
            edge[u].push_back(E(v, l, s));
        }
        for (int i = 1; i <= n; i++)
        {
            if(state[i] == 2)
            {
                continue;
            }
            if(dfs_cycle(i,edge,state))
            {
                nocycle = false;
                break;
            }
        }
        if(nocycle)
        {
            cout << "A+\n";
            continue;
        }
    }
}