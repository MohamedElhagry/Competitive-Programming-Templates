int anc[N][LG], par[N], dep[N], sz[N], head[N], timer, in[N], flat[N];
vi adj[N];
int n, val[N];
const ll IDN = 0;

struct SegTree {
    vector <ll> tree;
    static int n;

    ll combine(ll a, ll b) { 
        return a + b; 
    }

    void build(int inputN) {
        n = inputN;
        if (__builtin_popcount(n) != 1) 
            n = 1 << (__lg(n) + 1);
        tree.resize(n << 1, IDN);
        for (int i = 0; i < inputN; i++) 
            tree[i + n] = val[flat[i]];
        for (int i = n - 1; i >= 1; i--) 
            tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int ql, int qr, ll v, int k = 1, int sl = 0, int sr = n - 1) {
        if (qr < sl || sr < ql || ql > qr) return;
        if (ql <= sl && qr >= sr) {
            tree[k] = v;
            return;
        }
        
        int mid = (sl + sr) / 2;
        update(ql, qr, v, k << 1, sl, mid);
        update(ql, qr, v, (k << 1) | 1, mid + 1, sr);
        tree[k] = combine(tree[k << 1], tree[k << 1 | 1]);
    }

    ll query(int ql, int qr, int k = 1, int sl = 0, int sr = n - 1) {
        if (qr < sl || sr < ql || ql > qr) 
            return IDN;
        if (ql <= sl && qr >= sr) 
            return tree[k];
        
        int mid = (sl + sr) / 2;
        ll left = query(ql, qr, k << 1, sl, mid);
        ll right = query(ql, qr, k << 1 | 1, mid + 1, sr);
        return combine(left, right);
    }
};
int SegTree::n = 0;

void preTree(int v, int p) {
    par[v] = p;
    dep[v] = dep[p] + 1;
    sz[v] = 1;
    for (auto u: adj[v]) {
        if (u == p) 
            continue;
        preTree(u, v);
        sz[v] += sz[u];
    }
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

void decompose(int v, int p, int h) {
    head[v] = h, in[v] = timer, flat[timer++] = v;
    int mx = 0, big = 0;
    for (auto u: adj[v]) {
        if (u == p)
            continue;
        if (sz[u] > mx) {
            mx = sz[u];
            big = u;
        }
    }
    if (big) 
        decompose(big, v, h);
    for (auto u: adj[v]) {
        if (u == p || u == big) 
            continue;
        decompose(u, v, u);
    }
}

SegTree tree;
ll query(int a, int b) {
    ll res = IDN, lca = LCA(a, b);
    while (true) {
        if (head[a] == head[lca]) {
            res = tree.combine(res, tree.query(in[lca], in[a]));
            break;
        }
        else {
            res = tree.combine(res, tree.query(in[head[a]], in[a]));
            a = par[head[a]];
        }
    }
    while (true) {
        if (head[b] == head[lca]) {
            res = tree.combine(res, tree.query(in[lca], in[b]));
            break;
        }
        else {
            res = tree.combine(res, tree.query(in[head[b]], in[b]));
            b = par[head[b]];
        }
    } 
    
    // lca was taken twice, so remove it 
    res -= tree.query(in[lca], in[lca]);
    return res;
}

void init() {
    preTree(1, 1);
    preLCA();
    decompose(1, 1, 1);
    tree.build(n);
}