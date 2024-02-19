struct SEG {
    ll sum = 0;
    SEG() {
    }
    SEG(ll x){
        sum = x;
    }
};
struct segTree {
    vector<SEG> seg;
    int sz = 1,n;
    segTree(int nn){
        n = nn;
        while (sz < nn)
            sz *= 2;
        seg.assign(2 * sz , SEG());
    }
    
    SEG merge(SEG seg1, SEG seg2) {
        SEG ret;
        ret.sum = seg1.sum + seg2.sum;
        return ret;
    }
    
    void build(vector<int> &v,int x, int lx, int rx) {
        if (lx == rx) {
            seg[x] = SEG(v[lx]);
            return;
        }
        int mid = (lx + rx) / 2;
        int lf = 2 * x + 1, rt = 2 * x + 2;

        build(v,lf, lx, mid);
        build(v,rt, mid + 1, rx);
        seg[x] = merge(seg[lf], seg[rt]);
    }
    void build(vector<int> &v){
        build(v,0, 0, n-1);
    }

    void update(int i, ll val, int x, int lx, int rx) {
        if (lx == rx) {
            seg[x] = SEG(val);
            return;
        }
        int mid = (lx + rx) / 2,lf = 2*x+1,rt= 2*x+2;
        if(i <= mid)
            update(i, val, lf, lx, mid);
        else
            update(i, val, rt, mid + 1, rx);
        seg[x] = merge(seg[lf] , seg[rt]);
    }

    void update(int i, ll val) {
        update(i, val, 0, 0, n-1);
    }
    
    SEG query(int l, int r, int x, int lx, int rx) {
        if (l <= lx && r >= rx)
            return seg[x];
        if (l > rx || r < lx)
            return SEG();

        int mid = (lx + rx) / 2,lf = 2 * x + 1,rt = 2*x+2;

        return merge(query(l, r, lf, lx, mid) , query(l, r, rt, mid + 1, rx));
    }

    SEG query(int l, int r) {
        return query(l, r, 0, 0, n-1);
    }
};