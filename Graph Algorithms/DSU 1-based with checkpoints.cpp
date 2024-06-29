struct Save {
    int big, small;
    bool isCheckPoint;
};

struct DSU {
    vi par, sz;
    int comps;
    stack<Save> saves;

    DSU(int n) {
        par.resize(n + 1);
        sz.resize(n + 1);
        comps = n;
        for (int i = 1; i <= n; ++i) {
            par[i] = i;
            sz[i] = 1;
        }
        saves = stack<Save>();
    }

    int find(int x) {
        if (par[x] == x)return x;
        return find(par[x]);
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)return false;

        if (sz[u] < sz[v])swap(u, v);

        saves.push({u, v, false});
        par[v] = u;
        sz[u] += sz[v];
        comps--;
        return true;
    }

    void persist() {
        saves.push({-1, -1, true});
    }

    void rollback() {
        while (!saves.top().isCheckPoint) {
            auto save = saves.top();
            saves.pop();
            comps++;
            par[save.small] = save.small;
            sz[save.big] -= sz[save.small];
        }
        saves.pop();
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }
};