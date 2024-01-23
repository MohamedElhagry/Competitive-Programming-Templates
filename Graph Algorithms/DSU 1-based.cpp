struct DSU {
    int n, comps;
    vector<int> sz, par;

    DSU(int n) {
        this->n = n;
        comps = n;
        sz.resize(n + 1);
        par.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            sz[i] = 1;
            par[i] = i;
        }
    }

    int find(int x) {
        if (par[x] == x) return x;
        return find(par[x]);
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        comps--;
        return true;
    }
}; 