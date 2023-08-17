const ll IDN = OO, LAZY_IDN = 0;

struct SegTree {
    vector <ll> tree;
    vector <ll> lazy;
    static int n;

    ll combine(ll a, ll b) { 
        return min(a, b); 
    }

    void build(int inputN, ll *a) {
        n = inputN;
        if (__builtin_popcount(n) != 1) 
            n = 1 << (__lg(n) + 1);
        tree.resize(n << 1, IDN);
        lazy.resize(n << 1, LAZY_IDN);
        for (int i = 0; i < inputN; i++) 
            tree[i + n] = a[i];
        for (int i = n - 1; i >= 1; i--) 
            tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
    }

    void propagate(int k, int sl, int sr) {
        if (lazy[k] != LAZY_IDN) {
            tree[k] += lazy[k];
            if (sl != sr) {
                lazy[k << 1] += lazy[k];
                lazy[k << 1 | 1] += lazy[k];
            }
        }
        lazy[k] = LAZY_IDN;
    }

    void update(int ql, int qr, ll v, int k = 1, int sl = 0, int sr = n - 1) {
        propagate(k, sl, sr);
        if (qr < sl || sr < ql || ql > qr) return;
        if (ql <= sl && qr >= sr) {
            lazy[k] = v;
            propagate(k, sl, sr);
            return;
        }
        
        int mid = (sl + sr) / 2;
        update(ql, qr, v, k << 1, sl, mid);
        update(ql, qr, v, (k << 1) | 1, mid + 1, sr);
        tree[k] = combine(tree[k << 1], tree[k << 1 | 1]);
    }

    ll query(int ql, int qr, int k = 1, int sl = 0, int sr = n - 1) {
        propagate(k, sl, sr);
        if (qr < sl || sr < ql || ql > qr) return IDN;
        if (ql <= sl && qr >= sr) return tree[k];
        
        int mid = (sl + sr) / 2;
        ll left = query(ql, qr, k << 1, sl, mid);
        ll right = query(ql, qr, k << 1 | 1, mid + 1, sr);
        return combine(left, right);
    }
};
int SegTree::n = 0;