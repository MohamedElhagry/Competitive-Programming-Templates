const ll OO = 1e18;
const int N = 500 + 5;
//capacity matrix
ll cap[N][N];
vi adj[N];
int n;

ll bfs(int src, int sink, vi& par){
    fill(par.begin(), par.end(), -1);
    par[src] = -2;
    queue<pair<int, ll>> q;

    q.push({src, OO});
    while(!q.empty()){
        int p;
        ll flow;
        tie(p, flow) = q.front();q.pop();
        for(auto e:adj[p]){
            if(!~par[e] && cap[p][e]){
                ll newFlow = min(flow, cap[p][e]);
                q.push({e, newFlow});
                par[e] = p;
                if(e == sink)return newFlow;
            }
        }
    }
    return 0;
}

ll edmondsKarp(int src, int sink){
    ll flow = 0, newFlow;
    vector<int> par(n+1);

    while(newFlow = bfs(src, sink, par)){
        flow += newFlow;
        //modify the graph
        int cur = sink;
        while(par[cur] != -2){
            int prv = par[cur];
            cap[cur][prv] += newFlow;
            cap[prv][cur] -= newFlow;
            cur = prv;
        }
    }
    return flow;
}

void addEdge(int u, int v, int edgeCap){
    adj[u].pb(v);
    adj[v].pb(u);
    cap[u][v] = edgeCap;
}