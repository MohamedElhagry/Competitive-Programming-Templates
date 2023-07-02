const int N = 500 + 5;
//node and index of node in adjList of dest and residual flow
vector<pair<pii,ll>> adj[N];
bool vis[N];

int src, sink;
bool dfs(int u, ll need){
    if(vis[u])
        return false;
    vis[u] = true;
    if(u == sink)
        return true;

    for(auto& e:adj[u]){
        if(e.S >= need && dfs(e.F.F, need)){
            e.S -= need;
            adj[e.F.F][e.F.S].S += need;
            return true;
        }
    }
    return false;
}

ll scaling(ll sum){
    ll flow = 0;
    for(ll val = sum; val;){
        if(dfs(src, val))
            flow += val;
        else val = val/2;
        memset(vis, 0, sizeof vis);
    }
    return flow;
}
