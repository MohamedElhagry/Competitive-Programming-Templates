int sz[N], n, k, freq[N];
vi adj[N];
bool rem[N];

void preSize(int i, int par) {
    sz[i] = 1;
    for (auto e: adj[i]) {
        if (e == par || rem[e])
            continue;
        preSize(e, i);
        sz[i] += sz[e];
    }
}

int getCen(int u, int p, int curSz) {
    for (auto v: adj[u]) {
        if (rem[v] || v == p)continue;
        if (sz[v] * 2 > curSz)
            return getCen(v, u, curSz);
    }
    return u;
}

ll solve(int v, int par, int d) {
    ll ans = k >= d ? freq[k - d] : 0;
    for (auto u: adj[v]) {
        if (rem[u] || u == par) 
            continue;
        ans += solve(u, v, d + 1);
    }
    return ans;
}

void update(int v, int par, int d, int inc) {
    freq[d] += inc;
    for (auto u: adj[v]) {
        if (rem[u] || u == par)
            continue;
        update(u, v, d + 1, inc);
    }
}

ll getAns(int v) {
    ll ans = 0;
    for (auto u: adj[v]) {
        if (rem[u]) 
            continue;
        ans += solve(u, v, 1);
        update(u, v, 1, 1);
    }
    return ans;
}

ll decompose(int v) {
    preSize(v, 0);
    int cen = getCen(v, 0, sz[v]);
    freq[0]++;
    ll ans = getAns(cen);
    update(cen, 0, 0, -1);
    rem[cen] = true;
    for (auto u: adj[cen]) {
        if (rem[u]) 
            continue;
        ans += decompose(u);
    }
    return ans;
}