
const int N = 2e5 + 5;
const int LG = 20;

int anc[N][20], p[N], d[N], n, q;
vi adj[N];

void dfs(int u, int par, int dep) {
    p[u] = par;
    d[u] = dep;
    for (int e: adj[u])
        if (e != par)
            dfs(e, u, dep + 1);
}

void pre() {
    for (int k = 0; k < LG; ++k) {
        for (int u = 1; u <= n; ++u) {
            if (k == 0) anc[u][k] = p[u];
            else anc[u][k] = anc[anc[u][k - 1]][k - 1];
        }
    }
}

int binLift(int u, int x) {
    for (int b = 0; b < LG; ++b)
        if ((1 << b) & x) u = anc[u][b];
    return u;
}

int LCA(int u, int v) {
    if (d[u] < d[v])swap(u, v);
    u = binLift(u, d[u] - d[v]);
    if (u == v)return u;
    for (int b = LG; b >= 0; --b) {
        if (anc[u][b] == anc[v][b])continue;
        u = anc[u][b];
        v = anc[v][b];
    }
    return anc[u][0];
}
 