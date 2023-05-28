struct SegTree {
    vector<ll> tree;
    vector<ll> lazy;
    int n;
 
    ll combine(ll left, ll right) {
        return left + right;
    }
 
    void build(int oldn) {
        //if oldn is not a perfect power of two
        //oldn & (oldn-1) != 0
        if (__builtin_popcount(oldn) != 1)
            n = 1 << (__lg(oldn) + 1);
        else
            n = oldn;
 
        tree.resize(n << 1);
        lazy.resize(n << 1, 0);
        for (int i = 0; i < oldn; i++)
            tree[i + n] = 0;
        for (int i = oldn; i < n; i++)
            tree[i] = 0;
        for (int i = n - 1; i >= 1; i--)
            tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
    }
 
    void propagate(int k, int sl, int sr) {
        if (lazy[k] != 0) {
            tree[k] += lazy[k] * (sr - sl + 1);
            if (sl != sr) {
                lazy[k << 1] += lazy[k];
                lazy[k << 1 | 1] += lazy[k];
            }
        }
        lazy[k] = 0;
    }
 
    ll query(int ql, int qr, int k, int sl, int sr) {
        propagate(k, sl, sr);
        // if seg is totally inside the query range
        if (ql <= sl && sr <= qr)
            return tree[k];
        if (ql > sr || sl > qr)
            return 0;
 
        int mid = (sl + sr) / 2;
        return combine(query(ql, qr, k << 1, sl, mid), query(ql, qr, k << 1 | 1, mid + 1, sr));
    }
 
    //range update
    void update(int ql, int qr, ll v, int k, int sl, int sr) {
        propagate(k, sl, sr);
        // if seg is totally inside the update range
        if (ql <= sl && sr <= qr) {
            lazy[k] = v;
            propagate(k, sl, sr);
            return;
        }
        if (ql > sr || sl > qr)
            return;
 
        int mid = (sl + sr) / 2;
        update(ql, qr, v, k << 1, sl, mid);
        update(ql, qr, v, k << 1 | 1, mid + 1, sr);
//        propagate(k, sl, sr);
//        propagate(k << 1, sl, mid);
//        propagate(k << 1|1, mid+1, sr);
        tree[k] = combine(tree[k << 1], tree[k << 1 | 1]);
    }
};