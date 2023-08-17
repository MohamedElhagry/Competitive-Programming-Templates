
vi adj[N];
vector<pii> bridges;
int in[N], low[N], timer;
void dfs(int u, int p){
    in[u] = low[u] = ++timer;
    for(auto e:adj[u]){
        if(e == p)
            continue;
        dfs(e, u);
        low[u] = min(low[u], low[e]);
    }
    if(p > 0 && in[p] < low[u])
        bridges.pb({u, p});
}
