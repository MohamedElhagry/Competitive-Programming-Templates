bool vis[N];
set<int> srcNodes;
void dfs(int u){
    if(vis[u])return;
    vis[u] = true;
    srcNodes.insert(u);
    for(auto e:adj[u]){
        if(cap[u][e] > 0)
            dfs(e);
    }
}

vector<pii> minCuts(int src, int sink){
    edmondsKarp(src, sink);
    memset(vis, 0, sizeof vis);
    dfs(1);
    vector<pii> cuts;
    for(auto e:srcNodes){
        for(auto v:adj[e]){
            if(srcNodes.find(v) == srcNodes.end())
                cuts.pb({e, v});
        }
    }
    return cuts;
}
