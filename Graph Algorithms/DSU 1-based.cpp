struct DSU{
    vi par, sz;

    DSU(int n) {
        par.resize(n + 1);
        sz.resize(n + 1);
        loop(i, 1, n) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int a)
    {
        if(a == par[a])
            return a;
        return find(par[a]);
    }
    
    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b)
            return;
        
        if(sz[a] > sz[b])
            swap(a,b);
        par[a] = b;
        sz[b] += sz[a];
    }
};