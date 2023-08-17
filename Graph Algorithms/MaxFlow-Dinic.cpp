struct Edge {
    int u, v;
    ll cap, flow;

    Edge() {}

    Edge(int u, int v, ll cap, ll flow) : u(u), v(v), cap(cap), flow(flow) {}
};

const ll OO = 1e18;

struct Dinic {
    int n, m, s, t;
    vector<Edge> edges;
    //adjacency list stores the edge indices instead of the end nodes
    vvi adj;
    vi level, ptr;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        m = 0;
        adj.resize(n + 1);
        level.resize(n + 1);
        ptr.resize(n + 1);
    }

    void addEdge(int u, int v, ll flow) {
        edges.pb(Edge(u, v, flow, 0));
        edges.pb(Edge(v, u, 0, 0));
        adj[u].pb(m++);
        adj[v].pb(m++);
    }

    bool bfs() {
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            for (auto id:adj[p]) {
                Edge e = edges[id];
                if (e.cap - e.flow == 0)continue;
                if (level[e.v] != 0)continue;
                level[e.v] = level[e.u] + 1;
                q.push(e.v);
            }
        }
        return level[t] != 0;
    }

    ll dfs(int u, ll pushed) {
        if (pushed == 0)
            return 0;
        if (u == t)
            return pushed;
        for (int &e = ptr[u]; e < adj[u].size(); ++e) {
            int id = adj[u][e];
            Edge edge = edges[id];
            if (edge.cap - edge.flow == 0)continue;
            if (level[edge.v] != level[edge.u] + 1)continue;
            ll f = dfs(edge.v, min(edge.cap - edge.flow, pushed));
            if (f == 0)continue;
            edges[id].flow += f;
            edges[id ^ 1].flow -= f;
            return f;
        }
        return 0;
    }

    ll flow() {
        ll flow = 0;
        while (true) {
            fill(level.begin(), level.end(), 0);
            fill(ptr.begin(), ptr.end(), 0);
            level[s] = 1;
            if (!bfs())
                break;
            ll pushed;
            do {
                pushed = dfs(s, OO);
                flow += pushed;
            } while (pushed > 0);
        }
        return flow;
    }

    bool isLeftOfMinCut(int u){
        return level[u] != 0;
    }
};