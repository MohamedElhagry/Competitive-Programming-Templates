const ll OO = 1e18;
const int N = 500 + 5;

struct Edge {
    int a, b, cap, cost, invID;

    Edge(int a, int b, int cap, int cost, int invID = 0) : a(a), b(b), cap(cap), cost(cost), invID(invID) {}
};

struct MinCostFlow {
    //edges going out of i, format: to, (id of inverse edge or cost or cap)
    vector<Edge> adj[N];
    int n;

    ll SP(int src, int sink, vi &p, vector<ll> &d, vi &ids) {
        fill(p.begin(), p.end(), -1);
        fill(ids.begin(), ids.end(), -1);
        fill(d.begin(), d.end(), OO);
        vector<bool> inQ(n + 1);
        queue<int> q;
        q.push(src);
        d[src] = 0;
        inQ[src] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            inQ[node] = false;
            int id = 0;
            for (auto &e:adj[node]) {
                if (e.cap && d[node] + e.cost < d[e.b]) {
                    d[e.b] = d[node] + e.cost;
                    p[e.b] = node;
                    ids[e.b] = id;
                    if (!inQ[e.b]) {
                        inQ[e.b] = true;
                        q.push(e.b);
                    }
                }
                ++id;
            }
        }
        return d[sink];
    }

    ll minCostFlow(vector<Edge> &edges, int n, int src, int sink, ll k){
        this->n = n;
        vi p(n + 1), ids(n + 1);
        vector<ll> d(n + 1);

        for (auto e:edges) {
            int invIndA = (int) adj[e.b].size(), invIndB = (int) adj[e.a].size();
            adj[e.a].pb(Edge(e.a, e.b, e.cap, e.cost, invIndA));
            adj[e.b].pb(Edge(e.b, e.a, 0, -e.cost, invIndB));
        }

        ll need = k, totalCost = 0;
        while (need && SP(src, sink, p, d, ids) != OO) {
            // get cost and new newFlow
            int newFlow = need;
            int cur = sink;
            while (cur != src) {
                int prv = p[cur];
                newFlow = min(newFlow, adj[prv][ids[cur]].cap);
                cur = prv;
            }

            //apply the new flow to the path
            need -= newFlow;
            totalCost += newFlow * d[sink];
            cur = sink;
            while (cur != src) {
                int prv = p[cur];
                adj[prv][ids[cur]].cap -= newFlow;
                int invInd = adj[prv][ids[cur]].invID;
                adj[cur][invInd].cap += newFlow;
                cur = p[cur];
            }
        }
        if (need)
            return -1;
        return totalCost;
    }
};