///HLD
const int N = 2e5 + 5;
const int LG = 20;

const int IDN = 0;
int segTree[N<<2];
// ind is index of node in segTree, indInv is node which this index refers to
int oldn, n, p[N], d[N], sz[N], arr[N], h[N], mxChild[N], ind[N], indInv[N], anc[N][LG], curr;
vi adj[N];

int combine(int a, int b) {
    return a ^ b;
}
void build() {
    oldn = n;
    if(__builtin_popcount(n) != 1)
        n = 1 << (__lg(n) + 1);

    for(int i=0; i<oldn; i++)
        segTree[i + n] = arr[indInv[i]];
    for (int i = n - 1; i >= 1; i--)
        segTree[i] = combine(segTree[i << 1], segTree[(i << 1) | 1]);
}
void update(int ql, int qr, int v, int k = 1, int sl = 0, int sr = n - 1) {
    if (sl == sr && sl == ql) {
        segTree[k] = v;
        return;
    }
    if (qr < sl || sr < ql)
        return;

    int mid = (sl + sr) / 2;
    update(ql, qr, v, k << 1, sl, mid);
    update(ql, qr, v, (k << 1) | 1, mid + 1, sr);

    segTree[k] = combine(segTree[k << 1], segTree[k << 1 | 1]);
}
int query(int ql, int qr, int k = 1, int sl = 0, int sr = n - 1) {
    if (ql <= sl && qr >= sr)
        return segTree[k];

    if (qr < sl || sr < ql)
        return IDN;

    int mid = (sl + sr) / 2;

    return combine(query(ql, qr, k << 1, sl, mid), query(ql, qr, k << 1 | 1, mid + 1, sr));
}

void pre(int i, int par)
{
    p[i] = par; d[i] = d[par]+1; sz[i] = 1;
    int mxSize = 0;
    for(auto e:adj[i])
    {
        if(e == par)continue;
        pre(e, i);
        sz[i] += sz[e];
        if(sz[e] > mxSize)
        {
            mxSize = sz[e]; mxChild[i] = e;
        }
    }
}
void conHLD(int i, int par, int head)
{
    ind[i] = curr;indInv[curr] = i;h[i] = head;
    ++curr;
    if(mxChild[i])
        conHLD(mxChild[i], i, head);
    for(auto e:adj[i])
    {
        if(e == par || e == mxChild[i])
            continue;
        conHLD(e, i, e);
    }
}
void preLCA() {
    for (int k = 0; k < LG; k++) {
        for (int i = 1; i <= n; i++) {
            if (k == 0)anc[i][k] = p[i];
            else anc[i][k] = anc[anc[i][k - 1]][k - 1];
        }
    }
}
void init()
{
    pre(1,1);
    preLCA();
    conHLD(1,1,1);
    build();
}

int binaryLift(int x, int jump)
{
    for(int b=0; b<LG; b++)
    {
        if(jump & (1 << b))
            x = anc[x][b];
    }
    return x;
}
int LCA(int a, int b)
{
    if(d[a] > d[b])
        swap(a, b);
    int diff = d[b] - d[a];
    b = binaryLift(b, diff);
    if(a == b)
        return a;
    for(int bit=LG-1; bit>=0; bit--)
    {
        if(anc[a][bit]==anc[b][bit])
            continue;
        a = anc[a][bit];
        b = anc[b][bit];
    }
    return p[a];
}

int queryJump(int x, int end)
{
    if(d[x] < d[end]) return 0;
    if(d[h[x]] <= d[end])
        return query(ind[end], ind[x]);
    if(d[h[x]] > d[end])
        return combine(query(ind[h[x]], ind[x]), queryJump(p[h[x]], end));
}

int queryN(int a, int b)
{
    int lca = LCA(a, b);
    int res = combine(queryJump(a,lca), queryJump(b, lca));
    return combine(res, query(ind[lca],ind[lca]));
}
