int in[N], out[N], col[N], flat[2 * N], timer;
int anc[N][20], par[N], dep[N], n, q;
vi adj[N];

void flatten(int v) {
    dep[v] = dep[par[v]] + 1;
    in[v] = timer, flat[timer] = v, ++timer;
    for (auto u: adj[v]) { 
        flatten(u); 
    }
    out[v] = timer, flat[timer] = v, ++timer;
}

void preLCA() { // k is 2^k anc 
    for (int k = 0; k < LG; k++) {
        for (int i = 1; i <= n; i++) {
            if (k == 0)
                anc[i][k] = par[i];
            else 
                anc[i][k] = anc[anc[i][k - 1]][k - 1];
        }
    }
}

int binaryLift(int x, int jump) {
    for (int b = 0; b < LG; b++) { 
        if (jump & (1 << b)) 
            x = anc[x][b]; 
    }
    return x;
}

int LCA(int a, int b) {
    if (dep[a] > dep[b]) 
        swap(a, b); // guaranteed that b is deeper 
    // make same depth 
    int diff = dep[b] - dep[a];
    b = binaryLift(b, diff);
    if (a == b) 
        return a;
    
    for (int bit = LG - 1; bit >= 0; bit--) {
        if (anc[a][bit] == anc[b][bit]) 
            continue;
        a = anc[a][bit];
        b = anc[b][bit];
    }
    return par[a];
}

struct Query {
    int l, r, ind, lca;

    Query(int _l, int _r, int _ind, int _lca = -1) : l(_l), r(_r), ind(_ind), lca(_lca) {}

    bool operator<(const Query &q2) { 
        return (l / B < q2.l / B) || (l / B == q2.l / B && r < q2.r); 
    }
};

int freqcol[N], freqind[N], distinct;

void upd(int ind, int inc) {
    int v = flat[ind];
    freqind[v] += inc;
    if (freqind[v] == 1) {
        freqcol[col[v]]++;
        if (freqcol[col[v]] == 1) 
            distinct++;
    }
    else {
        freqcol[col[v]]--;
        if (freqcol[col[v]] == 0) 
            distinct--;
    }
}

void init() {
    flatten(1);
    preLCA();
}

int ans[N];

void takeQueries() {
    vector<Query> queries;
    int x, y;
    for(int i = 0; i < q; i++)
    {
        cin >> x >> y;
        if (in[x] > in[y]) 
            swap(x, y);
        int lca = LCA(x, y);
        if (lca == x) 
            queries.emplace_back(Query(in[x], in[y], i));
        else
            queries.emplace_back(Query(out[x], in[y], i, lca));
    }
    sort(all(queries)); 
    
    // mo 
    int l = 0, r = 0;
    upd(0, 1);
    for(auto query:queries)
    {
        while (r < query.r) 
            upd(++r, 1);
        while (l > query.l) 
            upd(--l, 1);
        while (l < query.l) 
            upd(l++, -1);
        while (r > query.r) 
            upd(r--, -1);
        ans[query.ind] = distinct + (query.lca >= 0 && freqcol[col[query.lca]] == 0);
    }
}