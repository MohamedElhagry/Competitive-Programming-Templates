struct Seg {
    vector<ll> freq;
    ll inv;
 
    Seg() {
        freq.resize(MX);
        inv = 0;
    }
 
    Seg(ll u) {
        freq.resize(MX);
        freq[u] = 1;
        inv = 0;
    }
};
 
struct SegTree {
    vector<Seg> tree;
    int n;
 
    Seg combine(Seg left, Seg right) {
        Seg ret;
        ret.inv = left.inv + right.inv;
        ll curInv = 0, sum = 0;
        for (int i = 0; i < MX; i++) {
            curInv += left.freq[i] * sum;
            sum += right.freq[i];
        }
        ret.inv += curInv;
        for (int i = 0; i < MX; i++)
            ret.freq[i] = left.freq[i] + right.freq[i];
        return ret;
    }
 
    void build(int oldn, ll *arr) {
        //if oldn is not a perfect power of two
        //oldn & (oldn-1) != 0
        if (__builtin_popcount(oldn) != 1)
            n = 1 << (__lg(oldn) + 1);
        else
            n = oldn;
 
        tree.resize(n << 1);
        for (int i = 0; i < oldn; i++)
            tree[i + n] = Seg(arr[i]);
        for (int i = oldn; i < n; i++)
            tree[i] = Seg(41);
        for (int i = n - 1; i >= 1; i--)
            tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
    }
 
    Seg query(int ql, int qr, int k, int sl, int sr) {
        // if seg is totally inside the query range
        if (ql <= sl && sr <= qr)
            return tree[k];
        if (ql > sr || sl > qr)
            return Seg();
 
        int mid = (sl + sr) / 2;
        return combine(query(ql, qr, k << 1, sl, mid), query(ql, qr, k << 1 | 1, mid + 1, sr));
    }
 
    //point update
    void update(int ql, int qr, ll v, int k, int sl, int sr) {
        // if seg is totally inside the update range
        //ql == qr -> sl == sr
        if (ql <= sl && sr <= qr) {
            tree[k] = Seg(v);
            return;
        }
        if (ql > sr || sl > qr)
            return;
 
        int mid = (sl + sr) / 2;
        update(ql, qr, v, k << 1, sl, mid);
        update(ql, qr, v, k << 1 | 1, mid + 1, sr);
        tree[k] = combine(tree[k << 1], tree[k << 1 | 1]);
    }
};