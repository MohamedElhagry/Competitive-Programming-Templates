vi adj[N];
map<vi, int> mp;
int h[N], n;

int dfs(int u, int p) {
    vi cur;
    for (auto e:adj[u])
        if (e != p)
            cur.pb(dfs(e, u));

    sort(all(cur));
    h[u] = mp.emplace(cur, mp.size()+1).first->S;
    return h[u];
}