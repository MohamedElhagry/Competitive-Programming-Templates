const ll OO = 1e18;
const int N = 1e5 + 5;

vector<pair<int, ll>> adj[N];
ll dist[N];
int n, m;

void dijkstra(int src) {
    for (int i = 1; i <= n; i++)
        dist[i] = OO;

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll,int>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while(!pq.empty()){
        int u;ll w;
        tie(w, u) = pq.top();
        pq.pop();
        if(dist[u] < w)
            continue;

        for(auto e:adj[u]){
            if(dist[u] + e.S < dist[e.F]){
                dist[e.F] = dist[u] + e.S;
                pq.push({dist[e.F], e.F});
            }
        }
    }
}
