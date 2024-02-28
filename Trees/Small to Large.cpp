int par[N], d[N], sz[N];
vi adj[N];

void dfs(int v, int p) {
    par[v] = p;
    d[v] = d[p] + 1;
    sz[v] = 1;
    for (auto u: adj[v]) {
        if (u == p)
            continue;
        dfs(u, v);
        sz[v] += sz[u];
    }
}

vi *cols[N];
int c[N], freq[N], distinct, ans[N];

void smallToLarge(int v, int p, bool keep) {
    int mx = 0, big = 0;
    for (auto u: adj[v]) {
        if (u == p) 
            continue;
        if (sz[u] > mx) {
            mx = sz[u];
            big = u;
        }
    }
    for (auto u: adj[v]) {
        if (u == p || u == big) 
            continue;
        smallToLarge(u, v, false);
    }
    if (big) 
        smallToLarge(big, v, true), cols[v] = cols[big]; 
    else 
        cols[v] = new vi;
    
    cols[v]->pb(c[v]);
    freq[c[v]]++;
    if (freq[c[v]] == 1) 
        distinct++;
    for (auto u: adj[v]) {
        if (u == p || u == big) 
            continue;
        for (auto e: *cols[u]) {
            cols[v]->pb(e);
            freq[e]++;
            if (freq[e] == 1) 
                distinct++;
        }
    }
    ans[v] = distinct;
    if (keep) 
        return;
    for (auto e: *cols[v]) {
        freq[e]--;
        if (!freq[e]) 
            --distinct;
    }
}